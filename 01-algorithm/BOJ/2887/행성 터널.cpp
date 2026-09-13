#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Planet {
    int id;
    long pos;
};

struct Edge {
    long cost;
    int pA, pB;
};

class Ascending {
public:
    bool operator()(const Planet& a, const Planet &b) {
        return a.pos < b.pos;
    }
};

class AscendingEdge {
public:
    bool operator()(const Edge &a, const Edge &b) {
        return a.cost > b.cost;
    }
};

class Disjoint {
public:
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

class Constructor{
public:
    Constructor(int size) {planets = vector<vector<Planet>>(3, vector<Planet>(size));};

    void set(int id, int x, int y, int z) {
        planets[0][id]={id, x};
        planets[1][id]={id, y};
        planets[2][id]={id, z};
    }

    int mst() {
        sort(planets[0].begin(), planets[0].end(), Ascending());
        sort(planets[1].begin(), planets[1].end(), Ascending());
        sort(planets[2].begin(), planets[2].end(), Ascending());
        vector<bool> selected = vector<bool>(planets.size(), false);
        Disjoint distSet(planets[0].size());
        priority_queue<Edge, vector<Edge>, AscendingEdge> pq;

        for (int i=0; i<3; i++) {
            for (int p=0; p<planets[i].size()-1; p++) {
                long cost = abs(planets[i][p].pos-planets[i][p+1].pos);
                pq.push({cost, planets[i][p].id, planets[i][p+1].id});
            }
        }

        long cost = 0;
        long cnt = 0;
        while (cnt < planets[0].size()-1 && !pq.empty()) {
            Edge cur = pq.top();
            pq.pop();

            bool isCycle = distSet.unite(cur.pA, cur.pB);
            if (isCycle) continue;

            cost += cur.cost;
            cnt++;
        }

        return cost;
    }

private:
    int getNext(int idx, vector<Planet> &arr, vector<bool>& selected) {
        while (selected[arr[idx].id] == true) {
            idx++;
        }

        return idx;
    }

    int getMin(long a, long b, long c) {
        if (a < b) {
            if (a < c) return 0;
        } else {
            if (b < c) return 1;
        }

        return 2;
    }

    vector<vector<Planet>> planets;
};

int main() {
    int n;
    cin >> n;

    Constructor constr(n);
    for (int i=0; i<n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        constr.set(i, x, y, z);
    }

    cout << constr.mst() << '\n';
}