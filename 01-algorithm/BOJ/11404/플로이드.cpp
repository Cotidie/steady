#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int size) {
        graph = vector<vector<int>>(size, vector<int>(size, -1));
        for (int i=0; i<size; i++) {
            graph[i][i] = 0;
        }
    }

    void set(int cost, int from, int to) {
        int prev = graph[from][to];
        if (prev == -1) graph[from][to] = cost;
        if (prev > cost) graph[from][to] = cost;
    }

    void floyd() {
        for (int k=0; k<graph.size(); k++) {
            for (int r=0; r<graph.size(); r++) {
                if (k==r) continue;

                for (int c=0; c<graph.size(); c++) {
                    if (k==c) continue;

                    int direct = graph[r][c];
                    int medium1 = graph[r][k];
                    int medium2 = graph[k][c];

                    if (medium1 == -1 || medium2 == -1) continue;

                    if (direct == -1) graph[r][c] = medium1+medium2;
                    else if (direct > medium1 + medium2) graph[r][c] = medium1+medium2;
                }
            }
        }
    }

    vector<vector<int>> getGraph() {
        return graph;
    }

private:
    vector<vector<int>> graph;
};

int main() {
    int n;
    cin >> n;

    int buses;
    cin >> buses;

    Graph graph(n);
    for (int i=0; i<buses; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        graph.set(cost, from-1, to-1);
    }

    graph.floyd();
    
    for (auto row : graph.getGraph()) {
        for (auto col : row) {
            if (col == -1) col = 0;
            cout << col << " ";
        }

        cout << '\n';
    }
}