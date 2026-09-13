#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pair {
    int row, col;
    int cost;
};

class Shark {
public:
    bool isMovable(int size) {return size <= this->size;}
    bool isEatable(int size) {return size > 0 && size < this->size;}
    void eat() {
        ate++;

        if (ate >= size) {
            size++;
            ate = 0;
        }
    }
    void move(int row, int col) {
        this->row = row;
        this->col = col;
    }

    int row, col;
private:
    int size = 2;
    int ate = 0;
};

class Graph {
public:
    Graph(int size) {
        graph = vector<vector<int>>(size, vector<int>(size, 0));
    }

    void set(int row, int col, int val) {
        graph[row][col] = val;

        if (val == 9) {
            shark.move(row, col);
            graph[row][col] = 0;
        } else if (val > 0) numFishes++;
    }

    vector<Pair> bfs() {
        vector<Pair> fishes;
        vector<vector<bool>> visited = vector<vector<bool>>(graph.size(), vector<bool>(graph.size(), false));
        
        queue<Pair> q;
        q.push({shark.row, shark.col, 0});

        int dist = 10000;
        while (!q.empty()) {
            Pair cur = q.front();
            q.pop();

            if (cur.cost > dist) continue;
            if (shark.isEatable(graph[cur.row][cur.col])) {
                dist = min(dist, cur.cost);
                fishes.push_back(cur);
                continue;
            }

            for (const vector<int> &move : moves) {
                int dRow = cur.row + move[0];
                int dCol = cur.col + move[1];

                if (isOutBound(dRow, dCol)) continue;
                if (visited[dRow][dCol]) continue;

                int val = graph[dRow][dCol];
                if (!shark.isMovable(val)) continue;
                
                q.push({dRow, dCol, cur.cost+1});
                visited[dRow][dCol] = true;
            }
        }

        return fishes;
    }

    void eat(int row, int col) {
        graph[shark.row][shark.col] = 0;
        graph[row][col] = 0;
        numFishes--;

        shark.move(row, col);
        shark.eat();
    }

    int getFishes() { return numFishes; } 
private:
    bool isOutBound(int row, int col) {
        return (row < 0 || col < 0) ||
            (row >= graph.size() || col >= graph.size());
    }

    vector<vector<int>> graph;
    Shark shark;
    int numFishes = 0;

    const vector<vector<int>> moves = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
};

int main() {
    int size; 
    cin >> size;

    Graph graph(size);
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            int val;
            cin >> val;

            graph.set(r, c, val);
        }
    }

    vector<Pair> fishes = graph.bfs();
    int dist = 0;
    while (graph.getFishes() > 0 && fishes.size() > 0) {
        Pair fish = fishes[0];

        for (int i=1; i<fishes.size(); i++) {
            if (fishes[i].row < fish.row) fish = fishes[i];
            else if (fishes[i].row == fish.row) {
                if (fishes[i].col < fish.col) fish = fishes[i];
            }
        }

        graph.eat(fish.row, fish.col);
        dist += fish.cost;

        fishes = graph.bfs();
    }

    cout << dist << '\n';
}