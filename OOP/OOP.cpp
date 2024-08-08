#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    //Đen: 0; Xanh Navy : 1, 9; Xanh Lá Cây : 2; Xanh Biển Đậm : 3
    //Đỏ : 4; Tím : 5, 13; Cam : 6; Xám Đậm : 8 9?
    //Xanh Lá Cây Đậm : 10; Xanh Biển : 11; Hồng : 12
    //Vàng : 14; Trắng : 15
    // 15++ màu có thêm nền, 14 đẹp cực

    /*FOREGROUND_BLACK: Màu đen
    FOREGROUND_BLUE : Màu xanh navy
    FOREGROUND_GREEN : Màu xanh lá cây
    FOREGROUND_CYAN : Màu xanh biển
    FOREGROUND_RED : Màu đỏ
    FOREGROUND_MAGENTA : Màu tím
    FOREGROUND_YELLOW : Màu cam
    FOREGROUND_INTENSITY : Tăng độ sáng của màu
    BACKGROUND_BLACK : Nền đen
    BACKGROUND_BLUE : Nền xanh navy
    BACKGROUND_GREEN : Nền xanh lá cây
    BACKGROUND_CYAN : Nền xanh biển
    BACKGROUND_RED : Nền đỏ
    BACKGROUND_MAGENTA : Nền tím
    BACKGROUND_YELLOW : Nền cam
    BACKGROUND_INTENSITY : Tăng độ sáng của nền*/
}

class Tile {
protected:
    int value;  // Giá trị của ô

public:
    Tile(int v = 0) : value(v) {}

    virtual int getValue() const {
        return value;
    }

    virtual bool canMergeWith(const Tile& other) const {
        return value == other.value;
    }

    virtual void merge(Tile& other) {
        if (canMergeWith(other)) {
            value += other.value;
            other.value = 0;
        }
        if (value == -999 * 2) {
            value = 9999;
        }
        if (value == -2) {
            value = (rand() % 3 == 1 ? 512 : 256);
        }
    }

    virtual void printTile() const {

        if (value == 0) {
            std::cout << ".";
        }
        else {
            if (value == 2) {
                setColor(1);
            }
            else if(value == 4) {
                setColor(3);
            } 
            else if (value == 8) {
                setColor(4);
            }
            else if (value == 16) {
                setColor(5);
            }
            else if (value == 32) {
                setColor(6);
            }
            else if (value == 64) {
                setColor(7);
            } 
            else if (value == 128) {
                setColor(8);
            }
            else if (value == 256) {
                setColor(9);
            }
            else if (value == 512) {
                setColor(10);
            }
            else if (value == 1024) {
                setColor(11);
            }
            else if (value == 2048) {
                setColor(12);
            }
            std::cout << value;
            setColor(2);
        }
    }
};

class TileWithLetter : public Tile {
public:
    TileWithLetter(int v = 0) : Tile(v) {}

    char getLetter() const {
        return 'A' + (value / 2 - 1);  // Ví dụ: 2 -> 'A', 4 -> 'B'
    }

    void printTile() const override {
        if (value == 0) {
            std::cout << ".";
        }
        else {
            if (value == 2) {
                setColor(1);
            }
            std::cout << getLetter();
            setColor(2);
        }
    }
};

