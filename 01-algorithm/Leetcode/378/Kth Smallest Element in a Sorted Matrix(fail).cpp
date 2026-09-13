#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        int min = matrix[0][0];
        int max = matrix[rows-1][cols-1];

        while (min != max) {
            int mid = min + (max - min) / 2; // prevent overflow 
            int count = countLessThanEqual(matrix, mid);

            // mid 이하의 수를 세었으므로 답이 될 수 없다.
            if (count < k) min = mid+1;
            // 답이 될 수 있다.
            else max = mid-1;
        }

        return min;
    }

    int countLessThanEqual(vector<vector<int>>& matrix, int mid) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        int count = 0;
        int row = 0;
        int col = 0;

        while (matrix[row][cols-1] <= mid) {
            count += cols;
            row++;
        }

        while (matrix[row][col] <= mid) {
            count++;
            col++;
        }

        return count;
    }
};

int main() {
    Solution s;
    vector<vector<int>> matrix;
    int k;

    // 13
    matrix = {{1,5,9},{10,11,13},{12,13,15}};
    k = 8;
    cout << s.kthSmallest(matrix, k) << endl;

    // 1
    matrix = {{-5}};
    k = 1;
    cout << s.kthSmallest(matrix, k) << endl;

    // 1
    matrix = {{1, 2}, {1,3}};
    k = 2;
    cout << s.kthSmallest(matrix, k) << endl;
}