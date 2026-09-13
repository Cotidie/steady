## Link
[Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)

## Topic
- Topological Sort

## Approach
![img](https://i.imgur.com/BfcdX5F.png)

1. Prepare a graph and two arrays
    - **graph**: to quickly find outdgree edges
    - **visiting**: to indicate nodes in a callstack (for cycle detection)
    - **completed**: to indicate nodes done searching
2. Iterate all unvisited nodes and do DFS each
    - put nodes to `visiting` while searching
    - pop nodes from `visiting` and put it to completed when exiting a dfs
3. If it detects a cycle, abort
4. When exiting each callstack of DFS, put nodes to a result array in reverse order
5. After all the iterations, return the result array
> step 2~4 is general topological sort

