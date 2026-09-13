#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int INTMAX = INT32_MAX;

struct Size {
    int row, col;
};

class DP {
public:
    DP(int size) {
        matrix = vector<Size>(size);
    }

    void set(int row, int col, int num) {
        matrix[num].row = row;
        matrix[num].col = col;
    }

    int run() {
        int nums = matrix.size();
        vector<vector<int>> dp(nums, vector<int>(nums, INTMAX));

        for (int i=0; i<nums-1; i++) {
            dp[i][i] = 0;
            dp[i][i+1] = matrix[i].row * matrix[i].col * matrix[i+1].col;
        }
        dp[nums-1][nums-1] = 0;

        for (int s=2; s<nums; s++) {
            for (int low=0; low<nums-s; low++) {
                int high = low+s;
                for (int cut=low; cut<high; cut++) {
                    dp[low][high] = min(
                        dp[low][high],
                        dp[low][cut] + dp[cut+1][high] + getCost(low, cut, high)
                    );
                }
            }
        }

        return dp[0][nums-1];
    }

private:
    int getCost(int low, int cut, int high) {
        return matrix[low].row * matrix[cut].col * matrix[high].col;
    }

    vector<Size> matrix;
};

int main() {
    int nums;
    cin >> nums;

    DP dp(nums);
    for (int i=0; i<nums; i++) {
        int row, col;
        cin >> row >> col;

        dp.set(row, col, i);
    }

    cout << dp.run() << '\n';
}