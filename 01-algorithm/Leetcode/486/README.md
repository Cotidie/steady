## Link
[Predict the Winner](https://leetcode.com/problems/predict-the-winner/)

## Topic
* Dynamic Programming (2d)

## Approach
1. **Subproblem**: `Nums[i:j]`, where the first player gets the maximum score within the array.
   => The number of subproblems: `O(n^)`
2. **Guess**: In `Nums[i:j]`, which end the player would choose? 
3. **Recurrence**: `DP(i, j)` is the max value of
   - `Nums[i]` + (`Sum[i+1:j]` - `DP(i+1, j)`) (the left end is chosen)
   - `Nums[j]` + (`Sum[i:j-1]` - `DP(i, j-1)`) (the right end is chosen)
4. **Topology**: smaller to larger (fill the dp table diagonally)
5. **Solve**: `DP(0, n-1)`
   
## Note
![DP Table](https://i.imgur.com/uy1wdPD.png)  
- `DP[i][j]` holds the maximum score a player can get from `Nums[i, j+1]`
- The first column and the last row is added to prevent segmentation fault when accessing `[i+1]` and `[j-1]`
- Fill diagonally to compute from smaller to larger size of sub problem.