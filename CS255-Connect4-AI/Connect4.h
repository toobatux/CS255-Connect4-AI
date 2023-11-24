#pragma once
class Connect4
{
public:
	Connect4(int rows, int columns);
	//~Connect4();
	void playGame();

private:
	int numRows;
	int numColumns;
	char** board;
	char currentPlayer;

	void printBoard();
	int userMove();
	bool makeMove(int column, char playerCharacter);
	bool checkWin(int row, int column);
	bool checkHorizontal(int row, int column);
	bool checkVertical(int row, int column);
	bool checkDiagonal(int row, int column);
	bool boardIsFull();

	int evaulate();
	int minimax();
};

