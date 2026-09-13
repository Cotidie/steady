#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Pair {
    int city;
    int cost;
};

struct Edge {
    int to;
    int cost;
};

class Compare {
public:
    bool operator()(const Pair &left, const Pair &right) {
        return left.cost > right.cost;
    }
};

class Graph {
public:
    Graph(int num) {
        cities = vector<vector<Edge>>(num, vector<Edge>());
    }

    void set(int from, int to, int val) {
        cities[from].push_back(Edge{to, val});
    }

    vector<int> dijkstra(int start) {
        vector<int> distances = vector<int>(cities.size(), 1000001);
        priority_queue<Pair, vector<Pair>, Compare> pq;
        pq.push(Pair{start, 0});

        while (!pq.empty()) {
            Pair cur = pq.top();
            pq.pop();

            if (distances[cur.city] < cur.cost) continue;

            for (Edge edge : cities[cur.city]) {
                int dCost = cur.cost + edge.cost;
                if (distances[edge.to] <= dCost) continue;

                distances[edge.to] = dCost;
                pq.push(Pair{edge.to, dCost});
            }
        }

        return distances;
    }

private:
    vector<vector<Edge>> cities;
};

int main() {
    int students, roads, city;
    cin >> students >> roads >> city;

    Graph graph(students);
    for (int i=0; i<roads; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        graph.set(from-1, to-1, cost);
    }

    auto wayHome = graph.dijkstra(city-1);

    for (int i=0; i<students; i++) {
        if (i == city-1) continue;
        auto wayParty = graph.dijkstra(i);
        wayHome[i] += wayParty[city-1]; 
    }

    cout << *max_element(wayHome.begin(), wayHome.end()) << '\n';
}