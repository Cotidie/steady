## Link
[텀 프로젝트](https://www.acmicpc.net/problem/9466)

## Topic
- Union Find

## Approach

 규칙에 따라 사이클이 발생한 학생만 팀을 이룰 수 있다. 사이클 판단은 Union-Find로 가능하고, 사이클이 발생하면 DFS를 통해 그 개수를 세어야 한다.

1. 사이클을 판단할 Disjoint Set과 선호하는 학생 간 간선으로 이어 그래프를 만든다.
2. 간선을 하나씩 순회하며 두 학생 간 Union을 수행한다.
3. 사이클이 발생하면 그 학생에서부터 사이클을 따라 그 개수를 센다.
    - outdegree는 모두 1이므로 단순 while 문으로 가능하다.
4. 전체 학생에서 사이클 개수를 제외한 수를 반환한다.
