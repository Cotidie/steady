#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int maxSum = findMaxSum(nums);
        int minSum = findMinSum(nums);
        int total = 0;
        for (auto num : nums) total += num;

        // edge case: there are only negatives
        if (maxSum < 0) return maxSum;

        minSum = total - minSum;

        return (maxSum > minSum) ? maxSum : minSum;
    }

    int findMaxSum(vector<int>& nums) {
        int maxSum = nums[0];
        int sum = 0;

        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            if (maxSum < sum) maxSum = sum;
            if (sum < 0) sum = 0;
        }

        return maxSum;
    }

    int findMinSum(vector<int>& nums) {
        int minSum = nums[0];
        int sum = 0;

        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            if (minSum > sum) minSum = sum;
            if (sum > 0) sum = 0;
        }

        return minSum;
    }
};

int main() {
    Solution s;
    vector<int> nums;

    // 3
    nums = {1,-2,3,-2};
    cout << s.maxSubarraySumCircular(nums) << endl;

    // 10
    nums = {5,-3,5};
    cout << s.maxSubarraySumCircular(nums) << endl;

    // -2
    nums = {-3,-2,-3};
    cout << s.maxSubarraySumCircular(nums) << endl;

    // 4
    nums = {3,-1,2,-1};
    cout << s.maxSubarraySumCircular(nums) << endl;

    // 15
    nums = {6,9,-3};
    cout << s.maxSubarraySumCircular(nums) << endl;
}