#pragma once
#include <vector>
#include <chrono>

const int EMPTY = 0;
const int PLAYER = 1;
const int AI = 2;

class Connect4 {
public:
	Connect4(int rows, int columns) : numRows(rows), numColumns(columns), board(rows, std::vector<int>(columns, EMPTY)), currentPlayer(PLAYER), turns(0) {}
	void printBoard();
	void playGame(int maxTimeSeconds);

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

	int aiMove(int maxTimeSeconds);
	int bestMoveWithinTime(int maxTimeSeconds);
	std::vector<int> calculatePriority();
	int minimax(Connect4& game, int depth, int alpha, int beta, bool maximizingPlayer, std::chrono::high_resolution_clock::time_point startTime, int maxTimeSeconds);

	int evaluate(Connect4& game, int player);
	int evaluatePlayer(Connect4& game, int playerToCheck, int currentPlayer);
	int evaluatePosition(Connect4& game, int row, int col, int playerToCheck, int currentPlayer);
	int evaluateLine(Connect4& game, int row, int col, int deltaRow, int deltaCol, int playerToCheck, int currentPlayer, int weight);
	int evaluateDiagonal(Connect4& game, int row, int col, int playerToCheck, int currentPlayer);
	int countWinPos(int player);

	bool OppWinPosInColumn(int column);

};

