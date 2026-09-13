#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Node {
public:
    Node() {};
    Node(int val): val(val) {};

    bool isRoot() { return next == nullptr; }

    Node* next = nullptr;
    int val = 0;
    int size = 1;
};

class DisjointSet {
public:
    DisjointSet(vector<int>& nums) {
        for (int num : nums) {
            sets[num] = Node(num);
        }
    }

    Node& Find(int val) {
        Node& node = sets[val];

        if (node.isRoot()) return node;

        Node& root = Find(node.next->val);
        node.next = &root;

        return root;
    }

    bool Union(int a, int b) {
        Node& aRoot = Find(a);
        Node& bRoot = Find(b);

        if (aRoot.val == bRoot.val) return false;

        if (aRoot.size > bRoot.size) {
            bRoot.next = &aRoot;
            aRoot.size += bRoot.size;
        } else {
            aRoot.next = &bRoot;
            bRoot.size += aRoot.size;
        }

        return true;
    }

private:
    map<int, Node> sets;
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) return 0;

        map<int, bool> exists;
        DisjointSet disjointSet(nums);

        for (int num : nums) exists[num] = true;

        int largestSize = 1;
        for (int num : nums) {
            if (exists.find(num-1) == exists.end()) continue;

            disjointSet.Union(num, num-1);
            largestSize = max(largestSize, disjointSet.Find(num).size);
        }

        return largestSize;
    }
};

int main() {
    Solution s;
    vector<int> nums;

    // 4
    nums = {100,4,200,1,3,2};
    cout << s.longestConsecutive(nums) << endl;

    // 9
    nums = {0,3,7,2,5,8,4,6,0,1};
    cout << s.longestConsecutive(nums) << endl;
}