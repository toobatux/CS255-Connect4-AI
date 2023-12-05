#include "Connect4.h"
#include <iostream>
#include <chrono>

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

void Connect4::chooseFirstPlayer() {
    std::cout << "Who would you like to play first? (Enter '1' for Player or '2' for AI): ";
    int choice;
    std::cin >> choice;

    while (choice != 1 && choice != 2) {
        std::cout << "Invalid choice. Please enter '1' for Player or '2' for AI: ";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> choice;
    }

    currentPlayer = (choice == 1) ? PLAYER : AI;
}

void Connect4::playGame(int maxTimeSeconds)
{
    chooseFirstPlayer();

    bool gameDone = false;

    while (!gameDone) {
        this->printBoard();
        if (currentPlayer == PLAYER) {
            this->makeMove(userMove(), PLAYER);
        }
        else if (currentPlayer == AI) {
            this->makeMove(aiMove(maxTimeSeconds), AI);
        }

        //this->makeMove(userMove(turns), currentPlayer);

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
            turns++;
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
                if (count >= 4) {
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
                if (count >= 4) {
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
                if (count >= 4) {
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
                if (count >= 4) {
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
    clone.turns = turns;

    return clone;
}


// AI methods
int Connect4::aiMove(int maxTimeSeconds)
{
    std::cout << "AI is choosing a move...\n";

    std::vector<int> priorityOrder = calculatePriority();
    int bestMove = -1;
    int bestEval = INT_MIN;

    std::cout << "Evaluation values for each column:" << std::endl;

    for (int c : priorityOrder) {
        if (isValidMove(c)) {
            Connect4 clone = this->copy();
            clone.makeMove(c, AI);

            int eval = minimax(clone, 8, INT_MIN, INT_MAX, false, std::chrono::high_resolution_clock::now(), maxTimeSeconds);

            std::cout << "Column " << c << " - Value: " << eval << std::endl;

            if (eval > bestEval) {
                bestEval = eval;
                bestMove = c;
            }
        }
    }

    return bestMove;

}

int Connect4::bestMoveWithinTime(int maxTimeSeconds) {
    auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = startTime;

    std::vector<int> priorityOrder = calculatePriority();
    int bestMove = -1;
    int bestEval = INT_MIN;

    for (int c : priorityOrder) {
        currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        if (elapsedTime >= maxTimeSeconds) {
            break;
        }


        if (isValidMove(c)) {
            Connect4 clone = this->copy();
            clone.makeMove(c, AI);

            if (clone.checkWin()) {
                return c;
            }
            else if (OppWinPosInColumn(c)) {
                return c;
            }
            else {
                int eval = minimax(clone, 11, INT_MIN, INT_MAX, false, startTime, maxTimeSeconds);
                if (eval > bestEval) {
                    bestEval = eval;
                    bestMove = c;
                }
            }
        }
    }

    return bestMove;
}

std::vector<int> Connect4::calculatePriority() {
    std::vector<int> priorityOrder;

    // Prioritize winning moves for AI and blocking moves for the opponent
    for (int c = 0; c < numColumns; ++c) {
        if (isValidMove(c)) {
            Connect4 clone = this->copy();
            clone.makeMove(c, AI);
            if (clone.checkWin()) {
                priorityOrder.push_back(c);
                return priorityOrder;
            }
            // Prioritize blocking moves for the opponent
            clone = this->copy();
            clone.makeMove(c, PLAYER);
            if (clone.checkWin()) {
                priorityOrder.push_back(c);
            }
        }
    }

    // Handle the center column separately based on conditions
    int centerColumn = numColumns / 2;
    if (isValidMove(centerColumn)) {
        priorityOrder.push_back(centerColumn);
    }

    // Prioritize other columns after the first move
    for (int c = 0; c < numColumns; ++c) {
        if (c != centerColumn && isValidMove(c)) {
            priorityOrder.push_back(c);
        }
    }

    return priorityOrder;
}

int Connect4::minimax(Connect4& game, int depth, int alpha, int beta, bool maximizingPlayer, std::chrono::high_resolution_clock::time_point startTime, int maxTimeSeconds) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

    if (depth == 0 || game.checkWin() || game.isBoardFull() || elapsedTime >= maxTimeSeconds) {
        return evaluate(game, AI);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int c = 0; c < game.numColumns; c++) {
            if (game.isValidMove(c)) {
                Connect4 clone = game.copy();
                clone.makeMove(c, AI);
                int eval = minimax(clone, depth - 1, alpha, beta, false, startTime, maxTimeSeconds);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) {
                    break; // Beta cut-off
                }
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
                int eval = minimax(clone, depth - 1, alpha, beta, true, startTime, maxTimeSeconds);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break; // Alpha cut-off
                }
            }
        }
        return minEval;
    }
}

int Connect4::evaluate(Connect4& game, int player) {
    int aiScore = evaluatePlayer(game, AI, player);
    int playerScore = evaluatePlayer(game, PLAYER, player);

    return aiScore - playerScore;
}

int Connect4::evaluatePlayer(Connect4& game, int playerToCheck, int currentPlayer) {
    int score = 0;

    // Evaluate rows and columns
    for (int r = 0; r < game.numRows; r++) {
        for (int c = 0; c < game.numColumns; c++) {
            score += evaluatePosition(game, r, c, playerToCheck, currentPlayer);
        }
    }

    // Evaluate diagonals
    for (int r = 0; r < game.numRows; r++) {
        for (int c = 0; c < game.numColumns; c++) {
            score += evaluateDiagonal(game, r, c, playerToCheck, currentPlayer);
        }
    }

    return score;
}

int Connect4::evaluatePosition(Connect4& game, int row, int col, int playerToCheck, int currentPlayer) {
    int score = 0;
    int weight = 1;

    // Check horizontally
    score += evaluateLine(game, row, col, 0, 1, playerToCheck, currentPlayer, weight);

    // Check vertically
    score += evaluateLine(game, row, col, 1, 0, playerToCheck, currentPlayer, weight);

    // Check diagonally (positive slope)
    score += evaluateLine(game, row, col, 1, 1, playerToCheck, currentPlayer, weight);

    // Check diagonally (negative slope)
    score += evaluateLine(game, row, col, 1, -1, playerToCheck, currentPlayer, weight);

    return score;
}

// Adjust weights and scores within evaluateLine function
int Connect4::evaluateLine(Connect4& game, int row, int col, int deltaRow, int deltaCol, int playerToCheck, int currentPlayer, int weight) {
    int score = 0;
    int tokens = 0;
    int empty = 0;

    for (int i = 0; i < 4; i++) {
        int r = row + i * deltaRow;
        int c = col + i * deltaCol;

        if (r >= 0 && r < game.numRows && c >= 0 && c < game.numColumns) {
            if (game.board[r][c] == playerToCheck) {
                tokens++;
            }
            else if (game.board[r][c] == EMPTY) {
                empty++;
            }
        }
    }

    if (tokens == 4) {
        score += 10000; // Winning position
    }
    else if (tokens == 3 && empty == 1) {
        score += 20; // Potential winning position

        // Adjust score based on the threat of opponent winning
        if (playerToCheck == PLAYER) {
            score += 100;
        }
    }
    else if (tokens == 2 && empty == 2) {
        score += 6; // Good position

        // Add more weight to AI's potential winning positions
        if (playerToCheck == AI) {
            score += 2;
        }
    }
    else if (tokens == 1 && empty == 3) {
        score += 3; // Single token with three empty spaces
    }

    return score;
}

int Connect4::evaluateDiagonal(Connect4& game, int row, int col, int playerToCheck, int currentPlayer) {
    int score = 0;

    score += evaluateLine(game, row, col, 1, 1, playerToCheck, currentPlayer, 1); // Positive slope
    score += evaluateLine(game, row, col, 1, -1, playerToCheck, currentPlayer, 1); // Negative slope

    return score;
}

int Connect4::countWinPos(int player)
{
    int count = 0;

    for (int c = 0; c < numColumns; c++) {
        if (isValidMove(c)) {
            Connect4 clone = this->copy();
            clone.makeMove(c, player);
            if (clone.checkWin()) {
                count++;
            }
        }
    }

    return count;
}

bool Connect4::OppWinPosInColumn(int column)
{
    if (isValidMove(column)) {
        Connect4 clone = this->copy();
        clone.makeMove(column, PLAYER);
        //clone.printBoard();
        bool isOppWinning = clone.checkWin();
        //std::cout << "Opponent winning position in column " << column << ": " << (isOppWinning ? "Yes" : "No") << std::endl;
        return isOppWinning;
    }
    return false;
}
