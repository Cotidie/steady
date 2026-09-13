## Link
[N-Queens](https://leetcode.com/problems/n-queens/)

## Concepts
* Back Tracking

# Approach

- Prepare an array to store locations of queens
    - `queens[row] = column`
- Iterate by rows using dfs, and try placing a queen to a column
- When placing a queen to a column, check if it is placable
    - `check(int row, int col, vector<int>& queens)`
- If placable, put the location to `queens[row]`
- When it reaches to the end row, build a string of the chess board
- Return an array of chess boards after all the iterations
