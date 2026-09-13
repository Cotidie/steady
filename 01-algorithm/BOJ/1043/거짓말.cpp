#include <iostream>
#include <vector>

using namespace std;

class Disjoint {
public:
    Disjoint(int people) {
        set = vector<int>(people+1, -1);
        truth = vector<bool>(people+1, false);
    }

    void setTruth(int person) {
        truth[person] = true;
    }

    bool knowTruth(int person) {
        int root = find(person);

        return truth[root];
    }

    int find(int person) {
        if (set[person] < 0) return person;

        int root = find(set[person]);
        set[person] = root;

        return root; 
    }

    void unite(int a, int b) {
        int aRoot = find(a);
        int bRoot = find(b);

        if (aRoot == bRoot) return;

        bool aTruth = truth[aRoot];
        bool bTruth = truth[bRoot];

        if (aTruth) {
            set[bRoot] = aRoot;
        } else {
            set[aRoot] = bRoot;
        }
    }

private:
    vector<int> set;
    vector<bool> truth;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int numPeople, numParty;
    cin >> numPeople >> numParty;

    int truth;
    cin >> truth;

    Disjoint disjoint(numPeople);
    for (int i=0; i<truth; i++) {
        int person;
        cin >> person;

        disjoint.setTruth(person);
    }

    vector<vector<int>> parties(numParty, vector<int>());
    for (int i=0; i<numParty; i++) {
        int participants, represent;
        cin >> participants >> represent;

        parties[i].push_back(represent);
        for (int j=1; j<participants; j++) {
            int person;
            cin >> person;

            parties[i].push_back(person);
            disjoint.unite(represent, person);
        }
    }

    int cnt = 0;
    for (auto party : parties) {
        bool truth = false;
        
        for (int person : party) {
            if (disjoint.knowTruth(person)) {
                truth = true;
                break;
            }
        }

        if (!truth) cnt++;
    }

    cout << cnt << '\n';
}