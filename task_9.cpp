#include "task_9.h"
#include<sstream>
#include<fstream>
#include<iostream>
#include<map>
#include<stdexcept>



std::vector<std::tuple<char, unsigned int>>
LoadMovesSequence(
    std::string filename) {
  std::fstream file;
  std::vector<std::tuple<char, unsigned int>> moves_sequence;
  file.open(filename, std::ios::in);  // open a file to perform read operation
                                      // using file object
  if (file.is_open()) {  // checking whether the file is open
    std::string tp;
    while (getline(file, tp)) {
      unsigned int distance;
      char direction;
      std::stringstream ss;
      ss << tp;
      ss >> direction >> distance;

      if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R')
        throw(std::invalid_argument("Wrong moves sequence file. Direction must not be other than U, D, R, L"));

      moves_sequence.push_back(std::make_tuple(direction, distance));
    }
    file.close();
  }
  return moves_sequence;
}

std::tuple<size_t, size_t, RopeBridge::Coordinates> CalculateMapSize(
    const std::vector<std::tuple<char, unsigned int>>
        &moves_sequence) {  // coordinates tells where to put 
  int left_columns = 0;                                                  // bridge at first move to fit it perfectly in map
  int right_columns = 0;
  int up_columns = 0;
  int down_columns = 0;
  int position_x = 0;
  int position_y = 0;
  
  for (auto i = moves_sequence.cbegin(); i != moves_sequence.cend(); ++i) {
    switch (std::get<0>(*i)) {
      case 'U':
        position_y -= std::get<1>(*i);
        if (-position_y > up_columns) up_columns = -position_y;
        break;
      case 'D':
        position_y += std::get<1>(*i);
        if (position_y > down_columns) down_columns = position_y;
        break;
      case 'L':
        position_x -= std::get<1>(*i);
        if (-position_x > left_columns) left_columns = -position_x;
        break;
      case 'R':
        position_x += std::get<1>(*i);
        if (position_x > right_columns) right_columns = position_x;
        break;
    }
    //std::cout <<std::get<0>(*i)<< " " << std::get<1>(*i)<< "  pos: " << position_y << ", " << position_x << std::endl; 

  }

  size_t width = left_columns + right_columns + 1;
  size_t height = up_columns + down_columns + 1;
  RopeBridge::Coordinates coordinates;
  coordinates.y = up_columns;
  coordinates.x = left_columns;
  return std::make_tuple(height, width, coordinates);
}

void task9_1(std::string filename) {
  auto seq = LoadMovesSequence(filename);
  auto m = CalculateMapSize(seq);
  RopeBridge head(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  for (auto move = seq.cbegin(); move != seq.cend(); ++move)
    head.MoveHeadOfBridge(*move);
  std::cout << std::endl << head.CountVisitedByLast() << std::endl;
}

void task9_2(std::string filename) {
  auto seq = LoadMovesSequence(filename);
  auto m = CalculateMapSize(seq);
  RopeBridge head(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  head.AddTail(std::get<0>(m), std::get<1>(m), std::get<2>(m));
  for (auto move = seq.cbegin(); move != seq.cend(); ++move)
    head.MoveHeadOfBridge(*move);
  std::cout << std::endl << head.CountVisitedByLast() << std::endl;
}

RopeBridge::RopeBridge(size_t height_of_map, size_t width_of_map,
                      const RopeBridge::Coordinates &start_position) {
  map_of_positions = std::vector<std::vector<bool>>(height_of_map, std::vector<bool>(width_of_map, false));
  map_of_positions[start_position.y][start_position.x] = true;
  _head = start_position;
  _tail = start_position;
  _coord = start_position;
}

void RopeBridge::MoveHeadOfBridge(const std::tuple<char, unsigned int> &move) {
  switch (std::get<0>(move)) {
    case 'U':
      _coord.y -= std::get<1>(move);
      break;
    case 'D':
      _coord.y += std::get<1>(move);
      break;
    case 'L':
      _coord.x -= std::get<1>(move);
      break;
    case 'R':
      _coord.x += std::get<1>(move);
      break;
  }
  TailFollowsHead();
}
void RopeBridge::MoveHeadOfBridge(const Coordinates &move) {

  _coord = _coord + move;
  TailFollowsHead();
}

unsigned int RopeBridge::CountVisitedCells() const { 
  unsigned int counter = 0;
  for (auto row = map_of_positions.cbegin(); row != map_of_positions.cend();
       ++row) {
    for (auto elem_in_row = (*row).cbegin(); elem_in_row != (*row).cend();
         ++elem_in_row)
      if (*elem_in_row) ++counter;
  }
  return counter;
}

void RopeBridge::ShowMap() {
  std::string map_as_str;
  for (auto row = map_of_positions.cbegin(); row != map_of_positions.cend(); ++row) {
    for (auto elem_in_row = (*row).cbegin(); elem_in_row != (*row).cend(); ++elem_in_row)
      if (*elem_in_row)
        map_as_str.push_back('X');
      else
        map_as_str.push_back('O');
    map_as_str += "\n";
  }
  std::cout << map_as_str;

  if (map_of_positions[_head.y][_head.x])
    std::cout << _head.y << " " << _head.x;
 }

RopeBridge::Coordinates RopeBridge::CalculateStepOfTail() {
  Coordinates one_step = Coordinates{0,0};
  if (_tail_node) one_step = _coord - _tail_node->_coord;

  //Calculate one step of a tail to follow the head
  if (one_step.x != 0)
    one_step.x = one_step.x / abs(one_step.x);
  if (one_step.y != 0)
    one_step.y = one_step.y / abs(one_step.y);
  return one_step;
}

void RopeBridge::TailFollowsHead() {

  if (_tail_node)
    while (abs(_coord.y - _tail_node->_coord.y) > 1 ||
           abs(_coord.x - _tail_node->_coord.x) > 1) {
     _tail_node->MoveHeadOfBridge(CalculateStepOfTail());
      _tail_node->map_of_positions[_tail_node->_coord.y][_tail_node->_coord.x] = true;
  }
}

RopeBridge::Coordinates RopeBridge::Coordinates::operator+(const Coordinates &cord) {
  Coordinates result;
  result.x = cord.x + this->x;
  result.y = cord.y + this->y;
  return result;
}

RopeBridge::Coordinates RopeBridge::Coordinates::operator-(const Coordinates &cord) {
  Coordinates result;
  result.x = this->x - cord.x;
  result.y = this->y - cord.y;
  return result;
}
