## Link
[Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/description/)

## Topic
- Tree
- Recursion
- Queue
- BFS

## Approach
![Right View](https://i.imgur.com/NQNHvsI.png)  
- 트리를 순회하기 전 다음과 같은 자료구조를 준비한다.
  - 트리를 레벨 단위로 순회하기 위해 큐를 준비한다. (BFS)
  - 노드와 레벨 정보를 담을 NodeWithLevel 구조체를 준비한다. 
  - 결과를 담을 벡터를 준비한다. (인덱트 = 레벨)
- 트리를 레벨 단위로 순회한다. (큐에는 미리 루트 노드가 담겨 있다)
  - 큐에서 노드를 꺼낸다.
  - 꺼낸 노드의 레벨에 맞추어 결과 벡터를 업데이트 한다. 
  - 왼쪽과 오른쪽 자식 노드를 큐에 담는다.
  - 큐가 빌 때까지 반복한다.

## Note
(남길말)  