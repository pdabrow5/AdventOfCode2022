#include "task_8.h"

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdexcept>


std::deque<std::vector<int>> ReadMapFromFile(std::string filename) {
  std::fstream file;
  std::deque<std::vector<int>> map;

  file.open(
      filename,
      std::ios::in);  // open a file to perform read operation using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    while (getline(file, tp)) {
      size_t width = tp.size();
      std::vector<int> row(width);
      for (size_t i = 0; i < width; ++i) row[i] = tp[i] - '0';
      map.push_back(row);

    }
    file.close();
  }
  return map;
}

std::deque<std::vector<bool>> AnalyseVisibilityFromOutside(
    const std::deque<std::vector<int>>& map) {
  size_t height_of_map = map.size();
  size_t width_of_map = map[0].size();
  std::deque<std::vector<bool>> analysed_map(height_of_map,        //creates empty map in shape of rectangle filled with false value
                                             std::vector<bool>(width_of_map, false));
    for (size_t column = 0; column < width_of_map; ++column) {
        int shortest_up(-1), shortest_down(-1);
        for (size_t row = 0; row < height_of_map; ++row) {
            if (shortest_up < map[row][column]) {
                analysed_map[row][column] = true;
                shortest_up = map[row][column];
            }
            if (shortest_down < map[height_of_map - 1 -row][column]) {
                analysed_map[height_of_map - 1 -row][column] = true;
                shortest_down = map[height_of_map - 1 - row][column];
            }
        }
    }

    for (size_t row = 0; row < height_of_map; ++row) {
        int shortest_left(-1), shortest_right(-1);
        for (size_t column = 0; column < height_of_map; ++column) {
            if (shortest_left < map[row][column]) {
                analysed_map[row][column] = true;
                shortest_left = map[row][column];
            }
            if (shortest_right < map[row][width_of_map - 1 - column]) {
                analysed_map[row][width_of_map - 1 - column] = true;
                shortest_right = map[row][width_of_map - 1 - column];
            }
        }
    }


  return analysed_map;
}

size_t SumVisibleTrees(const std::deque<std::vector<bool>>& analysed_map) {
  size_t sum_of_visible_trees(0);
    
  for (auto i = analysed_map.cbegin(); i != analysed_map.cend(); i++)
    for (auto j = (*i).cbegin(); j != (*i).cend(); j++)
      if (*j) ++sum_of_visible_trees;

  return sum_of_visible_trees;
}

int AnalyseViewFromTree(const std::deque<std::vector<int>>& map, size_t row,
                           size_t column) {

  
  int sum_of_visible_trees = 0;
  int scenic_score = 1;
  size_t height = map.size();
  size_t width = map[0].size();
  int considered_tree = map[row][column];
  if (row >= height) throw std::invalid_argument("Row out of map range");
  if (column >= width) throw std::invalid_argument("Column out of map range");

  for (int r = row - 1; r >= 0; --r) { //up
    ++sum_of_visible_trees;
    if (considered_tree <= map[r][column])
      break;
  }
  scenic_score *= sum_of_visible_trees;
  sum_of_visible_trees = 0;
  for (int r = row + 1; r < height; ++r) { //down
    ++sum_of_visible_trees;
    if (considered_tree <= map[r][column])
      break;
  }
  scenic_score *= sum_of_visible_trees;
  sum_of_visible_trees = 0;
  for (int c = column - 1; c >= 0; --c) { //left
    ++sum_of_visible_trees;
    if (considered_tree <= map[row][c]) 
      break;
  }
  scenic_score *= sum_of_visible_trees;
  sum_of_visible_trees = 0;
  for (int c = column + 1; c < width; ++c) { //right
    ++sum_of_visible_trees;
    if (considered_tree <= map[row][c])
      break;
  }
  scenic_score *= sum_of_visible_trees;
  return scenic_score;
}

int MaxViewFromTree(const std::deque<std::vector<int>>& map) {
  int highest_score = 0;
  int considered_row(0), considered_column(0);
  size_t height = map.size();
  size_t width = map[0].size();

  for (size_t row = 0; row != height; ++row)
    for (size_t column = 0; column != width; ++column) {
      int view_from_tree = AnalyseViewFromTree(map, row, column);
      if (view_from_tree > highest_score) highest_score = view_from_tree;
    }
      

  return highest_score;
}
