#include "Connect4.h"
#include <iostream>

void Connect4::printBoard()
{
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == EMPTY) {
                std::cout << "_ ";
            }
            else if (cell == PLAYER) {
                std::cout << "X ";
            }
            else if (cell == AI) {
                std::cout << "O ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < numColumns; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;
}

void Connect4::playGame()
{
    currentPlayer = PLAYER;

    bool gameDone = false;

    while (!gameDone) {
        this->printBoard();
        if (currentPlayer == PLAYER) {
            this->makeMove(userMove(), PLAYER);
        }
        else if (currentPlayer == AI) {
            this->makeMove(aiMove(), AI);
        }

        //this->makeMove(userMove(turns), currentPlayer);

        turns++;

        gameDone = this->checkWin();
        if (gameDone) {
            this->printBoard();
            std::cout << "Player " << currentPlayer << " wins!\n";
            return;
        }
        else if (this->isBoardFull()) {
            this->printBoard();
            std::cout << "The game is a draw!\n";
            return;
        }

        currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER;
    }
}

int Connect4::userMove()
{
    int move = -1;

    std::cout << "Player " << currentPlayer << " enter your move (column number 0 - " << numColumns - 1 << ") : ";
    std::cin >> move;

    while (!isValidMove(move)) {
        std::cout << "Invalid Input.\n";

        if (!std::cin) {	// handle non-int input
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "Please enter an integer.\n";
        }

        std::cout << "Player " << currentPlayer << " enter a column: ";
        std::cin >> move;
    }

    return move;
}

bool Connect4::isValidMove(int column)
{
    if (column >= 0 && column < numColumns && board[0][column] == EMPTY) {
        if (!(turns <= 1 && (column == numColumns / 2 || column == 0 || column == numColumns - 1))) {
            return true;
        }
    }
    return false;
}

bool Connect4::makeMove(int column, int player)
{
    for (int r = numRows - 1; r >= 0; r--) {
        if (board[r][column] == EMPTY) {
            board[r][column] = player;
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

    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numColumns - 3; c++) {
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

    for (int r = 0; r < numRows - 3; r++) {
        for (int c = 0; c < numColumns; c++) {
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

    // Bottom-left to top-right
    for (int r = 3; r < numRows; r++) {
        for (int c = 0; c < numColumns - 3; c++) {
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

    // Top-left to bottom-right
    for (int r = 0; r < numRows - 3; r++) {
        for (int c = 0; c < numColumns - 3; c++) {
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

bool Connect4::isBoardFull()
{
    for (int c = 0; c < numColumns; c++) {
        if (board[0][c] == EMPTY) {
            return false;
        }
    }

    return true;
}

Connect4 Connect4::copy()
{
    Connect4 clone(numRows, numColumns);
    clone.board = board;

    return clone;
}


// AI methods
int Connect4::aiMove()
{
    std::cout << "AI is choosing a move...\n";

    return bestMove();
}

int Connect4::bestMove()
{
    std::vector<int> priorityOrder = calculatePriority();

    int bestMove = -1;
    int bestEval = INT_MIN;

    //for (int c = 0; c < numColumns; c++) {
    for (int c : priorityOrder) {
        if (isValidMove(c)) {
            Connect4 clone = this->copy();
            clone.makeMove(c, AI);
            int eval = minimax(clone, 6, INT_MIN, INT_MAX, false);

            if (eval > bestEval) {
                bestEval = eval;
                bestMove = c;
            }
        }
    }
    return bestMove;
}

std::vector<int> Connect4::calculatePriority()
{
    int centerCol = numColumns / 2;
    std::vector<int> priorityOrder;

    priorityOrder.push_back(centerCol);

    for (int c = 1; c < numColumns - 1; c++) {
        if (c != centerCol) {
            priorityOrder.push_back(c);
        }
    }

    priorityOrder.push_back(0);
    priorityOrder.push_back(numColumns - 1);

    return priorityOrder;
}

int Connect4::minimax(Connect4& game, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0 || game.checkWin() || game.isBoardFull()) {
        return evaluate(game);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int c = 0; c < game.numColumns; c++) {
            if (game.isValidMove(c)) {
                Connect4 clone = game.copy();
                clone.makeMove(c, AI);
                int eval = minimax(clone, depth - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);

                if (beta <= alpha) { break; }
            }
        }
        return maxEval;
    }

    else {
        int minEval = INT_MAX;
        for (int c = 0; c < game.numColumns; c++) {
            if (game.isValidMove(c)) {
                Connect4 clone = game.copy();
                clone.makeMove(c, PLAYER);
                int eval = minimax(clone, depth - 1, alpha, beta, true);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);

                if (beta <= alpha) { break; }
            }
        }
        return minEval;
    }
}

int Connect4::evaluate(Connect4& game)
{
    int aiScore = occurrences(game, AI);
    int playerScore = occurrences(game, PLAYER);

    return aiScore - playerScore;
}

int Connect4::occurrences(Connect4& game, int player)
{
    int count = 0;

    for (int r = 0; r < game.numRows; r++) {
        for (int c = 0; c < game.numColumns; c++) {
            if (game.board[r][c] == player) {
                count++;
            }
        }
    }

    return count;
}
