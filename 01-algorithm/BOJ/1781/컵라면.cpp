#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Problem {
    int deadline;
    int reward;
};

class Descending {
public:
    bool operator()(const Problem &a, const Problem &b) {
        return a.reward > b.reward;
    }
};

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

        parents[aRoot] = bRoot;

        return false;
    }

private:
    vector<int> parents;
};

int main() {
    int n;
    cin >> n;

    vector<Problem> problems(n);
    for (int i=0; i<n; i++) {
        int deadline, reward;
        cin >> deadline >> reward;

        problems[i] = {deadline, reward};
    }

    sort(problems.begin(), problems.end(), Descending());

    int sum = 0;
    Disjoint distSet(n);
    for (Problem &p : problems) {
        int slot = distSet.find(p.deadline);
        if (slot == 0) continue;

        sum += p.reward;
        distSet.unite(slot, slot-1);
    }

    cout << sum << '\n';

    return 0;
}