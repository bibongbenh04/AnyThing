#include "GameBoard.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GameBoard::GameBoard(int width, int height) : width(width), height(height), snake(width / 2, height / 2), score(0)
{
    std::srand(std::time(0));
    generateFood();
}

void GameBoard::display()
{
    std::vector<std::vector<char>> board(height, std::vector<char>(width, ' '));

    for (const auto &segment : snake.getSegments())
    {
        board[segment.second][segment.first] = 'O';
    }

    board[food->getY()][food->getX()] = 'F';

    if (specialFood)
    {
        board[specialFood->getY()][specialFood->getX()] = 'S';
    }

    for (const auto &row : board)
    {
        for (char cell : row)
        {
            std::cout << cell;
        }
        std::cout << std::endl;
    }

    std::cout << "Score: " << score << std::endl;
}

bool GameBoard::update(char direction)
{
    snake.move(direction);

    if (snake.checkCollision(width, height))
    {
        return false;
    }

    std::pair<int, int> head = snake.getSegments()[0];

    if (head.first == food->getX() && head.second == food->getY())
    {
        snake.grow();
        score += food->getScore();
        generateFood();
    }

    if (specialFood && head.first == specialFood->getX() && head.second == specialFood->getY())
    {
        snake.grow();
        score += specialFood->getScore();
        specialFood.reset();
    }

    return true;
}

void GameBoard::generateFood()
{
    int x = std::rand() % width;
    int y = std::rand() % height;
    food = std::make_unique<Food>(x, y);
}

void GameBoard::generateSpecialFood()
{
    int x = std::rand() % width;
    int y = std::rand() % height;
    specialFood = std::make_unique<SpecialFood>(x, y);
}
