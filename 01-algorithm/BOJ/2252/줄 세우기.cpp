#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Person {
    int indegree = 0;
    vector<int> lessThan;
};

class Topsort {
public:
    Topsort(int size) {
        people = vector<Person>(size+1);
    }

    void set(int less, int tall) {
        people[less].lessThan.push_back(tall);
        people[tall].indegree += 1;
    }

    vector<int> sort() {
        vector<int> order;
        queue<int> q;

        for (int i=1; i<people.size(); i++) {
            if (people[i].indegree == 0) q.push(i);
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            order.push_back(cur);

            for (int tall : people[cur].lessThan) {
                people[tall].indegree -= 1;
                if (people[tall].indegree == 0) q.push(tall);
            }
        }

        return order;
    }

private:
    vector<Person> people;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int people, deps;
    cin >> people >> deps;

    Topsort topsort(people);
    for (int i=0; i<deps; i++) {
        int less, tall;
        cin >> less >> tall;

        topsort.set(less, tall);
    }

    auto order = topsort.sort();
    for (int person : order) cout << person << " ";

    cout << '\n';
}