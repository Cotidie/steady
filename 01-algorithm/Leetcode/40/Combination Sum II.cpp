#include <vector>
#include <iostream>
#include <map>

using namespace std;

vector<vector<int>> result;
map<int, int> counts;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        counts = map<int, int>();
        result = vector<vector<int>>();

        for (int candidate : candidates) {
            if (counts.find(candidate) == counts.end()) {
                counts[candidate] = 0;
            }

            counts[candidate] += 1;
        }

        vector<int> comb;
        for (auto count: counts) {
            combination(count.first, 0, target, comb);
        }

        return result;
    }

    void combination(
        int num, int sum, int target, 
        vector<int>& comb
    ) {
        if (sum + num > target) return;
        if (sum + num == target) {
            comb.push_back(num);
            result.push_back(comb);
            comb.pop_back();
            return;
        }

        comb.push_back(num);
        sum += num;
        counts[num] -= 1;
        for (auto count: counts) {
            if (count.second == 0) continue;
            if (count.first < num) continue;

            combination(count.first, sum, target, comb);
        }

        comb.pop_back();
        counts[num] += 1;
    }
};

int main() {
    Solution s;
    vector<int> candidates;
    int target;

    // [
    // [1,1,6],
    // [1,2,5],
    // [1,7],
    // [2,6]
    // ]
    candidates = {10,1,2,7,6,1,5};
    target = 8;
    for (auto candidate : s.combinationSum2(candidates, target)) {
        for (int num: candidate) cout << num << " ";
        cout << endl;
    }
    cout << endl;

    // [
    // [1,2,2],
    // [5]
    // ]
    candidates = {2,5,2,1,2};
    target = 5;
    for (auto candidate : s.combinationSum2(candidates, target)) {
        for (int num: candidate) cout << num << " ";
        cout << endl;
    }
    cout << endl;
}