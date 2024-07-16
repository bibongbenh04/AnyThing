#ifndef FOOD_H
#define FOOD_H

class Food
{
public:
    Food(int x, int y);
    virtual ~Food() = default;
    int getX();
    int getY();
    virtual int getScore() const;

protected:
    int x;
    int y;
};

class SpecialFood : public Food
{
public:
    SpecialFood(int x, int y);
    int getScore() const override;
};

#endif // FOOD_H
#pragma once
