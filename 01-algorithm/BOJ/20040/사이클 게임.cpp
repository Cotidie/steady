#include <iostream>
#include <vector>

using namespace std;

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

int main() {
    int dots, turns;
    cin >> dots >> turns;

    Disjoint distSet(dots);
    int cycleTurn = 0;
    for (int i=1; i<=turns; i++) {
        int a, b;
        cin >> a >> b;

        bool isCycle = distSet.unite(a, b);
        if (isCycle) {
            cycleTurn = i;
            break;
        }
    }

    cout << cycleTurn << '\n';
}