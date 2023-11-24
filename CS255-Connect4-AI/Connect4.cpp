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
	int col;
	bool validMove;

	do {
		this->printBoard();
		col = userMove();
		makeMove(col, currentPlayer);
		if (this->checkWin(numRows - 1, col)) {
			this->printBoard();
			std::cout << "Player " << currentPlayer << " wins!\n";
			return;
		}
		else if (this->boardIsFull()) {
			this->printBoard();
			std::cout << "The game is a draw.\n";
			return;
		}

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
	std::cout << "\n";
}

int Connect4::userMove()
{
	int move = -1;
	while (true) {
		std::cout << "Player " << currentPlayer << " enter a column: ";
		std::cin >> move;

		if (!std::cin) {	// handle non-int input
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please enter an integer.\n";
		}
		else if (!(move < numColumns && move >= 0)) {
			std::cout << "Invalid move, try again.\n";
		}
		else if (!(move >= 0 && move < numColumns && board[0][move] == ' ')) {
			std::cout << "Column is full, try again.\n";
		}
		else {
			break; // valid input
		}
	}
	return move;
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

bool Connect4::checkWin(int row, int column)
{
	return checkHorizontal(row, column) || checkVertical(row, column) || checkDiagonal(row, column);
}

bool Connect4::checkHorizontal(int row, int column)
{
	int count = 0;
	
	for (int j = 0; j < numColumns; ++j) {
		if (board[row][j] == currentPlayer) {
			count++;
			if (count == 4) return true;
		}
		else {
			count = 0;
		}
	}
	return false;
}

bool Connect4::checkVertical(int row, int column)
{
	int count = 0;
	
	for (int i = 0; i < numRows; i++) {
		if (board[i][column] == currentPlayer) {
			count++;
			if (count == 4) return true;
		}
		else {
			count = 0;
		}
	}
	
	return false;
}

bool Connect4::checkDiagonal(int row, int column)
{
	// Top-left to bottom-right
	int count = 0;

	for (int i = row - 3, j = column - 3; i <= row + 3 && j <= column + 3; ++i, ++j) {
		if (i >= 0 && i < numRows && j >= 0 && j < numColumns) {
			if (board[i][j] == currentPlayer) {
				count++;
				if (count == 4) {
					return true;
				}
			}
			else {
				count = 0;
			}
		}
	}

	// Bottom-left to top-right
	count = 0;

	for (int i = row - 3, j = column + 3; i <= row + 3 && j >= column - 3; ++i, --j) {
		if (i >= 0 && i < numRows && j >= 0 && j < numColumns) {
			if (board[i][j] == currentPlayer) {
				count++;
				if (count == 4) {
					return true;
				}
			}
			else {
				count = 0;
			}
		}
	}

	return false;
}

bool Connect4::boardIsFull()

{
	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numColumns; ++j) {
			if (board[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

int Connect4::evaulate()
{
	return 0;
}
