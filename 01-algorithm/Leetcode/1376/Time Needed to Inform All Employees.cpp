#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    Node(): value(-1) {};
    Node(int value):value(value) {};

    void Attach(Node* node) {
        childen.push_back(node);
    }

    int Size() {
        return childen.size();
    }

    int value;
    vector<Node*> childen;
};

class Company {
public:
    Company(int size) {
        employees = vector<Node>(size);

        for (int i=0; i<size; i++) {
            employees[i] = Node(i);
        }
    }

    void SetManagers(vector<int>& managers) {
        for (int i=0; i<managers.size(); i++) {
            if (managers[i] == -1) continue;

            Node& manager = employees[managers[i]];
            Node& sub = employees[i];

            manager.Attach(&sub);
        }
    }

    int GetInformTime(int head, vector<int>& times) {
        return traverse(&employees[head], times);
    }

    int traverse(Node* employee, vector<int>& times) {
        if (employee->Size() == 0) return 0;

        int childInform = -1;
        for (Node* sub : employee->childen) {
            childInform = max(childInform, traverse(sub, times));
        }

        int myInform = times[employee->value];

        return myInform + childInform;
    }

private:
    vector<Node> employees; 
};

class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        Company company(n);

        company.SetManagers(manager);

        return company.GetInformTime(headID, informTime);
    }
};

class TestCases {
public:
    TestCases() {
        s = Solution();
    };
    
    void Test1() {
        int headID = 0;
        vector<int> manager = {-1};
        vector<int> informTime = {0};

        cout << s.numOfMinutes(manager.size(), headID, manager, informTime) << endl;
    }

    void Test2() {
        int headID = 2;
        vector<int> manager = {2,2,-1,2,2,2};
        vector<int> informTime = {0,0,1,0,0,0};

        cout << s.numOfMinutes(manager.size(), headID, manager, informTime) << endl; 
    }

    void Test3() {
        int headID = 0;
        vector<int> manager = {-1,0,0,1,1,2,2,3,3,4,4,5,5,6,6};
        vector<int> informTime = {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};

        cout << s.numOfMinutes(manager.size(), headID, manager, informTime) << endl; 
    }

private:
    Solution s;
};

int main() {
    TestCases cases;

    cases.Test1();
    cases.Test2();
    cases.Test3();
}