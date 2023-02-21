#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <memory>



class RopeBridge {
 public:
  enum DirectionOfMove {Up, Down, Left, Right};
  struct Coordinates {
    int x;
    int y;
    Coordinates operator+(const Coordinates &cord);
    Coordinates operator-(const Coordinates &cord);


  };
  RopeBridge(size_t height_of_map, size_t width_of_map,
             const RopeBridge::Coordinates &start_position);
  void MoveHeadOfBridge(const std::tuple<char, unsigned int> &move);
  void MoveHeadOfBridge(const Coordinates &move);
  unsigned int CountVisitedCells() const;

  unsigned int CountVisitedByLast() const{
    if (!_tail_node)
      return CountVisitedCells();
    else
      return _tail_node->CountVisitedByLast();
  }
  void ShowMap();
  void AddTail(size_t height_of_map, size_t width_of_map,
               const RopeBridge::Coordinates &start_position) {
    if (!_tail_node)
      _tail_node = std::make_unique<RopeBridge>(height_of_map, width_of_map,
                                                start_position);
    else
      _tail_node->AddTail(height_of_map, width_of_map, start_position);
  }
  std::unique_ptr<RopeBridge> _tail_node;
 private:
  Coordinates _head, _tail, _coord;
  Coordinates _position;

  std::vector<std::vector<bool>> map_of_positions;
  Coordinates CalculateStepOfTail();
  void TailFollowsHead();
};

std::vector<std::tuple<char, unsigned int>> LoadMovesSequence(
    std::string filename);


std::tuple<size_t, size_t, RopeBridge::Coordinates> CalculateMapSize(
    const std::vector<std::tuple<char, unsigned int>>
        &moves_sequence);

void task9_1(std::string filename);
void task9_2(std::string filename);
