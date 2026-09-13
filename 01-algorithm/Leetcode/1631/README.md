## Link
[Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/description/)

## Concepts
* Dijkstra

## Approach
![approach](https://i.imgur.com/shUJX8d.png)  
It's about finding the minimum cost from the source to the destination.  
Dikstra can do the calculation.

1. Prepare a priority queue and a effort table
    - priority queue: to find the minimum adjacent cost
    - effort table: to record the minimum effort to other cells
2. Finds minimum efforts to other cells using Dijkstra
    - there can be cell duplications in the queue -> skip
        - duplications always have non-minimum value than from effort table
    - push adjacent cells to the queue with the updated minimum value
3. After Dijkstra, return the value of the destination.

