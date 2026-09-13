## Link
[사이클 게임](https://www.acmicpc.net/problem/20040)

## Topic
- Union-Find

## Approach
 각 번호를 노드로 하고, 주어지는 진행상황에 따라 노드를 병합하면서 사이클을 확인한다. Union-Find로 사이클을 확인하는 문제이다.
 
1. 주어진 크기의 Disjoint Set을 정의한다.
2. 진행상황을 받으며 두 노드를 병합한다.
3. 사이클이 발생하면 해당 진행번호를 출력하고, 전부 병합이 되었다면 0을 출력한다.
