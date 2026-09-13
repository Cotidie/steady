## Link
[Jump Game](https://leetcode.com/problems/jump-game/)

## Concepts
* Dynamic Programming

# Approach
If all the numbers are non-zero, then it's always possible to reach to the end.  
It's about whether it can cross zero points.  

- Prepare an integer that keeps the maximum `reachable` index
- Iterate through the array and update `reachable` integer
    - As long as the current index is behind `reachable`, keep continue
- Returns true if it reached to the end.

# Complexity
- Time complexity: O(n)
