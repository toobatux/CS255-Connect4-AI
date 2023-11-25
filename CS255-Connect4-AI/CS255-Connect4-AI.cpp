#include <iostream>
#include "Connect4.h"

int main()
{
	int rows, columns;
	std::cout << "Set the number of rows (default is 6): ";
	std::cin >> rows;
	std::cout << "Set the number of columns (default is 7): ";
	std::cin >> columns;

	Connect4 Game(rows, columns);
	Game.playGame();
}
