#include "manager.hpp"

#include "query_gen.hpp"


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
                return (i[0] < 410);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "10%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 820);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "20%"
    },
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 1229);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "30%"
    },
    
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 1639);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "40%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 2048);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "50%"
    },
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 2458);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "60%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 2868);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "70%"
    },
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 3277);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "80%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 3687);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "90%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "100%"
    },




     {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 410);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },

        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "10%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 820);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "20%"
    },
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 1229);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "30%"
    },
    
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 1639);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "40%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 2048);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "50%"
    },
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 2458);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "60%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 2868);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "70%"
    },
    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 3277);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "80%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] < 3687);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "90%"
    },

    {
        .filterFunc = {
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
            [](const std::vector<int>& i) -> bool { // 1
                return (i[0] >= 0);
            },
        },
        .filter = { // selection
            {.table = 0, .columns = {C3}}, // 1
            {.table = 0, .columns = {C8}}, 
        },
        .projection = { // projection
            .table = 0,
            .columns = {C5,C6,C10,C14}
        },
        "100%"
    }




};

std::vector<Query> baseQuery = {
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 410);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "10%"
    },  
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 820);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "20%"
    },        
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 1229);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "30%"
    },    
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 1639);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "40%"
    },    
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 2048);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "50%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 2458);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "60%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 2868);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "70%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 3277);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "80%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] < 3687);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "90%"
    },

    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 1);
            return (f[0] >= 0);
        },
        .filterCols = 1,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C5, C6, C10, C14}
        },
        "100%"
    },


     {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 410 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "10%"
    },  
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 820 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "20%"
    },        
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 1229 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "30%"
    },    
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 1639 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3,C8, C5, C6, C10, C14}
        },
        "40%"
    },    
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 2048 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "50%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 2458 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "60%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 2868 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "70%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 3277 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "80%"
    },
    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] < 3687 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3, C8, C5, C6, C10, C14}
        },
        "90%"
    },

    {
        .filterFunc = [](const std::vector<int>& f) -> bool {
            assert(f.size() == 2);
            return (f[0] >= 0 && f[1] >= 0);
        },
        .filterCols = 2,
        .projCols = 4,
        .view = {
            .table = 0,
            .columns = {C3,C8, C5, C6, C10, C14}
        },
        "100%"
    }


};


int main()
{
	auto hwStat = new DTL::AGUHardwareStat({ // (nAdd, nMult, nSUb, nPassThru) 
		{2,4,2,4},
		{2,2,1,4},
		{2,2,1,2},
		{1,1,1,2},
		{1,1,1,1},
		{0,0,0,1},
	}, 5, 6, 5, 1, 1, 2);
  hwStat->nMaxConfigs = 8;
  
    auto manager =  new DBManager(globalConf, hwStat);
    PerfManager perf;

    std::cout << perf.PrintCountersLabel() << "\n";

    std::string bench_res;



    for (float f1 = 0.01; f1 <= 1.00; f1 += 0.01)
    {
        for (float f2 = 0.01; f2 <= 1.00; f2 += 0.01)
        {
            for (float f3 = 0.01; f3 <= 1.00; f3 += 0.01)
            {
                for (float f4 = 0.01; f4 <= 1.00; f4 += 0.01)
                {
                    auto sq = genSplitQuery({{C3},{C5},{C10}, {C13}}, {{f1},{f2},{f3}, {f4}}, {C5, C6, C10, C14});
                    auto bq = genQuery({{C3},{C5},{C10}, {C13}}, {{f1},{f2},{f3}, {f4}}, {C5, C6, C10, C14});

                    bench_res += manager->RunQuerySplit(sq);
                    bench_res += manager->RunQuery(bq);
                    bench_res += manager->RunQueryCPU(bq);



                }
            }
        }
    }



    //for (auto& query: splitQuery)
    //{
    //    std::cout << manager->RunQuerySplit(query) << "\n";
    //}
    //for (auto& query: baseQuery)
    //{
    //    std::cout << manager->RunQuery(query) << "\n";
    //    std::cout << manager->RunQueryCPU(query) << "\n";
    //}


    return 0;
}