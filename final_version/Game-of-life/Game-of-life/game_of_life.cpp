//
// Created by Viktor on 22.05.22.
//

#include <thread>
#include <iostream>
#include "game_of_life.h"
#include "Canvas.h"
#include <utility>
#include <vector>

#define BLACK  RGB(0, 0, 0)
#define WHITE  RGB(255, 255, 255)


bool isValueInVector(const std::vector<int>& vec, int value) {
    for (auto x : vec) if (x == value) { return true; };
    return false;
}
void GameOfLife::swap() {
    for (int i = 0; i < height_world; i++) {
        for (int j = 0; j < width_world; j++) {
            currentGeneration[i][j] = previousGeneration[i][j];
        }
    }
}
void GameOfLife::add(const Shape& sh) {
    for (int i = sh.yCoord; i - sh.yCoord < sh.height; i++) {
        for (int j = sh.xCoord; j - sh.xCoord < sh.width; j++) {
            if (i < height_world && j < width_world) {
                currentGeneration[i][j] = sh.figure[i - sh.yCoord][j - sh.xCoord];
            }
        }
    }
}
void GameOfLife::consol_print() {
    canvas c;
    c.clear();
    c.add((shape*) new rectangle(0, 0, width_world*resolution, height_world*resolution, RGB(255, 255, 255), true, RGB(255, 255, 255)));
    for (int i = 0; i < height_world; i++) {
        for (int j = 0; j < width_world; j++) {
            int x = i * resolution;
            int y = j * resolution;
            if (currentGeneration[i][j] == 'X') 
                c.add((shape*) new rectangle(x, y, x + resolution, y + resolution, RGB(0, 0, 0), true, RGB(0, 0, 0)));
        }
    }
    c.show();
}
void GameOfLife::update() {
    days++;
    for (int i = 0; i < height_world; i++) {
        for (int j = 0; j < width_world; j++) {
            previousGeneration[i][j] =
                GameOfLife::getState(currentGeneration[i][j], i, j);
        }
    }
    swap();
}
char GameOfLife::getState(char state, int y, int x) {
    int neighbors = 0;

    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i == y && j == x) {
                continue;
            }
            if (i > -1 && i < height_world && j > -1 && j < width_world) {
                if (currentGeneration[i][j] == 'X') {
                    neighbors++;
                }
            }
        }
    }

    if (state == 'X') {
        return isValueInVector(neighbors_to_survive, neighbors) ? 'X' : '.';
    }
    else {
        return isValueInVector(neighbors_to_born, neighbors) ? 'X' : '.';
    }
}
[[noreturn]] void GameOfLife::run() {
    for (;;) {
        system("cls");
        consol_print();
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        update();
    }
}
void GameOfLife::random_field() {
    for (int i = 0; i < height_world; i++) {
        for (int j = 0; j < width_world; j++) {
            currentGeneration[i][j] = rand() % 2 == 0 ? 'X' : '.';
        }
    }
}

void GameOfLife::set_resolution(int value) {
    resolution = value;
}

GameOfLife::GameOfLife(int height, int width) : height_world(height), width_world(width), sleep_time(200), days(0) {
    resolution = 10;
    for (int i = 0; i < height_world; i++) {
        std::vector<char> vec;
        for (int j = 0; j < width_world; j++) {
            vec.push_back('.');
        }
        currentGeneration.push_back(vec);
        previousGeneration.push_back(vec);
    }

    neighbors_to_born = { 3 };
    neighbors_to_survive = { 2,3 };
}
void GameOfLife::set_sleep_time(int time) {
    sleep_time = time;
}

void GameOfLife::set_rule(std::vector<int> vec_to_born, std::vector<int> vec_to_survive) {
    neighbors_to_born = std::move(vec_to_born);
    neighbors_to_survive = std::move(vec_to_survive);
}

GameOfLife::~GameOfLife() {}

Glider::Glider(int x, int y) : Shape() {
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
void Glider::info() {
    std::cout << "Glider is smallest spaceship and it travel diagonally at a speed of one cell every four generations" << std::endl;
}

Blinker::Blinker(int x, int y) : Shape() {
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
void Blinker::info() {
    std::cout << "The blinker is the smallest and most common oscillator, found by John Conway in March 1970.\n It is one of only a handful of known oscillators that is a polyomino, and it is the only known finite oscillator that is \n one cell thick (although the pentadecathlon is \"almost\" one cell thick in that there is a one cell thick pattern that is a grandparent of it, and the infinite version of the worker bee is one cell thick)." << std::endl;
}

Dot::Dot(int x, int y) : Shape() {
    height = DOT_SIZE;
    width = DOT_SIZE;
    xCoord = x;
    yCoord = y;
    figure = new char* [DOT_SIZE];
    for (int i = 0; i < DOT_SIZE; i++) {
        figure[i] = new char[DOT_SIZE];
    }
    figure[0][0] = 'X';
}
Dot::~Dot()
{
    for (int i = 0; i < DOT_SIZE; i++) {
        delete[] figure[i];
    }
    delete[] figure;
}
void Dot::info() {
    std::cout << "Simple dot" << std::endl;
}


