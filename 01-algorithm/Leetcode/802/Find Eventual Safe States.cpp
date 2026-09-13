#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<bool> visiting(graph.size(), false);
        vector<bool> completed(graph.size(), false);
        vector<bool> unsafe(graph.size(), false);

        for (int i=0; i<graph.size(); i++) {
            dfs(i, visiting, completed, unsafe, graph); 
        }

        vector<int> result;
        for (int i=0; i<unsafe.size(); i++) {
            if (!unsafe[i]) result.push_back(i);
        }

        return result;
    }

    bool dfs(int node, vector<bool>& visiting, vector<bool>& completed, vector<bool>& unsafe, vector<vector<int>>& graph) {
        if (completed[node]) return false;
        if (unsafe[node]) return true;
        if (visiting[node]) {
            visiting[node] = false;
            return true;
        }

        visiting[node] = true;
        for (int edge : graph[node]) {
            bool cycle = dfs(edge, visiting, completed, unsafe, graph);
            if (cycle) {
                unsafe[node] = true;
                return true;
            }
        }
        
        visiting[node] = false;
        completed[node] = true;
        return false;
    }
};
int main() {
    Solution s;
    vector<vector<int>> graph;

    // [2,4,5,6]
    graph = {{1,2},{2,3},{5},{0},{5},{},{}};
    for (int node : s.eventualSafeNodes(graph)) cout << node << " ";
    cout << endl;

    // [4]
    graph = {{1,2,3,4},{1,2},{3,4},{0,4},{}};
    for (int node : s.eventualSafeNodes(graph)) cout << node << " ";
    cout << endl;
}