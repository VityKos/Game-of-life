#include "game_of_life.h"

int main() {
	GameOfLife game = GameOfLife(600, 600);
	game.set_sleep_time(300);
	game.set_resolution(2);
	game.set_rule({ 5,6,7,8 }, { 4, 5,6,7,8 });
	game.random_field();
	game.run();
}




