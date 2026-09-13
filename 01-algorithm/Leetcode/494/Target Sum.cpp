#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        map<vector<int>, int> memo;

        backtrack(0, 0, target, nums, memo);
    
        return memo[{0, 0}];
    }

    int backtrack(int depth, int sum, int target, vector<int>& nums, map<vector<int>, int>& memo) {
        if (depth == nums.size()) {
            if (sum == target) return 1;

            return 0;
        }

        vector<int> pair = {depth, sum};
        if (memo.find(pair) != memo.end()) {
            return memo[pair];
        }

        int found = backtrack(depth+1, sum+nums[depth], target, nums, memo) + \
                backtrack(depth+1, sum-nums[depth], target, nums, memo);
        memo[pair] = found;

        return found;
    }
};

int main() {
    Solution s;
    vector<int> nums;
    int target;

    // 5
    nums = {1,1,1,1,1};
    target = 3;
    cout << s.findTargetSumWays(nums, target) << endl;

    // 1
    nums = {1};
    target = 1;
    cout << s.findTargetSumWays(nums, target) << endl;

    // 44
    nums = {11,19,14,50,47,35,18,32,8,2,31,45,6,25,49,23,25,33,24,33};
    target = 44;
    cout << s.findTargetSumWays(nums, target) << endl;
}