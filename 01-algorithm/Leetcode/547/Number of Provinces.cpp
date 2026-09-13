#include <vector>
#include <iostream>

using namespace std;

class DisjointSet {
public:
    DisjointSet(int size): rootCount(size) {
        parents = vector<int>(size, -1);
    };

    int Find(int val) {
        if (parents[val] < 0) return val;

        int root = Find(parents[val]);
        parents[val] = root;

        return root;
    }

    bool Union(int a, int b) {
        int aRoot = Find(a);
        int bRoot = Find(b);

        if (aRoot == bRoot) return false;

        int aSize = -1 * parents[aRoot];
        int bSize = -1 * parents[bRoot];

        if (aSize < bSize) {
            parents[aRoot] = bRoot;
            parents[bRoot] -= aSize;
        } else {
            parents[bRoot] = aRoot;
            parents[aRoot] -= bSize;
        }

        rootCount--;
        return true;
    }

    int Size() { return rootCount; }

private:
    int rootCount = 0;
    vector<int> parents;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int numCities = isConnected.size();
        DisjointSet disjointSet(numCities);

        for (int i=0; i<numCities; i++) {
            for (int j=i+1;j<numCities; j++) {
                if (isConnected[i][j]) disjointSet.Union(i, j);
            }
        }

        return disjointSet.Size();
    }
};

int main() {
    Solution s;
    vector<vector<int>> isConnected;

    // 2
    isConnected = {{1,1,0},{1,1,0},{0,0,1}};
    cout << s.findCircleNum(isConnected) << endl;

    // 3
    isConnected = {{1,0,0},{0,1,0},{0,0,1}};
    cout << s.findCircleNum(isConnected) << endl;
}