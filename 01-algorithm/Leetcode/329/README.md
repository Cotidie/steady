## Link
[Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

## Topic
- DFS

## Approach

0. Prepare an array for memoization
    - memo the max length from the current node 
1. Iterate throught all the numbers in the given matrix, and do dfs
    - exit dfs if it meets lower number or an edge
    - exit if the current node has memoized value
2. on exiting a dfs, return the current max path length
    - update memoization of the current node
3. Return the max value from the memoization array
