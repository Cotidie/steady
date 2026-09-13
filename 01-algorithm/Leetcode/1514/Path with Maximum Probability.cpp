#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Pair {
public:
    Pair(int node, double prob):node(node), prob(prob) {};

    bool operator<(const Pair& other) const {
        return prob < other.prob;
    }

    int node;
    double prob;
};

class Edge {
public:
    Edge():from(0), to(0), prob(prob) {};
    Edge(int from, int to, double prob) {
        this->from = from;
        this->to = to;
        this->prob = prob;
    }

    int from, to;
    double prob;
};

class Graph {
public: 
    Graph(int size) {
        nodes = vector<vector<Edge>>(size, vector<Edge>());
    };

    void Set(int from, int to, double prob) {
        nodes[from].push_back(Edge(from, to, prob));
        nodes[to].push_back(Edge(to, from, prob));
    }

    double FindMaximumProb(int from, int to) {
        vector<bool> fixed(nodes.size(), false);
        vector<double> maxProb(nodes.size(), 0);
        priority_queue<Pair> pq;
        pq.push(Pair(from, 1));

        while (!pq.empty()) {
            Pair pair = pq.top(); pq.pop();

            // skip duplicate
            if (fixed[pair.node]) continue;
            fixed[pair.node] = true;

            for (Edge& edge : nodes[pair.node]) {
                if (fixed[edge.to]) continue;

                double curMax = maxProb[edge.to];
                double newMax = pair.prob * edge.prob;
                if (curMax >= newMax) continue;

                maxProb[edge.to] = newMax;
                pq.push(Pair(edge.to, newMax));
            }
        }

        return maxProb[to];
    }

private:
    vector<vector<Edge>> nodes;
};

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        Graph graph(n);

        for (int i=0; i<edges.size(); i++) {
            graph.Set(edges[i][0], edges[i][1], succProb[i]);
        }

        return graph.FindMaximumProb(start_node, end_node);
    }
};

int main() {
    Solution s;
    int n;
    vector<vector<int>> edges;
    vector<double> succProb;
    int startNode, endNode;

    // 0.25
    n = 3;
    edges = {{0,1},{1,2},{0,2}};
    succProb = {0.5,0.5,0.2};
    startNode = 0; endNode = 2;
    cout << s.maxProbability(n, edges, succProb, startNode, endNode) << endl;

    // 0.3
    n = 3;
    edges = {{0,1},{1,2},{0,2}};
    succProb = {0.5,0.5,0.3};
    startNode = 0; endNode = 2;
    cout << s.maxProbability(n, edges, succProb, startNode, endNode) << endl;

    // 0
    n = 3;
    edges = {{0, 1}};
    succProb = {0.5};
    startNode = 0; endNode = 2;
    cout << s.maxProbability(n, edges, succProb, startNode, endNode) << endl;
}