## Link
[팰린드롬?](https://www.acmicpc.net/problem/10942)

## Topic
- DP (2차원)

## Approach
 
`Text[i:j]`의 팰린드롬 여부를 알아보려면 바로 직전 범위 `Text[i+1, j-1]`의 팰린드롬 여부를 알아보면 빠르게 구할 수 있다. 직전에 팰린드롬이었다면 i와 j가 서로 같은 문자인지만 확인하면 되고, 팰린드롬이 아니었다면 이번 범위 또한 팰린드롬이 아니다. 

1. **Subproblem**: `DP[i][j]`, Text[i:j]의 팰린드롬 여부
2. **Guess**: 직전 범위 `DP[i+1][j-1]`이 팰린드롬이면 i, j만 비교하면 된다.
3. **Recurrence**: `DP[i+1][j-1]`의 팰린드롬 여부에 따라
    - `DP[i][j] = (Text[i] == Text[j])`, 직전에 팰린드롬이었을 때
    - `DP[i][j] = False`, 직전에 팰린드롬이 아니었을 때
4. **Solve**: `DP[i][j]`

DP 배열은 대칭이며, 초기값으로 DP[i][i]와 DP[i][i+1]을 채워넣어야 한다.

## Note