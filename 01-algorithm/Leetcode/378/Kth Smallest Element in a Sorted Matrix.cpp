#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    Node(int val, int row, int col): val(val), row(row), col(col) {};

    bool operator<(const Node& other) const {
        return this->val > other.val;
    }

    int val, row, col;
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int count = 0;

        priority_queue<Node> pq;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        int row = 0;
        int col = 0;

        pq.push(Node(matrix[0][0], 0, 0));
        visited[0][0] = true;

        while (!pq.empty()) {
            Node current = pq.top();pq.pop();
            row = current.row; col = current.col;
            count++;
            
            if (count == k) return current.val;

            if (row+1 < rows && !visited[row+1][col]) {
                pq.push(Node(matrix[row+1][col], row+1, col));
                visited[row+1][col] = true;
            }

            if (col+1 <cols && !visited[row][col+1]) {
                pq.push(Node(matrix[row][col+1], row, col+1));
                visited[row][col+1] = true;
            }
        }

        return 0;
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