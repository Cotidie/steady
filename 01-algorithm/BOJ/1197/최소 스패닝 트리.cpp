#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to;
    int cost;
};

class Ascending {
public:
    // true일 때 안정상태이다.
    bool operator()(const Edge &left, const Edge &right) {
        return left.cost > right.cost;
    }
};

class Disjoint {
public:
    Disjoint() {};

    Disjoint(int size) {
        set = vector<int>(size, -1);
    }

    int find(int num) {
        // 실수: num < 0으로 비교하였다.
        if (set[num] < 0) return num;

        int root = find(set[num]);
        set[num] = root;

        return root;
    }

    bool unite(int a, int b) {
        int aRoot = find(a);
        int bRoot = find(b);

        if (aRoot == bRoot) return true;

        int aSize = set[aRoot] * -1;
        int bSize = set[bRoot] * -1;

        if (aSize > bSize) {
            set[bRoot] = aRoot;
            set[aRoot] -= bSize;
        } else {
            set[aRoot] = bRoot;
            set[bRoot] -= aSize;
        }

        return false;
    }

private:
    vector<int> set;
};

class MST {
public: 
    MST(int size) {
        this->size = size;
        distSet = Disjoint(size+1);
    }

    void add(int from, int to, int cost) {
        edges.push_back({from, to, cost});
    }

    vector<Edge> build() {
        vector<Edge> result;
        // 실수: pq로 정렬해야 한다.
        priority_queue<Edge, vector<Edge>, Ascending> pq(edges.begin(), edges.end());

        while (!pq.empty()) {
            Edge edge = pq.top();
            pq.pop();

            bool isCycle = distSet.unite(edge.from, edge.to);

            if (isCycle) continue;

            result.push_back(edge);
            if (result.size() == (size-1)) break;
        }

        return result;
    }

private:
    int size;
    vector<Edge> edges;
    Disjoint distSet;
};

int main() {
    int V, E;
    cin >> V >> E;

    MST mst(V);
    for (int i=0; i<E; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;

        mst.add(from, to, cost);
    }

    auto edges = mst.build();

    int sum = 0;
    for (Edge &edge : edges) {
        sum += edge.cost;
    }

    cout << sum << '\n';
}