#pragma once
#include <vector>

const int EMPTY = 0;
const int PLAYER = 1;
const int AI = 2;

class Connect4 {
public:
	Connect4(int rows, int columns) : numRows(rows), numColumns(columns), board(rows, std::vector<int>(columns, EMPTY)), currentPlayer(PLAYER), turns(0) {}

	const std::vector<std::vector<int>>& getBoard() const { return board; }
	int getRows() const { return numRows; }
	int getColumns() const { return numColumns; }

	void printBoard();

	void playGame();

private:
	int numRows;
	int numColumns;
	std::vector<std::vector<int>> board;
	int currentPlayer;
	int turns;

	int userMove();
	bool isValidMove(int column);
	bool makeMove(int column, int player);

	bool checkWin();
	bool checkHorizontal();
	bool checkVertical();
	bool checkDiagonal();
	bool isBoardFull();

	Connect4 copy();

	int aiMove();
	int bestMove();
	std::vector<int> calculatePriority();
	int minimax(Connect4& game, int depth, int alpha, int beta, bool maximizingPlayer);
	int evaluate(Connect4& game);
	int occurrences(Connect4& game, int player);
};

