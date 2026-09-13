#include <iostream>
#include <vector>

using namespace std;

void initDP(vector<vector<bool>> &dp, vector<int> &nums) {
    for (int i=0; i<dp.size(); i++) {
        dp[i][i] = true;
    }

    for (int i=0; i<dp.size()-1; i++) {
        if (nums[i] == nums[i+1]) {
            dp[i][i+1] = true;
            dp[i+1][i] = true;
        }
    }
}

void fillDP(vector<vector<bool>> &dp, vector<int> &nums) {
    if (dp.size() < 3) return;

    for (int r=dp.size()-3; r>=0; r--) {
        for (int c=r+2; c<dp.size(); c++) {
            if (dp[r+1][c-1] == false) continue;

            if (nums[r] == nums[c]) {
                dp[r][c] = true;
                dp[c][r] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int size;
    cin >> size;
    
    vector<int> nums(size);
    for (int i=0; i<size; i++) {
        int val;
        cin >> val;

        nums[i] = val;
    }

    vector<vector<bool>> dp(size, vector<bool>(size, false));
    initDP(dp, nums);
    fillDP(dp, nums);

    int questions;
    cin >> questions;

    for (int i=0; i<questions; i++) {
        int start, end;
        cin >> start >> end;

        cout << dp[start-1][end-1] << '\n';
    }
}