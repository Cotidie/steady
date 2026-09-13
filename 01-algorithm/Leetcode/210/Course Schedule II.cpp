#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

class Graph {
public:
    Graph(int size) {
        nodes = vector<vector<Edge>>(size);
    }

    vector<Edge>& getEdges(int node) {
        return nodes[node];
    } 

    void connect(int from, int to) {
        nodes[from].push_back(Edge{from, to});
    }

    vector<int> getCoursePath() {
        visiting = vector<bool>(nodes.size(), false);
        completed = vector<bool>(nodes.size(), false);
        topology = vector<int>(nodes.size());
        idxTopology = nodes.size()-1;

        for (int node=0; node<nodes.size(); node++) {
            if (completed[node]) continue;
            bool success = dfs(node);
            if (!success) return {};
        }

        return topology;
    }

private:
    bool dfs(int node) {
        if (visiting[node]) return false;

        visiting[node] = true;
        for (Edge& edge : getEdges(node)) {
            if (completed[edge.to]) continue;

            bool success = dfs(edge.to);
            if (!success) return false;
        }
        visiting[node] = false;
        completed[node] = true;
        topology[idxTopology] = node;
        idxTopology--;

        return true;
    }

    int idxTopology;
    vector<int> topology;
    vector<bool> visiting;
    vector<bool> completed;
    vector<vector<Edge>> nodes;
};

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        Graph graph(numCourses);
        
        for (auto prerequisite : prerequisites) {
            graph.connect(prerequisite[1], prerequisite[0]);
        }

        return graph.getCoursePath();
    }
};

int main() {
    Solution s;
    vector<vector<int>> prerequisites;
    int numCourses;
    
    // // 0, 1
    // prerequisites = {{1, 0}};
    // numCourses = 2;
    // for (auto order : s.findOrder(numCourses, prerequisites)) cout << order << " ";
    // cout << endl;

    // 0, 2, 1, 3
    prerequisites = {{1,0},{2,0},{3,1},{3,2}};
    numCourses = 4;
    for (auto order : s.findOrder(numCourses, prerequisites)) cout << order << " ";
    cout << endl;
}