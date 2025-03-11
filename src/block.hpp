#pragma once
#include "position.hpp"
#include <map>
#include <vector>

class Block
{
  public:
    Block();
    int id;
    void Draw();
    std::map<int, std::vector<Position>> cells;
    int Rotate();
    int UndoRotation();
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();

  private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};