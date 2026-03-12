
#include "query_gen.hpp"



inline int GetSelectivityValue(float sel)
{
    return static_cast<int>(sel * 4096);
}

std::function<bool(const std::vector<int>&)> GenPredicate(std::vector<float>& selectivity) {
    std::vector<std::function<bool(const std::vector<int>&)>> preds;

    int x = 0;
    for (auto& sel: selectivity)
    {
        preds.push_back([sel, x](const std::vector<int>& r) { return r[x] < GetSelectivityValue(sel); });
        x++;
    }


    return [preds](const std::vector<int>& row) {
        assert(row.size() <= preds.size());
        for (const auto& p: preds) {
            if (!p(row)) {
                return false;
            }
        }
        return true;
    };
}


std::string GetLabelFromSelectivityVec(std::vector<std::vector<float>> filterSelectivity) {
    std::string ret;
    for (auto& s: filterSelectivity)
    {
        for(auto& percent: s)
        {
            ret += std::to_string(percent*100) + ",";
        }
        ret += "_";
    }

    return ret;
}


// assuming all one table for now
SplitQuery genSplitQuery(std::vector<std::vector<uint32_t>> filterCols, std::vector<std::vector<float>> filterSelectivity,\
                             std::vector<uint32_t> projCols) {
    SplitQuery Ret;
    

    for (auto filterView: filterCols)
    {
       TableView tableView{.table = 0, .columns = filterView};
       Ret.filter.push_back(tableView);
    }
    
    TableView projTableView{.table = 0, .columns = projCols};
    Ret.projection = projTableView;


    for (auto& selectivity_vec: filterSelectivity)
    {
        auto pred = GenPredicate(selectivity_vec);
        Ret.filterFunc.push_back(pred);
    }

    std::string label = GetLabelFromSelectivityVec(filterSelectivity);

    return Ret;

}


Query genQuery(std::vector<std::vector<uint32_t>> filterCols, std::vector<std::vector<float>> filterSelectivity,\
                             std::vector<uint32_t> projCols)
{
    Query ret;
    std::vector<uint32_t> cols;
    std::vector<float> selectivity;
    
     // We insert all the columns into a single view here. We just keep this format so we can use the same data 
     // format as the genSplitQuery() function
    for (auto& col: filterCols)
        cols.insert(cols.end(), col.begin(), col.end());

    for(auto& sel: filterSelectivity) // we do the same with the filter selectivity values
        selectivity.insert(selectivity.end(), sel.begin(), sel.end());

    assert(cols.size() == selectivity.size()); 

    ret.filterCols = cols.size();
    ret.projCols = projCols.size();
    cols.insert(cols.end(), projCols.begin(), projCols.end());
    ret.view = TableView{.table = 0, .columns=cols};
    ret.filterFunc = GenPredicate(selectivity);
    ret.label = GetLabelFromSelectivityVec({selectivity});

    return ret;
}