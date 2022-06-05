//
// Created by Viktor on 22.05.22.
//
#include <vector>

class Shape {
public:
    int xCoord{};
    int yCoord{};
    int height{};
    int width{};
    char** figure{};
    virtual  void info() {};
};

class Glider : public Shape {
    static const int GLIDER_SIZE = 3;
public:
    void info() override;
    Glider(int x, int y);
    ~Glider();
};

class Dot : public Shape {
    static const int DOT_SIZE = 1;
public:
    void info() override;
    Dot(int x, int y);
    ~Dot();
};

class Blinker : public Shape {
    static const int BLINKER_HEIGHT = 3;
    static const int BLINKER_WIDTH = 1;
public:
    void info() override;
    Blinker(int height, int width);
    ~Blinker();
};

class GameOfLife {

    std::vector<std::vector<char>> currentGeneration;
    std::vector<std::vector<char>> previousGeneration;

    int days;
    int height_world;
    int width_world;
    int sleep_time;
    std::vector<int> neighbors_to_born;
    std::vector<int>  neighbors_to_survive;
    int resolution;
    
public:
    char getState(char state, int y, int x);
    void update();
    void swap();
    void random_field();
    void set_sleep_time(int time);
    void set_resolution(int value);
    void set_rule(std::vector<int> vec_to_born, std::vector<int> vec_to_survive);
    GameOfLife(int height, int width);
    ~GameOfLife();
    void consol_print();
    [[noreturn]] void run();
    void add(const Shape& sh);
};


