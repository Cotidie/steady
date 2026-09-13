#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int rows, int cols) {
        graph = vector<vector<int>>(rows, vector<int>(cols));
        this->rowSize = rows;
        this->colSize = cols;
    }

    void set(int val, int row, int col) {
        graph[row][col] = val;
    }

    int get(int row, int col) {
        return graph[row][col];
    }

    int rows() { return rowSize; }
    int cols() { return colSize; }

private:
    vector<vector<int>> graph;
    int rowSize, colSize;
};

class DFS {
public:
    DFS(Graph& graph):graph(graph) {
        visited = vector<vector<bool>>(graph.rows(), vector<bool>(graph.cols(), false));
    };

    int search(int row, int col) {
        maxSum = 0;

        dfs(row, col, graph.get(row, col), 1);

        return maxSum;
    }
private:
    void dfs(int row, int col, int sum, int depth) {
        if (depth == 4) {
            maxSum = max(maxSum, sum);
            return;
        }

        visited[row][col] = true;
        for (auto move : moves) {
            int dr = row + move[0];
            int dc = col + move[1];

            if (dr < 0 || dc < 0) continue;
            if (dr >= graph.rows() || dc >= graph.cols()) continue;
            if (visited[dr][dc]) continue;

            int num = graph.get(dr, dc);
            dfs(dr, dc, sum + num, depth+1);
        }
        visited[row][col] = false;
    }

    Graph& graph;
    vector<vector<bool>> visited;
    const vector<vector<int>> moves = {
        {1, 0}, {-1, 0},
        {0, 1}, {0, -1}
    };
    int maxSum = 0;
};

class BlockSum {
public:
    BlockSum(Graph& g): graph(g) {};

    int getSum(int row, int col) {
        int maxSum = 0;
        
        for (int mirror : vector<int>{1, -1}) {
            for (auto moves : shapes) {
                int sum = 0;
                for (auto move : moves) {
                    int dr = row + move[0] * mirror;
                    int dc = col + move[1] * mirror;

                    if (!isInRange(dr, dc)) {
                        sum = -1;
                        break;
                    }

                    sum += graph.get(dr, dc);
                }
                if (maxSum < sum) maxSum = sum;
            }
        }

        return maxSum;
    }

    bool isInRange(int row, int col) {
        return (row >= 0 && col >= 0) && 
            (row < graph.rows() && col < graph.cols());
    }

private:
    Graph& graph;

    vector<vector<vector<int>>> shapes {
        { {0, 0}, {1, 0}, {2, 0}, {1, 1} },  // ㅏ
        { {0, 0}, {1, 0}, {2, 0}, {1, -1}},  // ㅓ
        { {0, 0}, {0, 1}, {0, 2}, {1, 1} },  // ㅜ
        { {0, 0}, {0, 1}, {0, 2}, {-1, 1}},  // ㅗ
    };
};

int main() {
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int rows, cols;
    cin >> rows >> cols;

    Graph g(rows, cols);
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            int val;
            cin >> val;

            g.set(val, r, c);
        }
    }

    DFS dfs(g);
    BlockSum block(g);

    int maxSum = 0;
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            maxSum = max(maxSum, dfs.search(r, c));
            maxSum = max(maxSum, block.getSum(r, c));
        }
    }

    cout << maxSum << '\n';
}