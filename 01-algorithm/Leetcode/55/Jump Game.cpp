#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reachable = nums[0];
        int cur = 0;

        while (cur < nums.size() && cur <= reachable) {
            int newReachable = cur + nums[cur];
            reachable = max(reachable, newReachable);

            cur++;
        }

        return (cur == nums.size()) ? true : false;
    }
};

int main() {
    Solution s;
    vector<int> nums;

    // true
    nums = {2,3,1,1,4};
    cout << s.canJump(nums) << endl;

    // false
    nums = {3,2,1,0,4};
    cout << s.canJump(nums) << endl;
}