## Link
[줄 세우기](https://www.acmicpc.net/problem/2252)

## Topic
- Topological Sort

## Approach
대소관계는 먼저 방문해야할 종속성을 의미하고, 이는 위상정렬을 통해 나열할 수 있다. 키가 작은 이들부터 먼저 모두 세운 이후 큰 이들을 세우게 된다.

1. 위상정렬을 위해 indegree와 종속성을 기록한다.
2. indegree가 0인 사람부터 모두 큐에 넣는다.
3. 큐에서 하나씩 꺼내 키가 큰 사람들에 대해 indegree를 하나 감소시킨다.
    -  indegree가 0이 되면 큐에 넣는다.
    -  꺼낸 사람은 정렬 결과 배열에 넣는다.
4. 큐가 빌 때까지 반복한다.
   
