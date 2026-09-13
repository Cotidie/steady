#include <iostream>
#include <vector>

using namespace std;

struct Shark {
    int speed = 0;
    int dir = 0;
    int size = 0;
};

struct Cell {
    Shark *arrived = nullptr;
    Shark *shark = nullptr;
};

struct Fisher {
    int col;
    int score;
};

class Board {
public:
    Board(int rows, int cols) {
        board = vector<vector<Cell>>(rows+1, vector<Cell>(cols+1));
        fisher = Fisher{0, 0};
    }

    void set(int row, int col, int speed, int dir, int size) {
        board[row][col].shark = new Shark{speed, dir, size};
    }

    int play() {
        for (int i=0; i<cols(); i++) {
            moveFisher();
            catchShark();
            moveSharks();
            commitSharks();
        }

        return fisher.score;
    }

    int rows() {return board.size()-1;}
    int cols() {return board[0].size()-1;}
private:
    void moveFisher() {
        fisher.col += 1;
    }

    void catchShark() {
        int col = fisher.col;
        for (int r=1; r<board.size(); r++) {
            if (board[r][col].shark == nullptr) continue;

            fisher.score += board[r][col].shark->size;
            board[r][col].shark = nullptr;
            break;
        }
    }

    void moveSharks() {
        for (int r=1; r<board.size(); r++) {
            for (int c=1; c<board[0].size(); c++) {
                if (board[r][c].shark == nullptr) continue;

                moveShark(r, c);
            }
        }
    }

    void moveShark(int row, int col) {
        Shark *shark = board[row][col].shark;
        board[row][col].shark = nullptr;

        int turns = clipTurns(shark->speed, shark->dir);
        while (turns > 0) {
            row += moves[shark->dir][0];
            col += moves[shark->dir][1];

            if (!isInBound(row, col)) {
                shark->dir = flipDirection(shark->dir);
                row += 2 * moves[shark->dir][0];
                col += 2 * moves[shark->dir][1];
            }

            turns--;
        }

        if (board[row][col].arrived == nullptr || board[row][col].arrived->size < shark->size) {
            board[row][col].arrived = shark;
        }
    }

    int clipTurns(int speed, int dir) {
        if (dir == 3 || dir == 4) {
            return speed % (2*cols()-2);
        } else {
            return speed % (2*rows()-2);
        }
    }

    void commitSharks() {
        for (int r=1; r<board.size(); r++) {
            for (int c=1; c<board[0].size(); c++) {
                if (board[r][c].arrived == nullptr) continue;

                board[r][c].shark = board[r][c].arrived;
                board[r][c].arrived = nullptr;
            }
        }
    }

    bool isInBound(int row, int col) {
        return (row > 0 && row < board.size()) &&
            (col > 0 && col < board[0].size());
    }

    int flipDirection(int dir) {
        if (dir==1) return 2;
        if (dir==2) return 1;
        if (dir==3) return 4;
        if (dir==4) return 3;
        
        return 0;
    }

    vector<vector<Cell>> board;
    Fisher fisher;

    vector<vector<int>> moves = {
        {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}
    };
};

int main() {
    int rows, cols, sharks;
    cin >> rows >> cols >> sharks;

    Board board(rows, cols);
    for (int i=0; i<sharks; i++) {
        int row, col, size, speed, dir;
        cin >> row >> col >> speed >> dir >> size;

        board.set(row, col, speed, dir, size);
    }

    cout << board.play() << '\n';
}