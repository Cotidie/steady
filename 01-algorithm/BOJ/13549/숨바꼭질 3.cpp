#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct Pair {
    int num;
    int sec;
};

bool tryUpdate(int num, int newDist, map<int, int>& distances) {
    if (distances.find(num) == distances.end()) {
        distances[num] = newDist;
        return true;
    }

    if (distances[num] > newDist) {
        distances[num] = newDist;
        return true;
    }

     return false;
}

int main() {
    int source, target;
    cin >> source >> target;

    map<int, int> distances;
    deque<Pair> dq;
    dq.push_front(Pair{source, 0});
    distances[source] = 0;

    while (!dq.empty()) {
        Pair cur = dq.front();
        dq.pop_front();

        if (cur.num == target) {
            cout << cur.sec << '\n';
            return 0;
        }

        bool updated = tryUpdate(cur.num-1, cur.sec+1, distances);
        if (updated) dq.push_back(Pair{cur.num-1, cur.sec+1});
        if (cur.num > target) continue;

        updated = tryUpdate(cur.num+1, cur.sec+1, distances);
        if (updated) dq.push_back(Pair{cur.num+1, cur.sec+1});

        updated = tryUpdate(cur.num * 2, cur.sec, distances);
        if (updated) dq.push_front(Pair{cur.num*2, cur.sec});
    }

    return 0;
}