# Minimum Spanning Tree
![minimum-spanning-tree](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Minimum_spanning_tree.svg/1200px-Minimum_spanning_tree.svg.png)  
 MST(Minimum Spanning Tree) is a spanning tree that connects all the vertices in a way that it minimizes the sum of all edges. There can be multiple minimum spanning trees in a graph. To construct MST, two popular algorithms are used: **Kruskal** and **Prim**.

## Kruskal
![kruskal](https://www.dotnetlovers.com/Images/KruskalsAlgorithmforMinimumSpanningTreeMST110201931155AM.png)  
 Kruskal's algorithm builds a MST based on edges in order. It selects the next minimum edge to add it to the growing MST, and stops when there are all the vertices in the growing MST. When connecting two vertices, it uses `disjoint set` to detect a cycle. 

### Algorithm
1. Prepare an array and a priority queue
    - **array**: to detect a cycle using union-find (disjoint set)
    - **priority queue**: to sort edges
2. Pop from the priority queue and try add the edge to MST
    - if two nodes have the same root, skip
    - if not, merge two nodes 
3. Stop when there are (V-1) edges in MST

### Pseudo Code
```cpp
KRUSKAL(G):
    A = ∅
    For each vertex v ∈ G.V:
        MAKE-SET(v)
    For each edge (u, v) ∈ G.E ordered by increasing order by weight(u, v):
        if FIND-SET(u) ≠ FIND-SET(v):       
        A = A ∪ {(u, v)}
        UNION(u, v)
    return A
```