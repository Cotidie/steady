#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pair {
    int node;
    int cost;   
};

struct Edge {
    int to;
    int cost;
};

class Ascending {
public:
    bool operator()(const Pair &left, const Pair &right) {
        return left.cost > right.cost;
    }
};

class Graph {
public:
    Graph(int size) {
        graph = vector<vector<Edge>>(size+1, vector<Edge>());
    }

    void set(int from, int to, int cost) {
        graph[from].push_back({to, cost});
    }

    vector<vector<int>> dijkstra(int start) {
        // [][0]: 최단거리, [][1]: 직전 방문노드
        auto result = vector<vector<int>>(graph.size()+1, vector<int>(2));
        for (int i=0; i<graph.size(); i++) {
            result[i][0] = -1;
            result[i][1] = -1;
        }
        result[start][0] = 0;
        result[start][1] = start;

        priority_queue<Pair, vector<Pair>, Ascending> pq;
        pq.push({start, 0});

        while (!pq.empty()) {
            Pair cur = pq.top();
            pq.pop();

            if (result[cur.node][0] > 0 && cur.cost > result[cur.node][0]) continue;

            for (Edge &edge : graph[cur.node]) {
                int curDist = result[edge.to][0];
                int newDist = cur.cost + edge.cost;
                if (curDist >= 0 && curDist <= newDist) continue;

                result[edge.to][0] = newDist;
                result[edge.to][1] = cur.node;
                pq.push({edge.to, newDist});
            }
        }

        return result;
    } 
private:
    vector<vector<Edge>> graph;
};

int main() {
    int cities, buses;
    cin >> cities >> buses;

    Graph graph(cities);
    for (int i=0; i<buses; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        graph.set(from, to, cost);
    }
    
    int start, end;
    cin >> start >> end;
    
    auto dijkstra = graph.dijkstra(start);

    cout << dijkstra[end][0] << '\n';

    vector<int> path; path.push_back(end);
    int node = end;
    while (node != start) {
        path.push_back(dijkstra[node][1]);
        node = dijkstra[node][1];
    }

    cout << path.size() << '\n';
    for (int i=path.size()-1; i>=0; i--) {
        cout << path[i] << " ";
    }
}