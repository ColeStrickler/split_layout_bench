#include "manager.hpp"



std::string InsertDTLConfigParameters(TableConfig tableConf, int view_col_count)
{
    std::unordered_map<std::string, int> params = {
        {"ROWS", tableConf.rows},
        {"COLUMNS", view_col_count}
    };

    std::string dtl_parameterized_config = proj_stencil;

    for (auto& [key, value] : params) {
       // printf("%s,%d\n", key.c_str(), value);
        std::string token = "[" + key + "]";
        size_t pos;
        while ((pos = dtl_parameterized_config.find(token)) != std::string::npos)
            dtl_parameterized_config.replace(pos, token.size(), std::to_string(value));
    }
    //printf("parametrized config %s\n", dtl_parameterized_config.c_str());
    return dtl_parameterized_config;
}

std::string CreateDTLConstants(std::vector<uint32_t> columns, int row_size) 
{
    std::string ret;
    ret += "int row_size = " + std::to_string(row_size) + ";\n";

    ret += "int col_offsets = {";
    for (auto& x: columns)
        ret += std::to_string(x) + ",";
    ret += "};\n";
    return ret;
}

std::string SplitQuery2InfoString(SplitQuery query) 
{
    std::string ret = "db_split__";
    
    for (auto& s: query.filter)
    {
        for (auto& fc: s.columns)
        {
            ret += std::to_string(fc) + "-";
        }
    }
    
    ret += "__";

    for (auto& s: query.selection.columns)
        ret += std::to_string(s) + "-";

    return ret;
}

std::string Query2InfoString(Query query) 
{
    std::string ret = "db__";
    
    for (int i = 0; i < query.filterCols; i++)
    {

        ret += std::to_string(query.view.columns[i]) + "-";
    }
    
    ret += "__";

    for (int i = 0; i < query.selCols; i++)
    {

        ret += std::to_string(query.view.columns[query.filterCols + i]) + "-";
    }
    

    return ret;
}

DBManager::DBManager(DBManagerConfig config, DTL::AGUHardwareStat *hwStat)
{
    
      
    m_dtlAPI = new DTL::API(hwStat);



    uint64_t size = 0x1000000UL;
    for (int i = 0;  i < config.tableCount; i++)
    {
        auto dummyTable = m_dtlAPI->AllocEphemeralRegion(size); // new DTL::EphemeralRegion(size*i, size, i, 0x170000000UL, hwStat);
        int* tableWrite  = (int*)dummyTable->GetHeadlessWriteregion();
        auto tableConf = config.tableConfigs[i];
        randomize_region_deterministic_int(tableWrite, size/sizeof(int));
        m_DummyRegions.push_back(dummyTable);
        m_TableConfigs.push_back(tableConf);
    }


}

std::string DBManager::RunQuerySplit(SplitQuery query) 
{
    PerfManager perf;
    std::string results;
    std::vector<std::string> filterViews;
    std::string selectionView;


    for (auto& t: query.filter)
        filterViews.push_back(TableView2Config(t));

    selectionView = TableView2Config(query.selection);


    std::vector<RegionView*> filterRegions;

    int a = 0 ;
    for (auto& f: query.filter)
    {
        auto region = m_dtlAPI->CloneEphemeralRegion(m_DummyRegions[f.table]);

        if (!m_dtlAPI->Compile(filterViews[a])) {
            printf("Failed to compile dtl program or map onto agu. View %d\n", a);
            return "Failed to compile dtl program or map onto agu\n";
        }
        m_dtlAPI->ProgramHardware(region);


        filterRegions.push_back(new RegionView(region, query.filter[a], m_TableConfigs[f.table], m_dtlAPI)); // wrap this in a class so we can incrementall read what we need
        a++;
    }


    auto selEphemeral = m_dtlAPI->CloneEphemeralRegion(m_DummyRegions[query.selection.table]);
        if (!m_dtlAPI->Compile(selectionView)) {
            printf("Failed to compile dtl program or map onto agu. View %d\n", a);
            return "Failed to compile dtl program or map onto agu\n";
        }
        m_dtlAPI->ProgramHardware(selEphemeral);

    RegionView* selectionRegion  = new RegionView(selEphemeral, query.selection, m_TableConfigs[query.selection.table], m_dtlAPI);
    auto selTable =  m_TableConfigs[query.selection.table];

    int* dataOut = new int[selectionRegion->MaxSize()];
   // std::vector<int> filterVals;
    bool write_out = true;
    int x = 0 ;
    perf.CollectCounters();
    for (int i = 0; i < selTable.rows; i++)
    {
         bool write_out = true;
        for (int j = 0; j < filterViews.size(); j++)
        {
             auto vector =  filterRegions[j]->ReadColumns();
             assert(vector.size() == query.filter[j].columns.size());
             //filterVals.insert(filterVals.end(), vector.begin(), vector.end());

             if (!query.filterFunc[j](vector)) // if we fail any condition
             {
                for (int l = j+1; l < filterViews.size(); l++)
                    filterRegions[l]->AdvanceN(query.filter[l].columns.size());
                selectionRegion->AdvanceN(query.selection.columns.size());
                write_out = false;
                break;
             }
        }

        if (write_out)
        {
            // dataOut[x++] =  selectionView->ReadCols();
            selectionRegion->ReadColumnsOut(&dataOut[x]);
            x += query.selection.columns.size();
        }


       // filterVals.clear();
    }
    perf.CollectDelta();
        printf("GOT X SPLIT %d\n", x);


    // Hash dataOut//
    std::string checksum = print_checksum_i32(dataOut, x);
    std::string queryInfo = SplitQuery2InfoString(query);


    results += queryInfo + "," + perf.PrintCounters() +  "," + checksum + "\n";


    delete selectionRegion; // this will also delete ephemeral
    for (auto& f: filterRegions)
        delete f;           // this will also delete ephemeral


    delete[] dataOut;

    return results;


}

