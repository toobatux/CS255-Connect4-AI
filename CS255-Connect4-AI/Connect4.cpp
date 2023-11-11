#include "Connect4.h"
#include <iostream>

Connect4::Connect4(int rows, int columns) : numRows(rows), numColumns(columns), currentPlayer('X')
{
	board = new char* [numRows];
	for (int i = 0; i < numRows; ++i) {
		board[i] = new char[numColumns];
		for (int j = 0; j < numColumns; ++j) {
			board[i][j] = ' ';
		}
	}

}

void Connect4::playGame()
{
	char playerSymbol = 'X';
	do {
		int col;
		std::cout << "Enter a column: ";
		std::cin >> col;

		this->makeMove(col, currentPlayer);
		this->printBoard();

		currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

	} while (true);
}

void Connect4::printBoard()
{
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numColumns; ++j) {
			std::cout << board[i][j] << " | ";
		}
		std::cout << "\n";
	}
}

bool Connect4::makeMove(int column, char playerCharacter)
{
	for (int i = numRows - 1; i >= 0; --i) {
		if (board[i][column] == ' ') {
			board[i][column] = playerCharacter;
			return true;
		}
	}

	return false;
}
