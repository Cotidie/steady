#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<vector<string>> result;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        result = vector<vector<string>>();
        vector<int> queens = vector<int>(n, -1);
        
        place(0, queens);

        return result;
    }

    void place(int row, vector<int>& queens) {
        if (row == queens.size()) {
            result.push_back(buildBoardString(queens));
            return;
        }
        
        for (int c=0; c<queens.size(); c++) {
            if (!isPlacable(row, c, queens)) continue;

            queens[row] = c;
            place(row+1, queens);
        }
    }

    vector<string> buildBoardString(vector<int>& queens) {
        vector<string> res(queens.size());

        for (int r=0; r<queens.size(); r++) {
            res[r] = buildRowString(queens[r], queens.size());
        }

        return res;
    }

    string buildRowString(int queen, int size) {
        string result = "";
        for (int i=0; i<size; i++) {
            if (i == queen) result += "Q";
            else result += ".";
        }

        return result;
    }

    // can reuse
    bool isPlacable(int row, int col, vector<int>& queens) {
        vector<bool> placable(queens.size(), true);
        
        for (int r=0; r<row; r++) {
            int queen = queens[r];
            placable[queen] = false;

            int move = row - r;
            int leftDiagonal = queen - move;
            int rightDiagonal = queen + move;

            if (leftDiagonal >= 0) placable[leftDiagonal] = false;
            if (rightDiagonal < queens.size()) placable[rightDiagonal] = false;
        }

        return placable[col];
    }
};

int main() {
    Solution s;
    int n;

    // ".Q.."
    // "...Q"
    // "Q..."
    // "..Q."

    // "..Q."
    // "Q..."
    // "...Q"
    // ".Q.."
    n = 4;
    for (auto row : s.solveNQueens(n)) {
        for (auto col : row) cout << col << endl;
        cout << endl;
    }
    cout << endl;


    n = 1;
    for (auto row : s.solveNQueens(n)) {
        for (auto col : row) cout << col;
        cout << endl;
    }
    cout << endl;
}