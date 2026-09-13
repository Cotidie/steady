#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int to, weight;
};

struct Pair {
    int num;
    int dist;
};

class Compare {
public:
    bool operator()(const Pair& left, const Pair& right) const {
        return left.dist > right.dist;
    }
};

class Graph {
public:
    Graph(int size) {
        graph = vector<vector<Edge>>(size, vector<Edge>());
    }

    void set(int val, int from, int to) {
        graph[from].push_back(Edge{to, val});
    }

    void dijkstra(int num) {
        vector<int> result = vector<int>(graph.size(), -1);
        priority_queue<Pair, vector<Pair>, Compare> pq;
        pq.push(Pair{num, 0});
        result[num] = 0;

        while (!pq.empty()) {
            Pair cur = pq.top();
            pq.pop();

            if (cur.dist > result[cur.num]) continue;

            for (auto edge : graph[cur.num]) {
                int dist = cur.dist + edge.weight;
                if (result[edge.to] < 0) result[edge.to] = dist;
                if (result[edge.to] < dist) continue;

                pq.push(Pair{edge.to, dist});
                result[edge.to] = dist;
            }
        }

        for (int dist : result) {
            if (dist == -1) cout << "INF" << '\n';
            else cout << dist << endl;
        }
    }

private:
    vector<vector<Edge>> graph;
};

int main() {
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int V, E;
    cin >> V >> E;

    int start;
    cin >> start;

    Graph graph(V);
    for (int i=0; i<E; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
    
        graph.set(weight, from-1, to-1);
    }

    graph.dijkstra(start-1);
}