#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "dtl_api.hpp"
#include "util.hpp"
#include "perf.hpp"
#include <vector>
#include <string>
#include <functional>

#define C1 1
#define C2 2
#define C3 3
#define C4 4
#define C5 5
#define C6 6
#define C7 7 
#define C8 8
#define C9 9
#define C10 10
#define C11 11
#define C12 12
#define C13 13
#define C14 14
#define C15 15
#define C16 16


const std::string proj_stencil = R"(
    for (int i = 0; i < [ROWS]; i++)
    {
        for (int j = 0; j < [COLUMNS]; j++)
        {
            out = i*row_size + col_offsets[j];
        }
    }
)";




struct TableView
{
    int table;
    std::vector<uint32_t> columns;
};

struct TableConfig
{
    int rows;
    int col_count;
    int col_size;
};
std::string InsertDTLConfigParameters(TableConfig tableConf);
std::string CreateDTLConstants(std::vector<uint32_t> columns, int row_size);

struct SplitQuery
{
    std::function<bool(const std::vector<int>& f)> filterFunc;
    std::vector<TableView> filter;
    TableView selection;
};

struct Query
{
    std::function<bool(const std::vector<int>& f)> filterFunc;;
    int filterCols; // We will always place the filter columns first
    int selCols;    // selection columns come immediately after
    TableView view;
};


std::string SplitQuery2InfoString(SplitQuery query);
std::string Query2InfoString(Query query);



struct DBManagerConfig
{
    int tableCount;
    std::vector<TableConfig> tableConfigs;
};



class RegionView
{
public:
    RegionView(DTL::EphemeralRegion* ephemeral, TableView view, TableConfig baseTableConf);
    ~RegionView();
    std::vector<int> ReadColumns();
    void ReadColumnsOut(int* out);
    std::vector<int> ReadNColumns(int n);
    void ReadNColumnsOut(int* out, int n);
    void AdvanceN(int n);
    int MaxSize();

private:
    int m_Loc;
    TableView m_View;
    TableConfig m_BaseTableConf;
    int* m_ReadPtr;
    DTL::EphemeralRegion* m_Ephemeral;
};



class DBManager
{
public:
    DBManager(DBManagerConfig config, DTL::AGUHardwareStat* hwStat);
    ~DBManager();
    std::string RunQuerySplit(SplitQuery query);
    std::string RunQuery(Query query);
    std::string TableView2Config(TableView t);
private:
    std::vector<TableConfig> m_TableConfigs;
    DTL::API* m_dtlAPI;
    std::vector<DTL::EphemeralRegion*> m_DummyRegions; //These regions are not allocated a config, they are just used to manage tables

};









#endif