class Board {
protected:
    int size;
    int score;  // Thêm biến lưu điểm số
    std::vector<std::vector<Tile*>> grid;

public:
    Board(int s = 4) : size(s), score(0), grid(s, std::vector<Tile*>(s)) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j] = new Tile();
            }
        }
    }

    int getScore() const {
        return score;
    }
    void changeScore(int s) {
        score += s;
    }
    virtual ~Board() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                delete grid[i][j];
            }
        }
    }

    void moveUp() {
        for (int col = 0; col < size; ++col) {
            for (int row = 1; row < size; ++row) {
                if (grid[row][col]->getValue() != 0) {
                    int targetRow = row - 1;
                    while (targetRow >= 0 && grid[targetRow][col]->getValue() == 0) {
                        targetRow--;
                    }
                    targetRow++;
                    if (targetRow != row) {
                        std::swap(grid[targetRow][col], grid[row][col]);
                    }
                    if (targetRow > 0 && grid[targetRow][col]->canMergeWith(*grid[targetRow - 1][col])) {
                        grid[targetRow - 1][col]->merge(*grid[targetRow][col]);
                        delete grid[targetRow][col];
                        grid[targetRow][col] = new Tile();
                        changeScore(grid[targetRow-1][col]->getValue());
                    }
                }
            }
        }
    }
    void moveDown() {
        for (int col = 0; col < size; ++col) {
            for (int row = size - 2; row >= 0; --row) {
                if (grid[row][col]->getValue() != 0) {
                    int targetRow = row + 1;
                    while (targetRow < size && grid[targetRow][col]->getValue() == 0) {
                        targetRow++;
                    }
                    targetRow--;
                    if (targetRow != row) {
                        std::swap(grid[targetRow][col], grid[row][col]);
                    }
                    if (targetRow < size - 1 && grid[targetRow][col]->canMergeWith(*grid[targetRow + 1][col])) {
                        grid[targetRow + 1][col]->merge(*grid[targetRow][col]);
                        delete grid[targetRow][col];
                        grid[targetRow][col] = new Tile();
                        changeScore(grid[targetRow + 1][col]->getValue());
                
                    }
                }
            }
        }
    }
    void moveLeft() {
        for (int row = 0; row < size; ++row) {
            for (int col = 1; col < size; ++col) {
                if (grid[row][col]->getValue() != 0) {
                    int targetCol = col - 1;
                    while (targetCol >= 0 && grid[row][targetCol]->getValue() == 0) {
                        targetCol--;
                    }
                    targetCol++;
                    if (targetCol != col) {
                        std::swap(grid[row][targetCol], grid[row][col]);
                    }
                    if (targetCol > 0 && grid[row][targetCol]->canMergeWith(*grid[row][targetCol - 1])) {
                        grid[row][targetCol - 1]->merge(*grid[row][targetCol]);
                        delete grid[row][targetCol];
                        grid[row][targetCol] = new Tile();
                        changeScore(grid[row][targetCol - 1]->getValue());
                    }
                }
            }
        }
    }
    void moveRight() {
        for (int row = 0; row < size; ++row) {
            for (int col = size - 2; col >= 0; --col) {
                if (grid[row][col]->getValue() != 0) {
                    int targetCol = col + 1;
                    while (targetCol < size && grid[row][targetCol]->getValue() == 0) {
                        targetCol++;
                    }
                    targetCol--;
                    if (targetCol != col) {
                        std::swap(grid[row][targetCol], grid[row][col]);
                    }
                    if (targetCol < size - 1 && grid[row][targetCol]->canMergeWith(*grid[row][targetCol + 1])) {
                        grid[row][targetCol + 1]->merge(*grid[row][targetCol]);
                        delete grid[row][targetCol];
                        grid[row][targetCol] = new Tile();
                        changeScore(grid[row][targetCol + 1]->getValue());
                    }
                }
            }
        }
    }
    virtual void addRandomTile()  {
        std::vector<std::pair<int, int>> emptyTiles;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j]->getValue() == 0) {
                    emptyTiles.emplace_back(i, j);
                }
            }
        }
        if (!emptyTiles.empty()) {
            std::pair<int, int> pos = emptyTiles[rand() % emptyTiles.size()];
            delete grid[pos.first][pos.second];
            int x = rand() % 100;
            if (x < 50) {
                grid[pos.first][pos.second] = new Tile(2);
            } else if (x < 70) {
                grid[pos.first][pos.second] = new Tile(4);
            } else if (x < 75) {
                grid[pos.first][pos.second] = new Tile(8);
            } else if (x < 80) {
                grid[pos.first][pos.second] = new Tile(16);
            } else if (x < 90) {
                grid[pos.first][pos.second] = new Tile(-1);
            }
            else if (x < 95) {
                grid[pos.first][pos.second] = new Tile(-999);
            }
            else {
                grid[pos.first][pos.second] = new Tile(2);
            }
        }
    }
    bool canMove() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j]->getValue() == 0) return true;
                if (i > 0 && grid[i][j]->canMergeWith(*grid[i - 1][j])) return true;
                if (i < size - 1 && grid[i][j]->canMergeWith(*grid[i + 1][j])) return true;
                if (j > 0 && grid[i][j]->canMergeWith(*grid[i][j - 1])) return true;
                if (j < size - 1 && grid[i][j]->canMergeWith(*grid[i][j + 1])) return true;
            }
        }
        return false;
    }
    virtual void printBoard() const {
        std::cout << "\n\n\n\n\n\n\n";
        std::cout << "\t\t\t\tScore: " << score << "\n";  // Hiển thị điểm số
        std::cout << "\t\t\t\t----------------------------------\n";
        for (const auto& row : grid) {
            std::cout << "\t\t\t       |";
            for (const auto& tile : row) {
                tile->printTile();
                std::cout << "\t";
            }
            std::cout << "  |";
            std::cout << std::endl;
        }
        std::cout << "\t\t\t\t----------------------------------\n";
    }
};




