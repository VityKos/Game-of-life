#include <iostream>

#define HEIGHT 21
#define WIDTH 50

class GameOfLife {
    char world[HEIGHT][WIDTH];
    char oldWorld[HEIGHT][WIDTH];
public:
    void print();
    void update();
    char getState();
};

int main()
{
    std::cout << "Hello World!\n";
}

void GameOfLife::print()
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << world[i][j];
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < WIDTH; i++) {
        std::cout << '=';
    }
    std::cout << std::endl;
}

void GameOfLife::update()
{
}

char GameOfLife::getState()
{
    return 0;
}
