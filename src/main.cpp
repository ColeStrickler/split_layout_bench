#include "manager.hpp"





static DBManagerConfig globalConf = {
    .tableCount = 1,
    .tableConfigs = {
        {
            .rows  = 43690,
            .col_count = 16,
            .col_size = 4,
        },
    }
};



std::vector<SplitQuery> splitQuery = {
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 4);
            return (f[0] < 256) && (f[1] > 64) && (f[2] % 2 == 0) && (f[3] > 128);
        },
        .filter = {
            {.table = 0, .columns = {C3}},
            {.table = 0, .columns = {C8}},
            {.table = 0, .columns = {C10}},
            {.table = 0, .columns = {C5}},
        },
        .selection = {
            .table = 0,
            .columns = {C5,C6,C10,C14}
        }
    },
};

std::vector<Query> baseQuery = {
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 4);
            return (f[0] < 256) && (f[1] > 64) && (f[2] % 2 == 0) && (f[3] > 128);
        },
        .filterCols = 4,
        .selCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C10, C15, C5, C6, C10, C14}
        }
    }
};


int main()
{
    auto hwStat = new DTL::AGUHardwareStat(4, 4, 5, 6, 5, 4, 1, 1, 2);
    auto manager =  new DBManager(globalConf, hwStat);



    for (auto& query: splitQuery)
    {
        std::cout << manager->RunQuerySplit(query) << "\n";
    }


    for (auto& query: baseQuery)
    {
        std::cout << manager->RunQuery(query) << "\n";
    }


    return 0;
}