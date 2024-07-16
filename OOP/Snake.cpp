#include "Snake.h"

Snake::Snake(int startX, int startY)
{
    segments.push_back({ startX, startY });
    currentDirection = 'R';
}

void Snake::move(char direction)
{
    currentDirection = direction;
    std::pair<int, int> head = segments[0];

    switch (currentDirection)
    {
    case 'W':
    case 'w':
        head.second -= 1;
        break;
    case 'S':
    case 's':
        head.second += 1;
        break;
    case 'A':
    case 'a':
        head.first -= 1;
        break;
    case 'D':
    case 'd':
        head.first += 1;
        break;
    }

    segments.insert(segments.begin(), head);
    segments.pop_back();
}

void Snake::grow()
{
    segments.push_back(segments.back());
}

bool Snake::checkCollision(int boardWidth, int boardHeight)
{
    std::pair<int, int> head = segments[0];

    if (head.first < 0 || head.first >= boardWidth || head.second < 0 || head.second >= boardHeight)
        return true;

    for (size_t i = 1; i < segments.size(); ++i)
    {
        if (head == segments[i])
            return true;
    }

    return false;
}

std::vector<std::pair<int, int>> Snake::getSegments()
{
    return segments;
}
