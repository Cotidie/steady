#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int row, col;
};

class Graph {
public:
    Graph(int rows, int cols): rows(rows), cols(cols) {
        graph = vector<vector<int>>(rows, vector<int>(cols, 0));
    }

    void set(int row, int col, int val) {
        graph[row][col] = val;
        if (val == 1) cheeses++;
    }

    void next() {
        auto visited = vector<vector<bool>>(rows, vector<bool>(cols, false));
        auto exposed = vector<vector<int>>(rows, vector<int>(cols, 0));
        visited[0][0] = true;

        queue<Point> q;
        q.push({0, 0});

        while (!q.empty()) {
            Point cur = q.front();
            q.pop();

            for (const vector<int> &move : moves) {
                int dRow = cur.row + move[0];
                int dCol = cur.col + move[1];

                if (isOutBound(dRow, dCol)) continue;
                if (visited[dRow][dCol]) continue;
                if (graph[dRow][dCol] == 1) {
                    exposed[dRow][dCol] += 1;
                    continue;
                }

                visited[dRow][dCol] = true;
                q.push({dRow, dCol});
            }
        }

        for (int r=0; r<rows; r++) {
            for (int c=0; c<cols; c++) {
                if (exposed[r][c] < 2) continue;

                cheeses--;
                graph[r][c]=0;
            }
        }

        hours++;
    }

    int getCheeses() {return cheeses;}
    int getHours() {return hours;}
private:
    bool isOutBound(int row, int col) {
        return (row < 0 || col < 0) ||
            (row >= rows || col >= cols);
    }

    int rows, cols;
    int cheeses=0;
    int hours = 0;
    
    vector<vector<int>> graph;

    const vector<vector<int>> moves = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int rows, cols;
    cin >> rows >> cols;

    Graph graph(rows, cols);
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            int val;
            cin >> val;

            graph.set(r, c, val);
        }
    }

    while (graph.getCheeses() != 0) {
        graph.next();
    }

    cout << graph.getHours() << '\n';
} 