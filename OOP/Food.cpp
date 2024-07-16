#include "Food.h"

Food::Food(int x, int y) : x(x), y(y) {}

int Food::getX()
{
    return x;
}

int Food::getY()
{
    return y;
}

int Food::getScore() const
{
    return 10; // Regular food score
}

SpecialFood::SpecialFood(int x, int y) : Food(x, y) {}

int SpecialFood::getScore() const
{
    return 20; // Special food score
}
