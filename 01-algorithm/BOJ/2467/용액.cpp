#include <iostream>
#include <vector>

using namespace std;

int main() {
    int size;
    cin >> size;

    vector<long> nums = vector<long>(size);
    for (int i=0; i<size; i++) {
        long val;
        cin >> val;

        nums[i] = val;
    }

    int left=0, right=size-1;
    long answer = 10000000000;
    int answerLeft, answerRight;

    while (left < right) {
        long sum = nums[left] + nums[right];

        if (answer >= abs(sum)) {
            answer = abs(sum);
            answerLeft = nums[left];
            answerRight = nums[right];
        }
        if (sum < 0) left++;
        else right--;
    }

    cout << answerLeft << " " << answerRight << '\n';
}