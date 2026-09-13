#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Edge {
    int to = -1;
    int weight = 0;
};

class Tree {
public:
    Tree() {
        tree = vector<vector<Edge>>(100001, vector<Edge>());
    };

    void set(int node, int to, int weight) {
        tree[node].push_back(Edge{to, weight});
    }

    int getDiameter() {
        dfs(1);
        dfs(dianode);

        return diameter;
    }

private:
    void dfs(int node) {
        visited = vector<bool>(100001, false);
        stack<Edge> st;

        st.push(Edge{node, 0});
        visited[node] = true;

        while (!st.empty()) {
            Edge cur = st.top();
            st.pop();

            if (diameter < cur.weight) {
                diameter = cur.weight;
                dianode = cur.to;
            }

            for (auto edge: tree[cur.to]) {
                if (visited[edge.to]) continue;

                st.push(Edge{edge.to, cur.weight+edge.weight});
                visited[edge.to] = true;
            }
        }
    }

    vector<vector<Edge>> tree;
    vector<bool> visited;
    int diameter = 0;
    int dianode = 0;
};

int main() {
    int n;
    cin >> n;

    Tree tree;

    for (int i=0; i<n; i++) {
        int node; 
        cin >> node;

        int val; bool isWeight = false;
        int to, weight;
        while (cin >> val, val != -1) {
            if (isWeight) {
                weight = val;
                tree.set(node, to, weight);
            } else {
                to = val;
            }

            isWeight = !isWeight;
        }
    }
    

    cout << tree.getDiameter() << '\n';
}