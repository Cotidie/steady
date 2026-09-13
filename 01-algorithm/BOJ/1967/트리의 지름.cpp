#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int to = -1;
    int weight = 0;
};

class Tree {
public:
    Tree() {
        tree = vector<vector<Edge>>(10001, vector<Edge>());
    };

    void set(int node, int to, int weight) {
        tree[node].push_back(Edge{to, weight});
    }

    int getDiameter() {
        recurse(1, 0);
        return diameter;
    }

private:
    int recurse(int node, int weight) {
        if (node == -1) return 0;

        int maxFirst = 0;
        int maxSecond = 0;
        for (int i=0; i<tree[node].size(); i++) {
            int val = recurse(tree[node][i].to, tree[node][i].weight);
            if (maxFirst < val) {
                maxSecond = maxFirst;
                maxFirst = val;
            } else if (maxSecond < val) {
                maxSecond = val;
            }
        }

        if (diameter < maxFirst+maxSecond) diameter = maxFirst+maxSecond;

        return maxFirst+weight;
    }

    vector<vector<Edge>> tree;
    int diameter = 0;
};

int main() {
    int n;
    cin >> n;

    Tree tree;
    for (int i=1; i<n; i++) {
        int node, to, weight;
        cin >> node >> to >> weight;

        tree.set(node, to, weight);
    }

    cout << tree.getDiameter() << '\n';
}