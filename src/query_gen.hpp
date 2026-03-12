#ifndef QUERY_GEN_HPP
#define QUERY_GEN_HPP




#include <vector>
#include <string>
#include <functional>
#include "manager.hpp"


inline int GetSelectivityValue(float sel);
std::function<bool(const std::vector<int>&)> GenPredicate(std::vector<float>& selectivity);
std::string GetLabelFromSelectivityVec(std::vector<std::vector<float>> filterSelectivity);
SplitQuery genSplitQuery(std::vector<std::vector<uint32_t>> filterCols, std::vector<std::vector<float>> filterSelectivity,\
                             std::vector<uint32_t> projCols);
Query genQuery(std::vector<std::vector<uint32_t>> filterCols, std::vector<std::vector<float>> filterSelectivity,\
                             std::vector<uint32_t> projCols);





#endif