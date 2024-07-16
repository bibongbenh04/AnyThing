#include "GameBoard.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

int main()
{
    GameBoard game(30, 30);

    char direction = 'R';

    while (true)
    {
        if (_kbhit())
        {
            direction = _getch();
        }

        if (!game.update(direction))
        {
            std::cout << "Game Over!" << std::endl;
            break;
        }
        game.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        system("cls");

    }

    return 0;
}
