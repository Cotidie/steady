#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Travel {
    int row, col;
    int cost;
    int canBreak;
};

class Board {
public:
    Board(int rows, int cols): rows(rows), cols(cols) {
        board = vector<string>(rows, "");
    }

    void set(int row, string cols) {
        board[row] = cols;
    }

    int bfs() {
        auto visited = vector<vector<vector<bool>>>(
                rows, 
                vector<vector<bool>>(
                    cols,
                    vector<bool>(2, false)
                )
            );
        
        queue<Travel> q;
        q.push(Travel{0, 0, 1, 1});
        visited[0][0][0] = true;

        while (!q.empty()) {
            Travel cur = q.front();
            q.pop();

            if (cur.row == rows-1 && cur.col == cols-1) return cur.cost;

            for (auto dir : dirs) {
                int dRow = cur.row + dir[0];
                int dCol = cur.col + dir[1];

                if (!isValid(dRow, dCol)) continue;
                if (visited[dRow][dCol][cur.canBreak]) continue;
                if (board[dRow].at(dCol) == '1' && cur.canBreak == 0) continue;
                if (board[dRow].at(dCol) == '1' && cur.canBreak == 1) {
                    q.push(Travel{dRow, dCol, cur.cost+1, 0});
                    visited[dRow][dCol][0] = true;
                }
                if (board[dRow].at(dCol) == '0') {
                    q.push(Travel{dRow, dCol, cur.cost+1, cur.canBreak});
                    visited[dRow][dCol][cur.canBreak] = true;
                }
            }
        }

        return -1;
    }

private:
    bool isValid(int row, int col) {
        return (row >= 0 && col >= 0) &&
            (row < rows && col < cols);
    }

    int rows, cols;
    vector<string> board;

    const vector<vector<int>> dirs = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };
};

int main() {
    int rows, cols;
    cin >> rows >> cols;

    Board board(rows, cols);
    for (int i=0; i<rows; i++) {
        string col;
        cin >> col;

        board.set(i, col);
    }

    cout << board.bfs() << '\n';
}