#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int lBound = *max_element(nums.begin(), nums.end());
        int uBound = accumulate(nums.begin(), nums.end(), 0);
        
        int minimum = uBound;
        while (lBound <= uBound) {
            int mid = lBound + (uBound-lBound) / 2;

            if (canSplit(nums, mid, k)) {
                minimum = mid;
                uBound = mid-1;
            } else {
                lBound = mid+1;
            }
        }   

        return minimum;
    }

    bool canSplit(vector<int>& nums, int target, int cnt) {
        int subarrays = 0;
        int sum = 0;
        for (int num : nums) {
            sum += num;
            if (sum > target) {
                sum = num;
                subarrays++;
            }
        }
        subarrays++;
        
        return subarrays <= cnt;
    }
};

int main() {
    Solution s;
    vector<int> nums;
    int k;

    // 18
    nums = {7,2,5,10,8};
    k = 2;
    cout << s.splitArray(nums, k) << endl;

    // 9
    nums = {1,2,3,4,5};
    k = 2;
    cout << s.splitArray(nums, k) << endl;
}