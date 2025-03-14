#include "block.hpp"
#include "colors.h"
#include "gameConfig.hpp"
Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(offsetX + item.column * cellSize, offsetY + item.row * cellSize, cellSize - 1, cellSize - 1, colors[id]);
    }
}

int Block ::Rotate()
{
    rotationState = (rotationState + 1) % cells.size();
    return rotationState;
}

int Block::UndoRotation()
{
    rotationState = (rotationState - 1) % cells.size();
    return rotationState;
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;

    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}