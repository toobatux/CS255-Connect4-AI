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

	void printBoard(char** board);

	int userMove(int turns);
	int aiMove();
	bool makeMove(int column, char playerCharacter);

	bool checkWin();
	bool checkHorizontal();
	bool checkVertical();
	bool checkDiagonal();
	bool boardIsFull();

	char** copyBoard(char** board);
	int evaulate();
	int minimax();
};

