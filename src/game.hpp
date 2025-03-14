#pragma once
#include "block.hpp"
#include "blocks.cpp"
#include "grid.hpp"

class Game
{
  public:
    bool gameOver;
    Game();
    Grid grid;
    Block GetRandomBlock();
    void Draw();
    void Update();
    void MoveBlockDown();
    int score;
    Block GetNextBlock();

  private:
    bool IsBlockOutside(Block block);
    std::vector<Block>
        blocks;
    Block currentBlock;
    Block nextBlock;
    std::vector<Block> GetAllBlocks();
    void HandleInput();
    void MoveBlockH(bool left);
    void LockBlock();
    bool BlockFits();
    void Reset();
};