## Link
[ACM Craft](https://www.acmicpc.net/problem/1005)

## Topic
- Topological Sort

## Approach

종속성이 만족되는 순서대로 순회를 해야 하므로 Kahn 방식으로 위상정렬을 수행한다. DFS로 할 시 1개 종속성에 대해서만 고려하기 때문에 지금처럼 2개 이상의 종속성이 있는 경우를 다룰 수 없다. 

1. 위상정렬을 위해 indegree 배열, 건설시간 배열, 큐를 준비한다.
2. 입력을 받으면서 건물마다 indegree를 기록한다.
    - A -> B에서 B의 indegree 증가
3. indegree가 0인 건물을 찾아 queue에 모두 넣는다.
4. queue에서 꺼내어 다음 건물에 대해 indegree를 하나씩 지운다.
    - 지운 결과 indegree가 0이 되면 큐에 넣는다.
    - 다음 건물을 짓는데 걸리는 시간을 비교해 더 오래 걸리면 갱신한다.
5. 큐가 빌 때까지 4를 반복한다.
