## Link
[Unique Paths](https://leetcode.com/problems/unique-paths/)

## Topic
* Dynamic Programming (2d)

## Approach
1. **Subproblem**: `paths[x, y]`, the number of unique paths a robot can have to `(x, y)`
2. **Guess**: How many unique paths are there in `paths[x-1, y]` and `paths[x, y-1]`?
3. **Recurrence**: `paths(x, y)` is sum of
    - `paths[x-1, y]` + `paths[x, y-1]` (a robot can only move down or right)
4. **Topology**: column-wise
5. **Solve**: `paths[x-1, y-1]`
