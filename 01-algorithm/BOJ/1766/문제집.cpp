#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int first;
    int after;
};

class Ascending {
public:
    bool operator()(const int left, const int right) {
        return left > right;
    }
};

class Topsort {
public:
    Topsort(int size) {
        problems = vector<vector<Edge>>(size+1);
        indegrees = vector<int>(size+1, 0);
    }

    void set(int first, int after) {
        problems[first].push_back({first, after});
        indegrees[after] += 1;
    }

    vector<int> sort() {
        vector<int> result;
        priority_queue<int, vector<int>, Ascending> pq;

        for (int i=1; i<indegrees.size(); i++) {
            if (indegrees[i] == 0) {
                pq.push(i);
            }
        }

        while (!pq.empty()) {
            int cur = pq.top();
            pq.pop();

            result.push_back(cur);

            for (Edge &edge : problems[cur]) {
                indegrees[edge.after] -= 1;
                if (indegrees[edge.after] == 0) pq.push(edge.after);
            }
        }

        return result;
    }

private:
    vector<vector<Edge>> problems;
    vector<int> indegrees;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nums, deps;
    cin >> nums >> deps;

    Topsort topsort(nums);
    for (int i=0; i<deps; i++) {
        int first, after;
        cin >> first >> after;

        topsort.set(first, after);
    }

    for (auto prob : topsort.sort()) {
        cout << prob << " ";
    }
    cout << '\n';
}