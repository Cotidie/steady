#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INTMAX = 600001;

class Edge {
public:
    Edge() {};
    Edge(int from, int to, int cost): from(from), to(to), cost(cost) {};

    int from = 0;
    int to = 0;
    int cost = 0;
};

class EdgeCompare {
public:
    bool operator()(Edge& edge1, Edge& edge2) {
        return edge1.cost > edge2.cost;
    }
};

class Graph {
public:
    Graph(vector<vector<int>>& times, int size) {
        graph = vector<vector<Edge>>(size);
        
        for (auto time : times) {
            int source = time[0]-1;
            int dest = time[1]-1;
            int cost = time[2];

            Edge edge = Edge(source, dest, cost);
            graph[source].push_back(edge);
        }
    };

    int getShortestDelay(int source) {
        source--;
        vector<bool> verified = vector<bool>(graph.size(), false);
        vector<int> distances = vector<int>(graph.size(), INTMAX);
        priority_queue<Edge, vector<Edge>, EdgeCompare> pq;

        distances[source] = 0;
        pq.push(Edge(source, source, 0));

        while (!pq.empty()) {
            Edge current = pq.top(); pq.pop();
            if (verified[current.to]) continue;

            verified[current.to] = true;

            for (Edge edge : graph[current.to]) {
                int curDist = distances[edge.to];
                int newDist = distances[edge.from] + edge.cost;

                distances[edge.to] = min(curDist, newDist);
                pq.push(
                    Edge(
                        source, 
                        edge.to, 
                        distances[edge.to]
                    )
                );
            }
        }

        int maxDelay = distances[0];
        for (int i=1; i<distances.size(); i++) {
            maxDelay = max(distances[i], maxDelay);
        }

        return (maxDelay == INTMAX) ? -1 : maxDelay;
    }

private:
    vector<vector<Edge>> graph;
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        Graph g(times, n);

        return g.getShortestDelay(k);
    }
};

int main() {
    Solution s;

    vector<vector<int>> times;
    int n, k;
    
    // 2
    times = {{2,1,1},{2,3,1},{3,4,1}};
    n = 4; k = 2;
    cout << s.networkDelayTime(times, n, k) << endl;

    // 1
    times = {{1, 2, 1}};
    n = 2; k = 1;
    cout << s.networkDelayTime(times, n, k) << endl;

    // -1
    times = {{1, 2, 1}};
    n = 2; k = 2;
    cout << s.networkDelayTime(times, n, k) << endl;

    // 59
    times = {{4,2,76},{1,3,79},{3,1,81},{4,3,30},{2,1,47},{1,5,61},{1,4,99},{3,4,68},{3,5,46},{4,1,6},{5,4,7},{5,3,44},{4,5,19},{2,3,13},{3,2,18},{1,2,0},{5,1,25},{2,5,58},{2,4,77},{5,2,74}};
    n = 5; k = 3;
    cout << s.networkDelayTime(times, n, k) << endl;
}