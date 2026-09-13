## Link
[카드 게임](https://www.acmicpc.net/problem/16566)

## Topic
- Union Find

## Approach
 주어지는 수들 차례대로 가장 효율적으로 이길 수 있는 카드를 내야 한다. Union-Find는 어떤 수에 대해 그 다음으로 큰 수를 가리키도록 할 수 있다.

**(1)** 시간초과
1. 수중에 가진 패를 입력받아 정렬한다.
2. 가지고 있는 카드를 순회하며 수중에 없는 카드는 가장 가까운 큰 카드를 가리키도록 한다.
    - 수중에 없는 카드는 다음 카드에 병합한다. (Union-Find)
3. 철수가 낼 카드에 대해 다음으로 큰 카드를 낸다.
    - 낸 이후 다음 수에 병합한다.

## Note
- `ios::sync_with_stdio(false), cin.tie(NULL)`을 해야 시간초과를 피할 수 있다.
