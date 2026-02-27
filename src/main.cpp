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
        .filterFunc = {
                [](const std::vector<int>& i) -> bool { // 1

                    return (i[0] >= 0);
                },
                [](const std::vector<int>& i) -> bool {

                    return  (i[0] >= 0);
                },
                [](const std::vector<int>& i) -> bool {

                    return  (i[0] >= 0);
                },
                [](const std::vector<int>& i) -> bool {

                    return  (i[0] >= 0);
                },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}},
            {.table = 0, .columns = {C10}},
            {.table = 0, .columns = {C15}},
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        }
    },

    {
        .filterFunc = {
            [](const std::vector<int>& f) -> bool { // 1
                assert(f.size() == 4);
                return (f[0] >= 0) && (f[1] >= 0) && (f[2] >= 0) && (f[3] >= 0);
            },
        },
        .filter = {
            {.table = 0, .columns = {C3, C8, C10, C15}}, // 1
        },
        .projection = {
            .table = 0,
            .columns = {C5,C6,C10,C14}
        }
    },
    
    


};

std::vector<Query> baseQuery = {
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 4);
            return (f[0] >= 0) && (f[1] >= 0) && (f[2] >= 0) && (f[3] >= 0);
        },
        .filterCols = 4,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C10, C15, C5, C6, C10, C14}
        }
    }
};


int main()
{
    auto hwStat = new DTL::AGUHardwareStat(4, 4, 5, 6, 5, 4, 1, 1, 2);
    hwStat->nMaxConfigs = 8;
    auto manager =  new DBManager(globalConf, hwStat);
    PerfManager perf;

    std::cout << perf.PrintCountersLabel() << "\n";


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