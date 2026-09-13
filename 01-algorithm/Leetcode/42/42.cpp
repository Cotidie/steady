/*
    Title: Trapping Rain Water
    Link: https://leetcode.com/problems/trapping-rain-water/
*/
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int pLeft = 0;
        int pRight = height.size() - 1;

        int maxLeft = height[pLeft];
        int maxRight = height[pRight];

        int water = 0;

        while (pLeft < pRight) {
            if (height[pLeft] > height[pRight]) {
                pRight--;
                maxRight = max(maxRight, height[pRight]);
                water += max(0, maxRight-height[pRight]);
            } else {
                pLeft++;
                maxLeft = max(maxLeft, height[pLeft]);
                water += max(0, maxLeft-height[pLeft]);
            }
        }

        return water;
    }
};