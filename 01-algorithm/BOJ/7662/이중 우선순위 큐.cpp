#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <string>

using namespace std;

class MaxCompare {
public:
    // true일 때 swap이 일어난다
    bool operator()(int a, int b) {
        return a < b;
    }
};

class MinCompare {
public:
    bool operator()(int a, int b) {
        return a > b;
    }
};

class DualQueue {
public:
    void Do(string operation, int operand) {
        if (operation == "I") {
            put(operand);
        }
        if (operation == "D") {
            if (operand == -1) {
                popMin();
            }
            if (operand == 1) {
                popMax();
            }
        }
    }

    int getMax() { 
        int num = maxHeap.top();
        while (!has(num)) {
            maxHeap.pop();
            num = maxHeap.top();
        } 

        return num;
    }

    int getMin() { 
        int num = minHeap.top();
        while (!has(num)) {
            minHeap.pop();
            num = minHeap.top();
        } 

        return num;
    }

    bool isEmpty() {
        return size == 0;
    }

    void popMin() {
        if (minHeap.empty()) return;

        int num = minHeap.top();
        minHeap.pop();
        while (!has(num)) {
            if (minHeap.empty()) return;

            num = minHeap.top();
            minHeap.pop();
        }

        exists[num] -= 1;
        size--;
    }

    void popMax() {
        if (maxHeap.empty()) return;

        int num = maxHeap.top();
        maxHeap.pop();
        while (!has(num)) {
            if (maxHeap.empty()) return;

            num = maxHeap.top();
            maxHeap.pop();
        }

        exists[num] -= 1;
        size--;
    }

    void put(int num) {
        minHeap.push(num);
        maxHeap.push(num);

        if (!has(num)) exists[num] = 1;
        else exists[num] += 1;

        size++;
    }

    bool has(int num) {
        if (exists.find(num) == exists.end()) {
            return false;
        }

        return exists[num] > 0;
    }

    int size=0;
private:
    priority_queue<int, vector<int>, MinCompare> minHeap;
    priority_queue<int, vector<int>, MaxCompare> maxHeap;
    map<int, int> exists;
};

int main() {
    int cases;
    cin >> cases;

    for (int c=0; c<cases; c++) {
        int operations;
        cin >> operations;

        DualQueue dq;

        for (int i=0; i<operations; i++) {
            string operation;
            int operand;

            cin >> operation >> operand;
            dq.Do(operation, operand);
        }

        if (dq.isEmpty()) cout << "EMPTY" << '\n';
        else cout << dq.getMax() << " " << dq.getMin() << '\n';
    }
}


