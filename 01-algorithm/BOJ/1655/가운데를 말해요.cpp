#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INTMIN = -10001;
const int INTMAX = 10001;

class Ascending {
public:
    bool operator()(const int a, const int b) {
        return a > b;
    }
};

class Descending {
public:
    bool operator()(const int a, const int b) {
        return a < b;
    }
};

class Medium {
public:
    Medium() {
        minHeap.push(INTMAX);
        maxHeap.push(INTMIN);
    };

    void put(int n) {
        if (n > maxHeap.top()) {
            minHeap.push(n);
        } else {
            maxHeap.push(n);
        }

        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        if (maxHeap.size() > minHeap.size()+1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
    }

    int getMed() {return maxHeap.top();}
private:
    priority_queue<int, vector<int>, Ascending> minHeap;
    priority_queue<int, vector<int>, Descending> maxHeap;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int nums;
    cin >> nums;

    Medium medium;
    for (int i=0; i<nums; i++) {
        int val;
        cin >>  val;

        medium.put(val);
        cout << medium.getMed() << '\n';
    }

    return 0;
}