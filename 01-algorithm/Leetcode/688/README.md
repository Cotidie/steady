## Link
[Knight Probability in Chessboard](https://leetcode.com/problems/knight-probability-in-chessboard/)

## Topic
* Dynamic Programming

## Approach
1. **Subproblem**: `prob[x][y][s]`, where the night reaches to `(x, y)` after `s` steps
2. **Guess**
   - the sum of every valid positions of `s-1` step / 8 is the prob. of `s` step
   - divide by 8, since it's one of eight choices from the previous steps
3. **Recurrence**: `prob[x][y][s]` is
   - 1, if `s` is zero
   - sum of `prob[x+d][y+d][s-1]` / 8, otherwise
4. **Solve**: `prob[x][y][s]`

## Note
- The whole set is power of `n`, not the actual number of valid moves.
- It assumes that even if it gets out of the board, it continues to move.