#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Snake.h"
#include "Food.h"
#include <memory>

class GameBoard
{
public:
    GameBoard(int width, int height);
    void display();
    bool update(char direction);
    void generateFood();
    void generateSpecialFood();

private:
    int width;
    int height;
    Snake snake;
    std::unique_ptr<Food> food;
    std::unique_ptr<Food> specialFood;
    int score;
};

#endif // GAMEBOARD_H
