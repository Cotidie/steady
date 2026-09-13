## Link
[Path with Maximum Probability](https://leetcode.com/problems/path-with-maximum-probability/description/)

## Concepts
* Dijkstra

## Approach 
Dijkstra will calculate the most optimal path to the destination.

1. Prepare a priority queue and two arrays
    - priority queue: to find the maximum adjacent probability
    - `done` array: to mark nodes which are confirmed as optimal
    - `maxProb` array: to store max probability for each node
2. Finds maximum prob. to other nodes using Dijkstra
    - there can be cell duplications in the queue -> skip
        - duplications can be checked with `done` array
    - push adjacent nodes to the queue with the updated prob. value
3. After Dijkstra, return the value of the destination.

