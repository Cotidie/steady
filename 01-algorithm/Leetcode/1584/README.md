## Link
[Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/description/)  

## Concepts
* Minimum Spanning Tree

## Approach 
If we can construct a MST connecting all the points, then its sum is the minimum cost.

1. Define `Edge` which holds a start point, end point and its manhattan distance.
2. Prepare a priority queue and a disjoint set
    - priority queue: to sort edges by cost in ascending order
    - disjoint set: to detect a cycle for constructing MST
3. Pop from the queue, detect a cycle, and add it to MST
    - A cycle between sub-MST of start point and of end point
4. iterate until the number of edges in MST is (V-1)

## Time Complexity
O(n) where n is the number of edges

