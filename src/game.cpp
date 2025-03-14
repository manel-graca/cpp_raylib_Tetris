#include "game.hpp"
#include <cstdlib>
#include <raylib.h>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
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
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::Update()
{
    HandleInput();
}

Block Game::GetNextBlock()
{
    return nextBlock;
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
    case KEY_A:
    case KEY_LEFT:
        MoveBlockH(true);
        break;
    case KEY_D:
    case KEY_RIGHT:
        MoveBlockH(false);
        break;
    case KEY_S:
    case KEY_DOWN:
        MoveBlockDown();
        break;
    case KEY_W:
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

    int completed = grid.ClearFullRows();
    score += completed * 10;
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
