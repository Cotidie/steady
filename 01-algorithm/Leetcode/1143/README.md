## Link
[https://leetcode.com/problems/longest-common-subsequence/description/](https://leetcode.com/problems/longest-common-subsequence/description/)

## Topic
* Dynamic Programming (2d)

## Approach
1. **Subproblem**: `TextA[i:]`, `TextB[j:]`. Find LCS between the two sub-strings.
2. **Guess**
   - if two chars are matching, it should be included. 
   - if not, consider two cases: `TextA[i+1:]` or `TextB[j+1:]`.  
3. **Recurrence**: `DP(i, j)` is
   - if matching, `1 + DP(i+1, j+1)`
   - if not matching, `max(DP(i+1, j), DP(i, j+1))`
4. **Solve**: `DP(0, 0)`
   
## Note
![Guess](https://i.imgur.com/qXLIfCk.png)  
Let TextA = "abcde" and TextB = "ace" then
- `DP(2, 1)` means LCS between "cde" and "ce"
- if not matching, examine both cases where one char is ignored.