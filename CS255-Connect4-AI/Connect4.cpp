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
	char user = 'X';
	char computer = 'O';

	currentPlayer = user;

	bool gameDone = false;

	while(!gameDone) {
		this->printBoard();
		if (currentPlayer == user) {
			makeMove(userMove(), user);
		}
		else if (currentPlayer == computer) {
			makeMove(aiMove(), computer);
		}

		gameDone = checkWin();
		if (gameDone) {
			this->printBoard();
			std::cout << "Player " << currentPlayer << " wins!\n";
			return;
		}
		else if (this->boardIsFull()) {
			this->printBoard();
			std::cout << "The game is a draw.\n";
			return;
		}

		currentPlayer = (currentPlayer == user) ? computer : user;

	}
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

int Connect4::aiMove()
{
	return 0;
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

bool Connect4::checkWin()
{
	return checkHorizontal() || checkVertical() || checkDiagonal();
}

bool Connect4::checkHorizontal()
{
	int count = 0;
	
	for (int c = 0; c < numColumns; c++) {
		for (int r = 0; r < numRows; r++) {
			for (int i = 0; i < 4; i++) {
				if (board[r][c + i] == currentPlayer) {
					count++;
				}
				if (count == 4) { 
					return true; 
				}
			}
			count = 0;
		}
	}
	return false;
}

bool Connect4::checkVertical()
{
	int count = 0;

	for (int c = 0; c < numColumns; c++) {
		for (int r = 0; r < numRows - 3; r++) {
			for (int i = 0; i < 4; i++) {
				if (board[r + i][c] == currentPlayer) {
					count++;
				}
				if (count == 4) {
					return true;
				}
			}
			count = 0;
		}
	}

	return false;
}

bool Connect4::checkDiagonal()
{
	int count = 0;

	for (int c = 0; c < numColumns - 3; c++) {
		for (int r = 3; r < numRows; r++) {
			for (int i = 0; i < 4; i++) {
				if (board[r - i][c + i] == currentPlayer) {
					count++;
				}
				if (count == 4) {
					return true;
				}
			}
			count = 0;
		}
	}

	count = 0;

	for (int c = 0; c < numColumns - 3; c++) {
		for (int r = 3; r < numRows - 3; r++) {
			for (int i = 0; i < 4; i++) {
				if (board[r + i][c + i] == currentPlayer) {
					count++;
				}
				if (count == 4) {
					return true;
				}
			}
			count = 0;
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

int Connect4::minimax()
{
	return 0;
}
