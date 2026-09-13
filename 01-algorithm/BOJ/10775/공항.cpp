#include <iostream>
#include <vector>

using namespace std;

class Disjoint {
public:
    Disjoint(int size) {
        parents = vector<int>(size+1, -1);
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

        if (aRoot < bRoot) parents[bRoot] = aRoot;
        else parents[aRoot] = bRoot;

        return false;
    }

private:
    vector<int> parents;
};


int main() {
    int gates, planes;
    cin >> gates >> planes;

    Disjoint distSet(gates);

    int cnt = 0;
    for (int p=0; p<planes; p++) {
        int maxGate;
        cin >> maxGate;

        int emptyGate = distSet.find(maxGate);
        if (emptyGate == 0) break;

        cnt++;
        distSet.unite(emptyGate, emptyGate-1); 
    }

    cout << cnt << '\n';
}