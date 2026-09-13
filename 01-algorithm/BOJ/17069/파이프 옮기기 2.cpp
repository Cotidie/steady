#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class House {
public:
    House(int size) {
        dp = vector<vector<vector<long>>>(
            size, vector<vector<long>>(
                size, vector<long>(
                    3, 0
                )
            )
        );

        house = vector<vector<int>>(
            size, vector<int>(
                size, 0
            )
        );
    };

    void calculate() {
        initDP();

        for (int r=1; r<house.size(); r++) {
            for (int c=1; c<house.size(); c++) {
                if (house[r][c] == 1) continue;

                dp[r][c][0] = getHorizontal(r, c);
                dp[r][c][1] = getVertical(r, c);
                dp[r][c][2] = getDiagonal(r, c);
            }
        }
    }

    void set(int row, int col, int val) {
        house[row][col] = val;
    }

    long getDP(int row, int col) {
        return dp[row][col][0] + dp[row][col][1] + dp[row][col][2];
    }
private:
    // 가로: DP[row][col-1][가로, 대각선]
    long getHorizontal(int row, int col) {
        return dp[row][col-1][0] + dp[row][col-1][2];
    }

    // 세로: DP[row-1][col][세로, 대각선]
    long getVertical(int row, int col) {
        return dp[row-1][col][1] + dp[row-1][col][2];
    }

    // 대각선: DP[row-1][col-1][가로, 세로, 대각선]
    // 단, 위쪽, 왼쪽이 장애물이어서는 안 된다.
    long getDiagonal(int row, int col) {
        if (house[row-1][col] == 1 || house[row][col-1] == 1) return 0;

        return dp[row-1][col-1][0] + dp[row-1][col-1][1] + dp[row-1][col-1][2];
    }

    void initDP() {
        // 첫 행 초기화
        for (int c=1; c<house.size(); c++) {
            if (house[0][c] == 1) return;

            dp[0][c][0] = 1;
        }
    }

    // 0: 가로, 1: 세로, 2: 대각선
    vector<vector<vector<long>>> dp;
    vector<vector<int>> house;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int size;
    cin >> size;

    House house(size);
    for (int r=0; r<size; r++) {
        for (int c=0; c<size; c++) {
            int val;
            cin >> val;

            house.set(r, c, val);
        }
    }

    house.calculate();

    cout << house.getDP(size-1, size-1) << '\n';
}