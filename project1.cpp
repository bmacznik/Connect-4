#include <iostream>
#include <vector>
// connect 4
const int ROWS = 6;
const int COLS = 7;
const int WIN_CONDITION = 4;
class ConnectFour {
public:
    ConnectFour() {
        board.resize(ROWS, std::vector<char>(COLS, ' '));
    }
    void playGame() {
        char player = 'X';
        bool gameOver = false;
        int moveCount = 0;
        
		while (!gameOver && moveCount < ROWS * COLS) {
            displayBoard();
            int col;
            std::cout << "Player " << player << ", enter column (0-" << COLS-1 << "): ";
            std::cin >> col;	
            
            if (makeMove(player, col)) {
                moveCount++;
                if (checkWin(player)) {
                    displayBoard();
                    std::cout << "Player " << player << " wins!\n";
                    gameOver = true;
                } else {
                    player = (player == 'X') ? 'O' : 'X';
                }
            } else {
                std::cout << "Invalid move. Try again.\n";
            }
    }
        
		if (!gameOver) {
            displayBoard();
            std::cout << "It's a draw!\n";
        }
    }
private:
    std::vector<std::vector<char>> board;
    void displayBoard() {
        for (const auto& row : board) {
            for (char cell : row) {
                std::cout << "|" << cell;
            }
            std::cout << "|\n";
        }
        for (int i = 0; i < COLS; i++) {
            std::cout << " " << i;
        }
        std::cout << "\n";
    }
    bool makeMove(char player, int col) {
        if (col < 0 || col >= COLS || board[0][col] != ' ') {
            return false;
        }

        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] == ' ') {
                board[row][col] = player;
                return true;
            }
        }
        return false;
    }
    bool checkWin(char player) {
        // horizontal
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col <= COLS - WIN_CONDITION; col++) {
                if (checkDirection(player, row, col, 0, 1)) {
                    return true;
                }
            }
        }
        // vertical
        for (int row = 0; row <= ROWS - WIN_CONDITION; row++) {
            for (int col = 0; col < COLS; col++) {
                if (checkDirection(player, row, col, 1, 0)) {
                    return true;
                }
            }
        }
        // diagonal (/)
        for (int row = 0; row <= ROWS - WIN_CONDITION; row++) {
            for (int col = 0; col <= COLS - WIN_CONDITION; col++) {
                if (checkDirection(player, row, col, 1, 1)) {
                    return true;
                }
            }
        }
        // diagonal (\)
        for (int row = 0; row <= ROWS - WIN_CONDITION; row++) {
            for (int col = WIN_CONDITION - 1; col < COLS; col++) {
                if (checkDirection(player, row, col, 1, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool checkDirection(char player, int startRow, int startCol, int deltaRow, int deltaCol) {
        for (int i = 0; i < WIN_CONDITION; i++) {
            if (board[startRow + i * deltaRow][startCol + i * deltaCol] != player) {
                return false;
            }
        }
        return true;
    }
};
int main() {
    ConnectFour game;
    game.playGame();
    return 0;
}