std::string DBManager::RunQuery(Query query)
{
    PerfManager perf;
    std::string results;
    std::string view = TableView2Config(query.view);


    TableConfig tableConf = m_TableConfigs[query.view.table];
    DTL::EphemeralRegion* region = m_dtlAPI->CloneEphemeralRegion(m_DummyRegions[query.view.table]);
    if (!m_dtlAPI->Compile(view)) {
        printf("DBManager::RunQuery(Query query) --> Failed to compile dtl program or map onto agu.\n");
        return "Failed to compile dtl program or map onto agu\n";
    }
    m_dtlAPI->ProgramHardware(region);

    RegionView* region_view = new RegionView(region, query.view, tableConf, m_dtlAPI);

    int* dataOut = new int[(query.filterCols + query.selCols)*tableConf.rows];
    int x = 0;
   // std::vector<int> filterVals;
    perf.CollectCounters();
    for (int i = 0; i < tableConf.rows; i++)
    {

        auto vector =  region_view->ReadNColumns(query.filterCols);
        //filterVals.insert(filterVals.end(), vector.begin(), vector.end());
        bool flag = false;

        if (query.filterFunc(vector))
        {
            // dataOut[x++] =  selectionView->ReadCols();
            region_view->ReadNColumnsOut(&dataOut[x], query.selCols);
            x += query.selCols;
            flag = true;
        }



        if (!flag)
            region_view->AdvanceN(query.selCols);


        //filterVals.clear();
    }
    perf.CollectDelta();
        printf("GOT X BASE %d\n", x);


    // Hash dataOut//
    std::string checksum = print_checksum_i32(dataOut, x);
    std::string queryInfo = Query2InfoString(query);


    results += queryInfo + "," + perf.PrintCounters() +  "," + checksum + "\n";


    delete region_view;

    delete[] dataOut;

    return results;
}

std::string DBManager::TableView2Config(TableView t) 
{
    std::string conf;
    auto tableConf = m_TableConfigs[t.table];
    return CreateDTLConstants(t.columns, tableConf.col_count) + "\n" + InsertDTLConfigParameters(tableConf, t.columns.size());
}

RegionView::RegionView(DTL::EphemeralRegion *ephemeral, TableView view, TableConfig baseTableConf, DTL::API* api) : m_BaseTableConf(baseTableConf), m_View(view), \
    m_Loc(0), m_Ephemeral(ephemeral), m_API(api)
{
    m_ReadPtr  = (int*)ephemeral->GetHeadlessReadRegion();
}

RegionView::~RegionView()
{
    m_API->FreeEphemeralRegion(m_Ephemeral);
}

std::vector<int> RegionView::ReadColumns()
{
    std::vector<int> ret;
    for (int i = 0; i < m_View.columns.size(); i++)
        ret.push_back(m_ReadPtr[m_Loc++]);
    return ret;
}

void RegionView::ReadColumnsOut(int *out)
{
    int x  = 0;
    for (int i = 0; i < m_View.columns.size(); i++)
        out[x++] = m_ReadPtr[m_Loc++];
}

std::vector<int> RegionView::ReadNColumns(int n) 
{
    std::vector<int> ret;
    for (int i = 0; i < n; i++)
        ret.push_back(m_ReadPtr[m_Loc++]);
    return ret;
}

void RegionView::ReadNColumnsOut(int *out, int n)
{
    int x  = 0;
    for (int i = 0; i < n; i++)
        out[x++] = m_ReadPtr[m_Loc++];
}

void RegionView::AdvanceN(int n)
{
    m_Loc += n;
}

int RegionView::MaxSize() 
{
    return m_View.columns.size() * m_BaseTableConf.rows;
}
