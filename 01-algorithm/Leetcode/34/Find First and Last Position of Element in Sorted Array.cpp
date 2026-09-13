#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    Solution() {
        leftIdx = -1;
        rightIdx = -1;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        leftIdx = -1; rightIdx = -1;

        binarySearch(nums, 0, nums.size()-1, target);

        return {leftIdx, rightIdx};
    }

    void binarySearch(vector<int>& nums, int start, int end, int target) {
        if (start < 0 || end >= nums.size()) return;
        if (start > end) return;

        int mid = (start + end) / 2;
        if (nums[mid] > target) {
            binarySearch(nums, start, mid-1, target);
        }
        if (nums[mid] < target) {
            binarySearch(nums, mid+1, end, target);
        }
        if (nums[mid] == target) {
            leftIdx = findLeftBound(nums, start, mid, target);
            rightIdx = findRightBound(nums, mid, end, target);
        }
    }

    int findLeftBound(vector<int>& nums, int start, int end, int target) {
        int mid = (start + end) / 2;
        if (nums[mid] == target) {
            if (mid == start) return start;
            if (nums[mid-1] != target) return mid;
            return findLeftBound(nums, start, mid-1, target);
        }
        if (nums[mid] != target) {
            if (nums[mid+1] == target) return mid+1;
            return findLeftBound(nums, mid+1, end, target);
        }
    }

    int findRightBound(vector<int>& nums, int start, int end, int target) {
        int mid = (start + end) / 2;
        if (nums[mid] == target) {
            if (mid == end) return end;
            if (nums[mid+1] != target) return mid;
            return findRightBound(nums, mid+1, end, target);
        }
        if (nums[mid] != target) {
            if (nums[mid-1] == target) return mid-1;
            return findRightBound(nums, start, mid-1, target);
        }
    }

private:
    vector<int>* nums;
    int leftIdx = -1;
    int rightIdx = -1;
};

int main() {
    Solution s;
    vector<int> nums, answer;
    int target;

    // [3, 4]
    nums = {5,7,7,8,8,10};
    target = 8;
    answer = s.searchRange(nums, target);
    cout << answer[0] << ", " << answer[1] << endl;

    // [-1, -1]
    nums = {5,7,7,8,8,10};
    target = 6;
    answer = s.searchRange(nums, target);
    cout << answer[0] << ", " << answer[1] << endl;

    // [-1, -1]
    nums = {};
    target = 0;
    answer = s.searchRange(nums, target);
    cout << answer[0] << ", " << answer[1] << endl;

    // [0, 1]
    nums = {2, 2};
    target = 2;
    answer = s.searchRange(nums, target);
    cout << answer[0] << ", " << answer[1] << endl;
}