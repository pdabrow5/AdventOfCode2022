#pragma once

#include<string>
#include<vector>
#include<deque>


std::deque<std::vector<int>> ReadMapFromFile(std::string filename);

std::deque<std::vector<bool>> AnalyseVisibilityFromOutside(
    const std::deque<std::vector<int>> &map);
size_t SumVisibleTrees(const std::deque<std::vector<bool>> &analysed_map);

int AnalyseViewFromTree(const std::deque<std::vector<int>> &map, size_t row,
                           size_t column);
int MaxViewFromTree(const std::deque<std::vector<int>> &map);