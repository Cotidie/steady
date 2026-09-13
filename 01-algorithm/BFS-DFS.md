# BFS-DFS
This document explains basics of BFS and DFS, and their applications in problem solving. **BFS**(Breadth First Search) and **DFS**(Depth First Search) are the two most common graph searching algorithms. Queue is typically used for BFS, and Stack/recursion for DFS. 

## BFS
```cpp
BFS (G, s)
  let Q be queue.
  Q.enqueue( s )

  mark s as visited.
  while ( Q is not empty)
    //Removing that vertex from queue,whose neighbour will be visited now
    v  =  Q.dequeue()

    for all neighbours w of v in Graph G
      if w is not visited 
        Q.enqueue( w )             
        mark w as visited.
```
1. Prepare a queue and an array
    - **queue**: stores nodes to visit
    - **array**: marks already visited nodes
2. Put a starting node into the queue
3. Pop from the queue and
    - put adjacent nodes
    - mark adjacent nodes as visited
3. Iterate until the queue is empty

### Level order traversal
![level-order-traversal](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS8kfsogDGt7Xe3g5KyevRUM8uP1-9fWJg9AA&usqp=CAU)  
BFS itself traverses a tree in a level order. In this case the queue should use a data structure that records both a node and its level. 

### 0-1 BFS
> [0-1 BFS Shortest Path](https://www.scaler.com/topics/data-structures/0-1-bfs-shortest-path-binary-graph/)

![0-1 bfs](https://images.velog.io/images/nmrhtn7898/post/556cd759-9591-4a0b-b3a4-20b0e204cd35/%E1%84%83%E1%85%A1%E1%84%8B%E1%85%AE%E1%86%AB%E1%84%85%E1%85%A9%E1%84%83%E1%85%B3.png)  

For a graph which has edges with weights of only 1 or 0, BFS can be used instead of Dijkstra to find the optimal path between two vertices. It works even without checking `visited` array since:
  - Edges can be sorted in ascending order without any sorting algorithm which takes `nlogn`
    - it replaces the need of priority queue in Dijkstra
    - Dequeue is used for this purpose
  - It removes the need of `visited` array if we can pop edges in ascending order

We can easily sort the queue using dequeue by putting 0 weights on the front. The steps are as follows:
1. Prepare a dequeue and an array to store the shortest distances from a source  
    - `dq`: a dequeue to store edges to explore next. Put the source node.
    - `distances`: an array to store shortest distances, initialized with positive infinites.
2. Pop from the `dq`, and update the shortest distances.  
    - if `distances[from] + edge.to < distances[to]`, update 
    - if not, ignore the target(`to`) node
3. If it's updated put the node based on the weight  
    - if it's 1, put the node on the back of `dq`
    - if it's 0, put the node on the front of `dq`
4. Repeat until the dequeue is empty

This improves the time complexity of the shortest path algorithm from `O(nLogn)` to `O(n)`, without the need of sorting.
