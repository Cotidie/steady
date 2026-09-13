#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int canSplit(vector<int>& nums, int target, int maxCount) {
    int sum = 0;
    int firstPosition = -1;

    for (int i=nums.size()-1; i>=0; i--) {
        sum += nums[i];
        if (sum > target) {
            maxCount--;
            sum = nums[i];
            firstPosition = i;
        }
    }

    if (maxCount > 0) return 0;
    else if (maxCount == 0) return firstPosition;
    else return -1;
}

int solution () {
    int length, split, maxSplit;
    cin >> length >> split >> maxSplit;

    vector<int> positions(split+1);
    for (int i=0; i<split; i++) {
        int position;
        cin >> position;

        positions[i] = position; 
    }
    positions[split] = length;
    sort(positions.begin(), positions.end());

    vector<int> lengths(split+1);
    lengths[0] = positions[0];
    for (int i=1; i<=split; i++) {
        lengths[i] = positions[i]-positions[i-1];
    }

    int lBound = *max_element(lengths.begin(), lengths.end());
    int uBound = length;
    
    int minLength = uBound;
    int firstPosition = -1;
    while (lBound <= uBound) {
        int mid = lBound + (uBound - lBound) / 2;
        int splitPosition = canSplit(lengths, mid, maxSplit);

        if (splitPosition >= 0) {
            minLength = mid;
            firstPosition = splitPosition;
            uBound = mid-1;
        } else {
            lBound = mid+1;
        }
    }
    
    cout << minLength << " " << positions[firstPosition] << endl;

    return 0;
}

int main() {
    while (true) {
        solution();
    }
}