#include "game.hpp"
#include <raylib.h>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    int randomIndex = GetRandomValue(0, blocks.size() - 1);
    if (randomIndex < 0)
        randomIndex = 0;

    if (randomIndex >= blocks.size())
        randomIndex = blocks.size() - 1;

    Block block = blocks[randomIndex];
    currentBlock = block;
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {LBlock(), IBlock(), JBlock(), SBlock(), ZBlock(), OBlock(), TBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}

void Game::Update()
{
    HandleInput();
}

void Game::HandleInput()
{
    int key = GetKeyPressed();
    if (gameOver && key != 0)
    {
        gameOver = false;
        Reset();
    }
    switch (key)
    {
    case KEY_LEFT:
        MoveBlockH(true);
        break;
    case KEY_RIGHT:
        MoveBlockH(false);
        break;
    case KEY_DOWN:
        MoveBlockDown();
        break;
    case KEY_UP:

        if (gameOver)
            break;

        currentBlock.Rotate();
        if (IsBlockOutside(currentBlock) || !BlockFits())
        {
            currentBlock.UndoRotation();
        }
        break;
    }
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

void Game::MoveBlockH(bool isLeft)
{
    if (gameOver)
        return;

    int direction = isLeft ? -1 : 1;
    currentBlock.Move(0, direction);
    if (IsBlockOutside(currentBlock) || !BlockFits())
    {
        currentBlock.Move(0, -direction);
    }
}

void Game::MoveBlockDown()
{
    if (gameOver)
        return;

    currentBlock.Move(1, 0);
    if (IsBlockOutside(currentBlock) || !BlockFits())
    {
        currentBlock.Move(-1, 0);
        LockBlock();
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;

    if (!BlockFits())
    {
        gameOver = true;
        return;
    }

    nextBlock = GetRandomBlock();

    grid.ClearFullRows();
}

bool Game::IsBlockOutside(Block block)
{
    std::vector<Position> cellPositions = block.GetCellPositions();
    for (const Position &pos : cellPositions)
    {
        if (grid.IsCellOutside(pos.row, pos.column))
        {
            return true;
        }
    }
    return false;
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (const Position &pos : tiles)
    {
        if (!grid.IsCellEmpty(pos.row, pos.column))
        {
            return false;
        }
    }
    return true;
}
