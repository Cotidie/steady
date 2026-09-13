#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Node {
    int indegree = 0;
    vector<int> next; 
};

class Topsort {
public:
    Topsort(int size) {
        nodes = vector<Node>(size+1);
    }

    void set(int before, int next) {
        if (before == next) return;
        nodes[before].next.push_back(next);
        nodes[next].indegree += 1;
    }

    vector<int> sort() {
        vector<int> result;
        queue<int> q;
        
        for (int i=1; i<nodes.size(); i++) {
            if (nodes[i].indegree == 0) q.push(i);
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            result.push_back(cur);

            for (int next : nodes[cur].next) {
                nodes[next].indegree -= 1;
                if (nodes[next].indegree == 0) q.push(next);
            }
        }

        return result;
    }
private:
    vector<Node> nodes;
};

int main() {
    int singers, deps; 
    cin >> singers >> deps;

    Topsort topsort(singers);
    for (int i=0; i<deps; i++) {
        int nums;
        cin >> nums;

        vector<int> queue(nums);
        for (int j=0; j<nums; j++) {
            int val;
            cin >> val;

            queue[j] = val;
        }
        
        for (int j=0; j<nums-1; j++) {
            topsort.set(queue[j], queue[j+1]);
        }
    }

    vector<int> sorted = topsort.sort();
    if (sorted.size() < singers) {
        cout << 0 << '\n';
        return 0;
    }

    for (int singer : sorted) {
        cout << singer << '\n';
    }
}