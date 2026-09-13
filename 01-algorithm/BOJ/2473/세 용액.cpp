#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pointer {
    int a, b, c;
};

int main() {
    int size;
    cin >> size;

    vector<long> nums(size);
    for (int i=0; i<size; i++) {
        long val;
        cin >> val;

        nums[i] = val;
    }

    sort(nums.begin(), nums.end());

    long closest = 3000000001;
    Pointer p;
    for (int i=0; i<size-2; i++) {
        int numA = nums[i];

        int low = i+1;
        int high = size-1;
        while (low < high) {
            long sum = numA + nums[low] + nums[high];
            if (abs(sum) < closest) {
                closest = abs(sum);
                p.a = i; p.b = low; p.c = high;
            }

            if (sum < 0) {
                low++;
            } else if (sum > 0) {
                high--;
            } else {
                cout << numA << " " << nums[low] << " " << nums[high] << '\n';
                return 0;
            }
        }
    }

    cout << nums[p.a] << " " << nums[p.b] << " " << nums[p.c] << '\n';
}