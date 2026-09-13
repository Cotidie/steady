#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int to;
    int cost;
};

class Topsort {
public:
    Topsort(int nodes, int deps) {
        buildings = vector<vector<int>>(nodes+1, vector<int>(2, 0));
        this->deps = vector<vector<int>>(nodes+1);
        costs = vector<int>(nodes+1, -1);
    }

    void setCost(int building, int cost) {
        buildings[building][0] = cost;
    }

    void setDep(int from, int to) {
        deps[from].push_back(to);
        buildings[to][1] += 1;
    }

    void fill() {
        queue<int> q;

        for (int i=1; i<buildings.size(); i++) {
            if (buildings[i][1] == 0) q.push(i);
            costs[i] = 0;
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int next : deps[cur]) {
                buildings[next][1] -= 1;
                if (buildings[next][1] == 0) q.push(next);

                costs[next] = max(costs[next], costs[cur] + buildings[cur][0]);
            }
        }
    }

    int getCost(int building) {
        return costs[building] + buildings[building][0];
    }
private:
    // [][0] costs, [][1] indegrees
    vector<vector<int>> buildings;
    vector<vector<int>> deps;
    vector<int> costs;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int cases;
    cin >> cases;

    for (int c=0; c<cases; c++) {
        int buildings, rules;
        cin >> buildings >> rules;

        Topsort topsort(buildings, rules);

        for (int i=0; i<buildings; i++) {
            int cost;
            cin >> cost;

            topsort.setCost(i+1, cost);
        }

        for (int r=0; r<rules; r++) {
            int from, to;
            cin >> from >> to;

            topsort.setDep(from, to);
        }

        topsort.fill();
        
        int target;
        cin >> target;

        cout << topsort.getCost(target) << '\n';
    }
}