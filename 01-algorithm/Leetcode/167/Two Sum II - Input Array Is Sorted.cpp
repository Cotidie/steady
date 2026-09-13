#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int size = numbers.size();
        vector<int> result = {0, 0};

        for (int i=0; i<size-1; i++) {
            int min = i+1;
            int max = size-1;
            
            while (min <= max) {
                int mid = min + (max-min) / 2;
                int sum = numbers[i] + numbers[mid];

                if (sum == target) return {i+1, mid+1};
                else if (sum > target) max = mid-1; 
                else min = mid+1;
            }
        }

        return result;
    }
};

int main() {
    Solution s;

    vector<int> numbers;
    int target;

    // [1, 2]
    numbers = {2,7,11,15};
    target = 9;
    for (int num: s.twoSum(numbers, target)) cout << num << " ";
    cout << endl;

    // [1, 3]
    numbers = {2,3,4};
    target = 6;
    for (int num: s.twoSum(numbers, target)) cout << num << " ";
    cout << endl;

    // [1, 2]
    numbers = {-1, 0};
    target = -1;
    for (int num: s.twoSum(numbers, target)) cout << num << " ";
    cout << endl;
}