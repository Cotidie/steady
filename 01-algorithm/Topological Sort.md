# Topological Sort
- [Topological Sort](#topological-sort)
  - [Overview](#overview)
  - [DFS](#dfs)
    - [Algorithm](#algorithm)
    - [Pseudo Code](#pseudo-code)
  - [Kahn's Algorithm](#kahns-algorithm)
    - [Algorithm](#algorithm-1)
    - [Pseudo Code](#pseudo-code-1)


## Overview
![topological sort](.images/topological%20sort-2.jpg)  
 Topological sort is a technique that finds a dependency path(a.k.a topological ordering) of the given graph. It only works with Directed Acyclic Graph(DAG) which doesn't have **any cycle** in a **directed** graph. Topological sort is widely used in dependency searching and scheduling.
  - Topological sort is a exhaustive search by nature, which costs `O(V+E)` complexity

## DFS
  A reverse order of DFS from any given node is itself a topological sort. To detect a cycle, use **DFS** on a directed graph or **Union-Find** on a undirected graph.

> DFS method can't solve a problem which has two or more dependencies.


### Algorithm
1. Pick a random node from the given graph
    - Preferably a node of zero indegree
2. Search paths using DFS
    - can use a stack or recursion
    - mark the nodes as visiting (`temporary`)
3. When returning from DFS, put searched nodes to a result array in reverse order
    - mark the nodes as completed (`permanent`)
    - unmark the nodes from visiting (`temporary`)
4. After emptying a stack, repeat until all nodes are visited
    - pick a node from unvisited list
5. Finally the resulting array is a topological sort

### Pseudo Code
```cpp
L ← Empty list that will contain the sorted nodes
while exists nodes without a permanent mark do
    select an unmarked node n
    visit(n)

function visit(node n)
    if n has a permanent mark then
        return
    if n has a temporary mark then
        stop   (graph has at least one cycle)

    mark n with a temporary mark

    for each node m with an edge from n to m do
        visit(m)

    remove temporary mark from n
    mark n with a permanent mark
    add n to head of L
```

## Kahn's Algorithm
Kahn's Algorithm works by keeping track of indegree number of a node. A cycle is detected when there are less than `|V|` after a complete search. 

### Algorithm
1. Calculate in-degree for each of the vertex.
2. Pick all the vertices with in-degree 0 and put them into a queue
3. Remove a vertex and then:
    - Decrease in-degree by 1 for all its neighboring nodes
    - if the in-degree of a neighboring node is 0, put it to the queue
3. Repeat until the queue is empty
4. If the count of vertices is less than `|V|`, it has a cycle

### Pseudo Code
The following pseudo code is from Wikipedia
```cpp
Kahn’s–Algorithm (graph)
 
L —> An empty list that will contain the sorted elements
S —> A set of all vertices with no incoming edges (i.e., having indegree 0)
 
while S is non-empty do
    remove a vertex n from S
    add n to tail of L
    for each vertex m with an edge e from n to m do
        remove edge e from the graph
        if m has no other incoming edges, then insert m into S
            insert m into S
 
if graph has edges then
    return report “graph has at least one cycle”
else
    return L “a topologically sorted order” 
```

### Implementation
```cpp
struct Node {
    int indegree = 0;
    vector<int> next; 
};

class Topsort {
public:
    Topsort(int size) {
        nodes = vector<Node>(size+1);
    }

    void set(int before, int next) {
        if (before == next) return;
        nodes[before].next.push_back(next);
        nodes[next].indegree += 1;
    }

    vector<int> sort() {
        vector<int> result;
        queue<int> q;
        
        for (int i=1; i<nodes.size(); i++) {
            if (nodes[i].indegree == 0) q.push(i);
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            result.push_back(cur);

            for (int next : nodes[cur].next) {
                nodes[next].indegree -= 1;
                if (nodes[next].indegree == 0) q.push(next);
            }
        }

        return result;
    }
private:
    vector<Node> nodes;
};
```