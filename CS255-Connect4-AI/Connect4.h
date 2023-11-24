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
	int aiMove();
	bool makeMove(int column, char playerCharacter);

	bool checkWin();
	bool checkHorizontal();
	bool checkVertical();
	bool checkDiagonal();
	bool boardIsFull();

	int evaulate();
	int minimax();
};

