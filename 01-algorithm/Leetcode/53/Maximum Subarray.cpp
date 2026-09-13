#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int sum = 0;
        int cur = 0;

        while (cur < nums.size()) {
            sum += nums[cur];
            maxSum = max(maxSum, sum);
            if (sum < 0) sum = 0;

            cur++;
        }

        return maxSum;
    }
};

int main() {
    Solution s;
    vector<int> nums;

    // 6
    nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << s.maxSubArray(nums) << endl;

    // 1
    nums = {1};
    cout << s.maxSubArray(nums) << endl;

    // 23
    nums = {5,4,-1,7,8};
    cout << s.maxSubArray(nums) << endl;
}