#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from, to;
    int cost;
};

class Graph {
public:
    Graph(int size): size(size) {};

    void addEdge(int from, int to, int cost) {
        edges.push_back({from, to, cost});
    }

    bool isNegativeCycle() {
        distances = vector<int>(size, 50000001);
        distances[0] = 0;

        for (int v=0; v<size-1; v++) {
            for (Edge &edge : edges) {
                int cur = distances[edge.to];
                int dist = distances[edge.from] + edge.cost;

                if (cur > dist) distances[edge.to] = dist;
            }
        }

        for (Edge &edge : edges) {
            int cur = distances[edge.to];
            int dist = distances[edge.from] + edge.cost;

            if (cur > dist) return true;
        }

        return false;
    }
private:
    int size;
    vector<int> distances;
    vector<Edge> edges;
};

int main() {
    int cases;
    cin >> cases;

    for (int i=0; i<cases; i++) {
        int nodes, roads, warmholes;
        cin >> nodes >> roads >> warmholes;
        
        Graph g(nodes);
        for (int j=0; j<roads; j++) {
            int from, to, cost;
            cin >> from >> to >> cost;

            g.addEdge(from-1, to-1, cost);
            g.addEdge(to-1, from-1, cost);
        }

        for (int j=0; j<warmholes; j++) {
            int from, to, cost;
            cin >> from >> to >> cost;

            g.addEdge(from-1, to-1, -1 * cost);
        }

        bool isCycle = g.isNegativeCycle();
        if (isCycle) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}