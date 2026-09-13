## Link
[Course Schedule](https://leetcode.com/problems/course-schedule/description/)

## Topic
- Tree
- DFS

## Approach
![img](https://i.imgur.com/BfcdX5F.png)

1. Loop through the graph via DFS. Prepare two arrays:
    - **Done**: nodes that are done and popped from the stack.
    - **InStack**: nodes that are currently in stack.
2. If you visit a node that's currently in stack, it's a cycle.
    - Needs to separate `Done` and `InStack` to 
3. If a cycle is detected, the course never finish.


