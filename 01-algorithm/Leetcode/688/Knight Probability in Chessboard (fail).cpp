#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int onBoard;
vector<vector<int>> moves = {
    {-1,2}, {-2, 1}, {-2, -1}, {-1, -2},
    {1, -2}, {2, -1}, {2, 1}, {1, 2}
};

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        onBoard = 0;
        double wholeSet = pow(8, k);

        move(n, k, row, column, 0);

        return onBoard / wholeSet;
    }

    void move(int size, int max, int row, int col, int depth) {
        if (row < 0 || col < 0) return;
        if (row >= size || col >= size) return;
        if (depth == max) {
            onBoard++;
            return;
        }

        for (auto next : moves) {
            move(size, max, row+next[0], col+next[1], depth+1);
        }
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