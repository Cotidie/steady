## Link
[Network Delay Time](https://leetcode.com/problems/network-delay-time/description/)

## Topic
* Dijkstra

## Approach
1. Examine the smallest costs to each nodes using Dijkstra
2. The biggest cost among the smallest costs is the minimum Network Delay Time.
   - Because it has to visit all the nodes
   - if there's INFINITE cost then it's not possible to deliver to all the nodes.
   