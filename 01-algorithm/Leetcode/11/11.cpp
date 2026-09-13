#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int pLeft = 0;
        int pRight = height.size()-1;

        int max = -1;
        while (pLeft < pRight) {
            int x = pRight - pLeft;
            int y = (height[pLeft] > height[pRight]) ? height[pRight] : height[pLeft];
            int area = x * y;

            if (area > max) max = area;
            
            (height[pLeft] > height[pRight]) ? pRight-- : pLeft++; 
        }

        return max;
    }
};