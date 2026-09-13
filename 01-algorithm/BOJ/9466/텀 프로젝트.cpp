#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int from, to;
};

class Disjoint {
public:
    Disjoint() {};
    Disjoint(int size) {
        parents = vector<int>(size, -1);
    }

    int find(int n) {
        if (parents[n] < 0) return n;

        int root = find(parents[n]);
        parents[n] = root;

        return root;
    }

    bool unite(int a, int b) {
        int aRoot = find(a);
        int bRoot = find(b);

        if (aRoot == bRoot) return true;

        int aSize = parents[aRoot] * -1;
        int bSize = parents[bRoot] * -1;

        if (aSize > bSize) {
            parents[bRoot] = aRoot;
            parents[aRoot] -= bSize;
        } else {
            parents[aRoot] = bRoot;
            parents[bRoot] -= aSize;
        }

        return false;
    }

private:
    vector<int> parents;
};

class Graph {
public:
    Graph(int size): students(size) {
        edges = vector<int>(size+1);
        distSet = Disjoint(size+1);
    }

    void set(int a, int b) {
        edges[a] = b;
    }

    int match() {
        int matched = 0;
        for (int i=1; i<=students; i++) {
            bool isCycle = distSet.unite(i, edges[i]);
            if (isCycle) matched += getCycleLength(i);
        }

        return students - matched;
    }

private:
    int getCycleLength(int start) {
        int cnt = 1;

        int cur = edges[start];
        while (cur != start) {
            cnt++;
            cur = edges[cur];
        }

        return cnt;
    }

    Disjoint distSet;
    vector<int> edges;
    int students;
};

int main() {
    int C;
    cin >> C;

    for (int c=0; c<C; c++) {
        int students;
        cin >> students;

        Graph graph(students);
        for (int i=0; i<students; i++) {
            int select;
            cin >> select;

            graph.set(i+1, select);
        }

        cout << graph.match() << '\n';
    }
}