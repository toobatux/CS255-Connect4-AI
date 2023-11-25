#include "Connect4.h"
#include <iostream>

Connect4::Connect4(int rows, int columns) : numRows(rows), numColumns(columns), currentPlayer(' ')
{
	board = new char* [numRows];
	for (int r = 0; r < numRows; ++r) {
		board[r] = new char[numColumns];
		for (int c = 0; c < numColumns; ++c) {
			board[r][c] = ' ';
		}
	}
}


void Connect4::playGame()
{
	char user = 'X';
	char computer = 'O';

	currentPlayer = user;

	int turns = 0;

	bool gameDone = false;

	while(!gameDone) {
		this->printBoard(board);
		if (currentPlayer == user) {
			this->makeMove(userMove(turns), user);
		}
		else if (currentPlayer == computer) {
			this->makeMove(aiMove(), computer);
		}

		turns++;

		gameDone = this->checkWin();
		if (gameDone) {
			this->printBoard(board);
			std::cout << "Player " << currentPlayer << " wins!\n";
			return;
		}
		else if (this->boardIsFull()) {
			this->printBoard(board);
			std::cout << "The game is a draw.\n";
			return;
		}

		currentPlayer = (currentPlayer == user) ? computer : user;

	}
}

void Connect4::printBoard(char** board)
{
	for (int r = 0; r < numRows; ++r) {
		for (int c = 0; c < numColumns; ++c) {
			std::cout << board[r][c] << " | ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int Connect4::userMove(int turns)
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
		else if (turns <= 1 && (move == numColumns / 2 || move == 0 || move == numColumns - 1)) {
			std::cout << "Cannot choose middle or edge columns on first turn.\n";
		}
		else {
			break; // valid input
		}
	}
	return move;
}

int Connect4::aiMove()
{
	std::cout << "AI is choosing a move..." << std::endl;
	return minimax();
}

bool Connect4::makeMove(int column, char playerCharacter)
{
	for (int r = numRows - 1; r >= 0; --r) {
		if (board[r][column] == ' ') {
			board[r][column] = playerCharacter;
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
	for (int r = 0; r < numRows; ++r) {
		for (int c = 0; c < numColumns; ++c) {
			if (board[r][c] == ' ') {
				return false;
			}
		}
	}
	return true;
}



char** Connect4::copyBoard(char** board)
{
	char** newBoard = new char* [numRows];
	for (int r = 0; r < numRows; ++r) {
		newBoard[r] = new char[numColumns];
		for (int c = 0; c < numColumns; ++c) {
			newBoard[r][c] = board[r][c];
		}
	}
	
	return newBoard;
}

int Connect4::evaulate()
{

	return 0;
}

int Connect4::minimax()
{
	this->evaulate();
	//this->printBoard(copyBoard(board));

	return 0;
}
