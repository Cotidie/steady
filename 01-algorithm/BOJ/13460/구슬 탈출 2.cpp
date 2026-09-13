#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct Point {
    int row, col;
};

struct Balls {
    Point red;
    Point blue;
};

struct Pair {
    Balls balls;
    int cnt=0;
};

class Mover {
public:
    Mover(vector<vector<char>> &board): board(board) {};


    bool lean(Point& red, Point& blue, int dir) {
        bool bFinished = false;
        bool rFinished = false;
        bool bEscaped = false;
        bool rEscaped = false;
        
        Point cBlue = {blue.row, blue.col};
        Point cRed = {red.row, red.col};
        while (!bFinished || !rFinished) {
            if (!bFinished) move(cBlue, dir);
            if (!rFinished) move(cRed, dir);

            if (get(cBlue) == '#') {
                bFinished = true;
                moveBack(cBlue, dir);
            }
            if (get(cRed) == '#') {
                rFinished = true;
                moveBack(cRed, dir);
            }
            if (get(cBlue) == 'O') {
                bFinished = true;
                bEscaped = true;
            }
            if (get(cRed) == 'O') {
                rFinished = true;
                rEscaped = true;
            }
        }

        if (bEscaped && rEscaped) return false;
        if (bEscaped) return false;

        if (cRed.row == cBlue.row && cRed.col == cBlue.col) {
            int rMoved = moved(red, cRed, dir);
            int bMoved = moved(blue, cBlue, dir);

            if (rMoved > bMoved)        moveBack(cRed, dir);
            else if (rMoved < bMoved)   moveBack(cBlue, dir);
            else                        return false;
        }

        red.row = cRed.row; red.col = cRed.col;
        blue.row = cBlue.row; blue.col = cBlue.col;

        return true;
    }
private:
    char get(const Point &p) {
        return board[p.row][p.col];
    }

    void move(Point &p, int dir) {
        p.row += moves[dir][0];
        p.col += moves[dir][1];
    }

    void moveBack(Point &p, int dir) {
        p.row -= moves[dir][0];
        p.col -= moves[dir][1];
    }

    int moved(Point &origin, Point &moved, int dir) {
        if (dir == 0) return origin.row - moved.row;
        if (dir == 1) return moved.row - origin.row;
        if (dir == 2) return origin.col - moved.col;
        if (dir == 3) return moved.col - origin.col;

        return 0;
    }

    vector<vector<char>> &board;
    vector<vector<int>> moves = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };
};

class Board {
public:
    Board(int rows, int cols) {
        board = vector<vector<char>>(rows, vector<char>(cols, '#'));
    }

    void set(int row, int col, char val) {
        board[row][col] = val;

        if (val == 'R') red = {row, col};
        if (val == 'B') blue = {row, col};
    }

    char get(int row, int col) { return board[row][col]; }

    int play() {
        auto visited = vector<vector<vector<vector<bool>>>>(
            board.size(), vector<vector<vector<bool>>>(
                board[0].size(), vector<vector<bool>>(
                     board.size(), vector<bool>(
                        board[0].size(), false
                     )
                )
            )
        );
        Mover mover(board);
        
        queue<Pair> q;
        q.push({Balls{red, blue}, 0});
        visited[red.row][red.col][blue.row][blue.col] == true;
        while (!q.empty()) {
            Pair cur = q.front(); q.pop();

            if (get(cur.balls.red.row, cur.balls.red.col) == 'O') return cur.cnt;
            visited[cur.balls.red.row][cur.balls.red.col][cur.balls.blue.row][cur.balls.blue.col] = true;
            if (cur.cnt >= 10) continue;

            for (int dir=0; dir<4; dir++) {
                Point cRed = cur.balls.red;
                Point cBlue = cur.balls.blue;
                bool moved = mover.lean(cRed, cBlue, dir);
                if (visited[cRed.row][cRed.col][cBlue.row][cBlue.col]) continue;
                if (moved) q.push({Balls{cRed, cBlue}, cur.cnt+1});
            }
        }

        return -1;
    }


private:
    Point red;
    Point blue;

    vector<vector<char>> board;
};

int main() {
    int rows, cols;
    cin >> rows >> cols;

    Board board(rows, cols);
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            char val;
            cin >> val;

            board.set(r, c, val);
        }
    }

    cout << board.play() << '\n';
}