class LetterBoard : public Board {
public:
    LetterBoard(int size = 4) : Board(size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                delete grid[i][j];
                grid[i][j] = new TileWithLetter();
            }
        }
    }

    void addRandomTile() override {
        std::vector<std::pair<int, int>> emptyTiles;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j]->getValue() == 0) {
                    emptyTiles.emplace_back(i, j);
                }
            }
        }
        if (!emptyTiles.empty()) {
            std::pair<int, int> pos = emptyTiles[rand() % emptyTiles.size()];
            delete grid[pos.first][pos.second];
            grid[pos.first][pos.second] = new TileWithLetter(rand() % 2 == 0 ? 2 : 4);
        }
    }
};

class Game {
private:
    Board* board;

public:
    Game(Board* b) : board(b) {}

    ~Game() {
        delete board;
    }

    void play() {
        while (board->canMove()) {
            board->printBoard();
            char move;
            move = _getch();
            system("cls");
            switch (move) {
            case 'w': board->moveUp(); break;
            case 's': board->moveDown(); break;
            case 'a': board->moveLeft(); break;
            case 'd': board->moveRight(); break;
            default: std::cout << "Invalid move!" << std::endl;
            }
            board->addRandomTile();
        }
        std::cout << "Game Over!" << std::endl;
    }
};


void sleepChrono(int milisecond)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milisecond));
}
void lamMau()
{
    int color = 1;
    std::cout << "\t\t\t*\t\t\t\t\t*\n\n\n LOADING:";
    std::string loadDing = "[<3 <3 0% ============ 25% =============== 50% =============== 75% ============= 100% <3 <3]\n \n \t\t\t\tWELCOME TO 2048 GAME, MAKE BY NHOM 5 - OOP HE:))";
    for (auto c : loadDing) {
        if (c > 't') {
            color += 29;
        }
        else {
            color += 10;
        }
        setColor(color);
        std::cout << c;
        sleepChrono(5); // Đợi 1000 ms (0.1 giây)
    }
    std::cout << "\n\n\n\t\t\t\t\tDANG NHAP THANH CONG\n\n\n";
}

int main() {
    srand(time(0));
    lamMau();
    setColor(2);
    std::cout << "\t\t\t\t\tPick type Board:\n";
    std::cout << "\t\t\t\t\t1. Number\n";
    std::cout << "\t\t\t\t\t2. Letter\n";
    char choice;
    choice = _getch();
    system("cls");
    setColor(2);
    Game* game;

    if (choice == '2') {
        game = new Game(new LetterBoard(4));
    }
    else {
        game = new Game(new Board(4));
    }

    game->play();

    delete game;

    return 0;
}
