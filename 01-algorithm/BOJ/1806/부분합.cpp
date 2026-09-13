#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int search(vector<int> &nums, int target) {
    if (nums[0] >= target) return 1;

    int length = 1000000;
    int low=0, high=0;
    int sum=0;
    while (low <= high && high <= nums.size()) {
        if (sum < target) {
            sum += nums[high];
            high++;
        } else {
            sum -= nums[low];
            low++;
            length = min(length, high+1-low);
        }
    }

    return (length == 1000000) ? -1 : length;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, target;
    cin >> N >> target;

    vector<int> numbers(N);
    for (int i=0; i<N; i++) {
        int val;
        cin >> val;

        numbers[i] = val;
    }

    int len = search(numbers, target);
    
    if (len == -1) cout << 0 << '\n';
    else cout << len << '\n';
}