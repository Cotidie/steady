## Link
[내려가기](https://www.acmicpc.net/problem/2096)

## Topic
- DP (1차원)

## Approach
 완전 탐색은 메모리 제한으로 인해 불가능하다. DP로 접근해야 하며, 이때 현재 행까지의 최대값, 최소값을 저장할 배열 2개로 풀이가 가능하다.

1. **Subproblem**: `Min[0:3], Max[0:3] (r)`, r 행에서 각 자리(0~2)의 최대/최소 점수
2. **Guess**: `Min[i], Max[i]`가 최대, 최소를 가지려면?
3. **Recurrence**: `Min[0:3][r]`은 이전 단계에서 올 수 있는 경우 중 가장 작은 곳에서 와야 한다.
   - `Min[0][r]` = `min(Min[0][r-1], Min[1][r-1])`
   - `Min[1][r]` = `min(Min[0][r-1], Min[1][r-1], Min[2][r-1])` 
   - `Min[0][r]` = `min(Min[1][r-1], Min[2][r-1])`
   - Max 또한 같은 로직이다.
4. **Solve**: `min(Min[0:3][r])`, `max(Max[0:3][r])`
