#include <vector>
#include <iostream>
#include <set>

using namespace std;

class Permutations {
public:
    Permutations(vector<int>& nums): nums(nums) {
        this->permutation = vector<int>(nums.size());
        this->used = vector<bool>(nums.size(), false);
    }

    vector<vector<int>> Get() {
        for (int i=0; i<nums.size(); i++) {
            makePermutation(i, 0);
        }

        vector<vector<int>> result;
        for (auto permutation : permutations) {
            result.push_back(permutation);
        }

        return result;
    }

private:
    void makePermutation(int idx, int depth) {
        if (depth == nums.size()) {
            permutations.insert(permutation);
            return;
        }
        if (used[idx]) return;

        permutation[depth] = nums[idx];
        used[idx] = true;
        for (int i=0; i<nums.size(); i++) {
            makePermutation(i, depth+1);
        }
        used[idx] = false;
    }

    vector<int>& nums;
    vector<bool> used;
    vector<int> permutation;
    set<vector<int>> permutations;
};

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        Permutations permutes(nums);

        return permutes.Get();
    }
};

int main() {
    Solution s;
    vector<int> nums;

    // [[1,1,2],
    //  [1,2,1],
    //  [2,1,1]]
    nums = {1,1,2};
    for (auto permutation : s.permuteUnique(nums)) {
        for (int num : permutation) cout << num << " ";
        cout << endl;
    }
    cout << endl;

    // [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    nums = {1,2,3};
    for (auto permutation : s.permuteUnique(nums)) {
        for (int num : permutation) cout << num << " ";
        cout << endl;
    }
    cout << endl;
}