## Link
[Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)

## Topic
* DFS

## Approach
It is about detecting a cycle in the middle of performing topological sort.  
If a cycle is detected, all the vertices currently visiting are not safe.

1. Prepare following arrays:
    - `visiting`: nodes that are currently in dfs stack 
    - `completed`: nodes that are done searching
    - `unsafe`: nodes that are connecting to a cycle
2. Iterate all the vertices and do DFS 
    - mark the node as `visiting` on entering
    - mark the node as `completed` on exiting
    - unmark the node from `visiting` on exiting
3. If the node is `visiting`, it's a cycle
    - mark the node as `unsafe` and exit
4. If a dfs ended by a cycle, mark the current node as `unsafe`
    - keep exiting to the root node
5. return safe nodes only
