#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility>

class Snake
{
public:
    Snake(int startX, int startY);
    void move(char direction);
    void grow();
    bool checkCollision(int boardWidth, int boardHeight);
    std::vector<std::pair<int, int>> getSegments();

private:
    std::vector<std::pair<int, int>> segments;
    char currentDirection;
};

#endif // SNAKE_H
#pragma once
