#pragma once
class Connect4
{
public:
	Connect4(int rows, int columns);
	void playGame();

private:
	int numRows;
	int numColumns;
	char** board;
	char currentPlayer;

	void printBoard();
	bool makeMove(int column, char playerCharacter);
};

