#include <vector>
#include <iostream>

using namespace std;

int longest = 0;
vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<vector<int>> memo;

struct Point {
    int row;
    int col;
};

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        longest = 0;
        memo = vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size(), 0));

        for (int i=0; i<matrix.size(); i++) {
            for (int j=0; j<matrix[i].size(); j++) {
                dfs(Point{i, j}, -1, matrix);
            }
        }

        return longest;
    }

    int dfs(Point cur, int prev, vector<vector<int>>& matrix) {
        if (prev >= matrix[cur.row][cur.col]) return 0;
        if (memo[cur.row][cur.col] > 0) return memo[cur.row][cur.col];

        int maxPath = 1;
        for (auto dir : dirs) {
            Point next = Point{cur.row+dir[0], cur.col+dir[1]};

            if (next.row < 0 || next.col < 0) continue;
            if (next.row >= matrix.size() || next.col >= matrix[0].size()) continue;

            int subPath = 1 + dfs(next, matrix[cur.row][cur.col], matrix);
            if (subPath > maxPath) maxPath = subPath;
        }

        memo[cur.row][cur.col] = maxPath;
        if (longest < maxPath) longest = maxPath;
        return maxPath;
    }
};

int main() {
    Solution s;
    vector<vector<int>> matrix;

    // 4
    matrix = {{9,9,4},{6,6,8},{2,1,1}};
    cout << s.longestIncreasingPath(matrix) << endl;

    // 4
    matrix = {{3,4,5},{3,2,6},{2,2,1}};
    cout << s.longestIncreasingPath(matrix) << endl;

    // 1
    matrix = {{1}};
    cout << s.longestIncreasingPath(matrix) << endl;
}