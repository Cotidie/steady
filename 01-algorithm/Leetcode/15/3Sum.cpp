// Q. How would you remove duplicate?

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> resultSet;
        
        sort(nums.begin(), nums.end());
        

        for (int i=0; i<nums.size()-2; i++) {
            int twoSumTarget = -1 * nums[i];
            set<vector<int>> twoNums = twoSum(nums, twoSumTarget, i+1, nums.size()-1);

            for (auto twoNum : twoNums) {
                int first = twoNum[0];
                int second = twoNum[1];
                resultSet.insert({nums[i], first, second});
            }
        }

        vector<vector<int>> result;
        for (auto set : resultSet) result.push_back(set);

        return result;
    }

    set<vector<int>> twoSum(vector<int>& nums, int target, int start, int end) {
        set<vector<int>> result;
        
        while (start < end) {
            int sum = nums[start] + nums[end];

            if (sum == target) {
                result.insert({nums[start], nums[end]});
                start++;
            };
            if (sum < target) start++;
            if (sum > target) end--;
        }

        return result;
    }
};

int main() {
    Solution s;
    vector<int> nums;

    // [[-1,-1,2],[-1,0,1]]
    nums = {-1,0,1,2,-1,-4};
    for (vector<int> indices : s.threeSum(nums)) {
        cout << "[";
        for (int index : indices) cout << index << ",";
        cout << "] ";
    }
    cout << endl;

    // []
    nums = {0,1,1};
    for (vector<int> indices : s.threeSum(nums)) {
        cout << "[";
        for (int index : indices) cout << index << ",";
        cout << "] ";
    }
    cout << endl;

    // [[-2,0,2],[-2,1,1]]
    nums = {-2,0,1,1,2};
    for (vector<int> indices : s.threeSum(nums)) {
        cout << "[";
        for (int index : indices) cout << index << ",";
        cout << "] ";
    }
    cout << endl;
}