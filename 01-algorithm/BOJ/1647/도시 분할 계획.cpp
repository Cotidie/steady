#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int a, b;
    int cost;
};

class Ascending {
public:
    bool operator()(const Edge &left, const Edge &right) {
        return left.cost > right.cost;
    }
};

class Disjoint {
public:
    Disjoint(int size) {
        set = vector<int>(size, -1);
    }

    int find(int n) {
        if (set[n] < 0) return n;

        int root = find(set[n]);
        set[n] = root;

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

class Village {
public:
    Village(int size): houses(size) {}

    void set(int a, int b, int cost) {
        roads.push_back({a, b, cost});
    }

    vector<Edge> build() {
        Disjoint distSet(houses+1);
        priority_queue<Edge, vector<Edge>, Ascending> pq(roads.begin(), roads.end());

        vector<Edge> mst;
        while (!pq.empty()) {
            Edge road = pq.top();
            pq.pop();

            bool isCycle = distSet.unite(road.a, road.b);
            if (isCycle) continue;

            mst.push_back(road);
            if (mst.size() == houses-1) break;
        }

        return mst;
    }
private:
    int houses;
    vector<Edge> roads;
};

int main() {
    int houses, roads;
    cin >> houses >> roads;

    Village village(houses);
    for (int i=0; i<roads; i++) {
        int a, b, cost;
        cin >> a >> b >> cost;

        village.set(a, b, cost);
    }

    auto mst = village.build();

    int sum = 0;
    int max = -1;
    for (Edge &road : mst) {
        sum += road.cost;
        if (max < road.cost) max = road.cost;
    }

    cout << sum - max << '\n';
}