#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> grid(m, vector<int>(n, 1));

        for (int r=1; r<m; r++) {
            for (int c=1; c<n; c++) {
                grid[r][c] = grid[r-1][c] + grid[r][c-1];
            }
        }

        return grid[m-1][n-1];
    }
};

int main() {
    Solution s;
    int m, n;

    // 28
    m = 3; n = 7;
    cout << s.uniquePaths(m, n) << endl;

    // 3
    m = 3; n = 2;
    cout << s.uniquePaths(m, n) << endl;
}