#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <Windows.h>


#define HEIGHT 30
#define WIDTH 100

#define FPS 100


void SetWindow(int Width, int Height) {
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

class Shape {
public:
    int xCoord;
    int yCoord;
    int height;
    int width;
    char** figure;
};

class Glider : public Shape {
    static const int GLIDER_SIZE = 3;
public:
    Glider(int x, int y);
    ~Glider();
};

class Dot : public Shape {
    static const int DOT_HEIGHT = 1;
    static const int DOT_WIDTH = 1;
public:
    Dot(int x, int y);
    ~Dot();
};

class Blinker : public Shape {
    static const int BLINKER_HEIGHT = 3;
    static const int BLINKER_WIDTH = 1;
public:
    Blinker(int x, int y);
    ~Blinker();
};

class RandomField : public Shape {
    static const int RandomField_HEIGHT = HEIGHT;
    static const int RandomField_WIDTH = WIDTH;
public:
    RandomField();
    ~RandomField();
};

class GameOfLife {
    char world[HEIGHT][WIDTH];
    char otherWorld[HEIGHT][WIDTH];
    bool toggle;
    char getState(char state, int xCoord, int yCoord);
    void update();
public:
    GameOfLife();
    void print();
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
    for(;;) {
        system("cls");
        print();
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS));
        update();
    }
}

Glider::Glider(int x, int y) {
    xCoord = x;
    yCoord = y;
    height = GLIDER_SIZE;
    width = GLIDER_SIZE;
    figure = new char* [GLIDER_SIZE];
    for (int i = 0; i < GLIDER_SIZE; i++) {
        figure[i] = new char[GLIDER_SIZE];
    }
    for (int i = 0; i < GLIDER_SIZE; i++) {
        for (int j = 0; j < GLIDER_SIZE; j++) {
            figure[i][j] = '.';
        }
    }
    figure[0][1] = 'X';
    figure[1][2] = 'X';
    figure[2][0] = 'X';
    figure[2][1] = 'X';
    figure[2][2] = 'X';
}

Glider::~Glider() {
    for (int i = 0; i < GLIDER_SIZE; i++) {
        delete[] figure[i];
    }
    delete[] figure;
}

Blinker::Blinker(int x, int y) {
    xCoord = x;
    yCoord = y;
    height = BLINKER_HEIGHT;
    width = BLINKER_WIDTH;
    figure = new char* [BLINKER_HEIGHT];
    for (int i = 0; i < BLINKER_HEIGHT; i++) {
        figure[i] = new char[BLINKER_WIDTH];
    }
    for (int i = 0; i < BLINKER_HEIGHT; i++) {
        for (int j = 0; j < BLINKER_WIDTH; j++) {
            figure[i][j] = 'X';
        }
    }
}

Blinker::~Blinker() {
    for (int i = 0; i < BLINKER_HEIGHT; i++) {
        delete[] figure[i];
    }
    delete[] figure;
}

Dot::Dot(int x, int y) {
    height = DOT_HEIGHT;
    width = DOT_WIDTH;
    xCoord = x;
    yCoord = y;
    figure = new char* [DOT_HEIGHT];
    for (int i = 0; i < DOT_HEIGHT; i++) {
        figure[i] = new char[DOT_WIDTH];
    }
    figure[0][0] = 'X';
}

Dot::~Dot()
{
    for (int i = 0; i < DOT_HEIGHT; i++) {
        delete[] figure[i];
    }
    delete[] figure;
}

RandomField::RandomField() {
    height = RandomField_HEIGHT;
    width = RandomField_WIDTH;
    xCoord = 0;
    yCoord = 0;
    figure = new char* [RandomField_HEIGHT];
    for (int i = 0; i < RandomField_HEIGHT; i++) {
        figure[i] = new char[RandomField_WIDTH];
    }
    for (int i = 0; i < RandomField_HEIGHT; i++) {
        for (int j = 0; j < RandomField_WIDTH; j++) {
            figure[i][j] = rand() % 2 == 0 ? 'X' : '.';
        }
    }
}

RandomField::~RandomField() {
    for (int i = 0; i < RandomField_HEIGHT; i++) {
        delete[] figure[i];
    }
    delete[] figure;
}

int main() {
    //std::ios_base::sync_with_stdio(false);
    SetWindow(WIDTH, HEIGHT+1);

    GameOfLife game = GameOfLife();
    Glider g(0,0);
    Blinker b(10, 10);

    game.add(b);
    game.add(g);
    game.run();

    return 0;
}