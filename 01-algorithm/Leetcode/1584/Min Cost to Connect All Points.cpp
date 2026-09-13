#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class DisjointSet {
public:
    DisjointSet(int size) {
        parents = vector<int>(size, -1);
    }

    int Find(int i) {
        if (parents[i] < 0) return i;

        int result = Find(parents[i]);
        parents[i] = result;

        return result;
    }

    bool Union(int i, int j) {
        int iRoot = Find(i);
        int jRoot = Find(j);

        if (iRoot == jRoot) return false;

        int iSize = -1 * parents[iRoot];
        int jSize = -1 * parents[jRoot];
        
        if (iSize > jSize) {
            parents[jRoot] = iRoot;
            parents[iRoot] -= jSize;
        } else {
            parents[iRoot] = jRoot;
            parents[jRoot] -= iSize;
        }
        
        return true;
    }

private:
    vector<int> parents;
};

class Edge {
public:
    Edge(int from, int to, int val): from(from), to(to), val(val) {};

    bool operator<(const Edge& other) const {
        return val > other.val;
    }

    int from, to, val;
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        DisjointSet disjSet(points.size());
        priority_queue<Edge> pq;
        int mstSize = 0;
        int mstSum = 0;

        for (int i=0; i<points.size(); i++) {
            for (int j=i+1; j<points.size(); j++) {
                int diffX = abs(points[i][0] - points[j][0]);
                int diffY = abs(points[i][1] - points[j][1]);
                int distance = diffX + diffY;

                pq.push(Edge(i, j, distance));
            }
        }

        while (mstSize < points.size()-1 && !pq.empty()) {
            Edge edge = pq.top(); pq.pop();

            bool notCycle = disjSet.Union(edge.from, edge.to);
            if (notCycle) {
                mstSize++;
                mstSum += edge.val;
            }
        }

        return mstSum;
    }
};

int main() {
    Solution s;
    vector<vector<int>> points;

    // 20
    points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << s.minCostConnectPoints(points) << endl;

    // 18
    points = {{3,12},{-2,5},{-4,1}};
    cout << s.minCostConnectPoints(points) << endl;
}