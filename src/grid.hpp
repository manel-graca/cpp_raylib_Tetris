#pragma once
#include <raylib.h>
#include <vector>

class Grid
{
  public:
    Grid();
    void Initialize();
    void Draw();
    void PrintToConsole();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int grid[20][10];

  private:
    void MoveRowDown(int row, int numRows);
    void ClearRow(int row);
    bool IsRowFull(int row);
    std::vector<Color> colors;
    int numRows;
    int numCols;
    int cellSize;
};