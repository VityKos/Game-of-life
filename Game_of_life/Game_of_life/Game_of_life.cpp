#include <iostream>
#include <chrono>
#include <thread>

#define HEIGHT 21
#define WIDTH 50
#define FPS 600

class Shape {
public:
    int xCoord;
    int yCoord;
    int height;
    int width;
    char** figure;
};


class GameOfLife {
    char world[HEIGHT][WIDTH];
    char otherWorld[HEIGHT][WIDTH];
    bool toggle;

public:
    GameOfLife();
    void print();
    void update();
    char getState(char state, int xCoord, int yCoord);
    void run();
    void add(Shape sh);
};

void GameOfLife::add(Shape sh) {
    for (int i = sh.yCoord; i - sh.yCoord < sh.height; i++) {
        for (int j = sh.xCoord; j - sh.xCoord < sh.width; j++) {
            if (i < HEIGHT && j < WIDTH) {
                world[i][j] = sh.figure[i - sh.yCoord][j - sh.xCoord];
            }
        }
    }
}

GameOfLife::GameOfLife() {
    toggle = true;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            world[i][j] = '.';
        }
    }

}

void GameOfLife::print() {
    for (int i = 0; i < WIDTH; i++) {
        std::cout << '=';
    }
    std::cout << std::endl;
    if (toggle) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << world[i][j];
            }
            std::cout << std::endl;
        }
    }
    else {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << otherWorld[i][j];
            }
            std::cout << std::endl;
        }
    }
    for (int i = 0; i < WIDTH; i++) {
        std::cout << '=';
    }
    std::cout << std::endl;
}

void GameOfLife::update() {
    if (toggle) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                otherWorld[i][j] =
                    GameOfLife::getState(world[i][j], i, j);
            }
        }
        toggle = !toggle;
    }
    else {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                world[i][j] =
                    GameOfLife::getState(otherWorld[i][j], i, j);
            }
        }
        toggle = !toggle;
    }
}

char GameOfLife::getState(char state, int y, int x) {
    int neighbors = 0;
    if (toggle) {
        for (int i = y - 1; i <= y + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (i == y && j == x) {
                    continue;
                }
                if (i > -1 && i < HEIGHT && j > -1 && j < WIDTH) {
                    if (world[i][j] == 'X') {
                        neighbors++;
                    }
                }
            }
        }
    }
    else {
        for (int i = y - 1; i <= y + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (i == y && j == x) {
                    continue;
                }
                if (i > -1 && i < HEIGHT && j > -1 && j < WIDTH) {
                    if (otherWorld[i][j] == 'X') {
                        neighbors++;
                    }
                }
            }
        }
    }
    if (state == 'X') {
        return (neighbors > 1 && neighbors < 4) ? 'X' : '.';
    }
    else {
        return (neighbors == 3) ? 'X' : '.';
    }
}

void GameOfLife::run() {
    while(true) {
        system("cls");
        print();
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS));
        update();
    }
}



int main() {

    GameOfLife game = GameOfLife();
    game.run();

}