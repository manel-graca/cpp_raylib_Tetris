#pragma once
#include <raylib.h>

class Position
{
  public:
    Position(int row, int column);
    int row;
    int column;
};