#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> moves = {
    {-1,2}, {-2, 1}, {-2, -1}, {-1, -2},
    {1, -2}, {2, -1}, {2, 1}, {1, 2}
};

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        double probs[n][n][k+1];
        
        for (int x=0; x<n; x++) {
            for (int y=0; y<n; y++) {
                probs[x][y][0] = 1;
            }
        }

        for (int step=1; step<=k; step++) {
            for (int x=0; x<n; x++) {
                for (int y=0; y<n; y++) {
                    double prob = 0;

                    for (auto move : moves) {
                        int nx = x+move[0];
                        int ny = y+move[1];

                        if (isInside(nx, ny, n)) {
                            prob += probs[nx][ny][step-1];
                        }
                    }

                    probs[x][y][step] = prob / 8;
                }
            }
        }

        return probs[row][column][k];
    }

    bool isInside(int row, int col, int n) {
        return (row >= 0 && col >= 0) &&
            (row < n && col < n);
    }
};

int main() {
    Solution s;
    int n, k, row, column;

    // 1.0000
    n = 1; k = 0;
    row = 0; column = 0;
    cout << s.knightProbability(n, k, row, column) << endl;

    // 0.0625
    n = 3; k=2;
    row=0;column=0;
    cout << s.knightProbability(n, k, row, column) << endl;
}