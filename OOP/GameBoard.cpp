#include "GameBoard.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

GameBoard::GameBoard(int width, int height) : width(width), height(height), snake(width / 2, height / 2), score(0)
{
    std::srand(std::time(0));
    generateFood();
}

void GameBoard::display()
{
    std::vector<std::vector<std::string>> board(height+1, std::vector<std::string>(width+1, " "));

    for (const auto& segment : snake.getSegments())
    {
        board[segment.second][segment.first] = 'O';
    }
    board[snake.getSegments()[0].second][snake.getSegments()[0].first] = 'X';
    board[food->getY()][food->getX()] = "F";

    if (specialFood)
    {
        board[specialFood->getY()][specialFood->getX()] = "S";
    }
    for (int i = 0; i <= height; ++i) {
        board[i][0] = "*";
        board[i][width] = "*";
    }
    for (int i = 0; i <= width; ++i) {
        board[0][i] = "*";
        board[height][i] = "*";
    }
    for (const auto& row : board)
    {
        for (std::string cell : row)
        {
            std::cout << cell << " ";
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
    int x = std::rand() % (width+1);
    int y = std::rand() % (height+1);
    food = std::make_unique<Food>(x, y);
}

void GameBoard::generateSpecialFood()
{
    int x = std::rand() % (width + 1);
    int y = std::rand() % (height + 1);
    specialFood = std::make_unique<SpecialFood>(x, y);
}
