## Link
[Partition Labels](https://leetcode.com/problems/partition-labels/)

## Topic
* Greedy

## Approach
0. Prepare three `int` variables 
   - size: counted size of the current partition
   - cur: the current iterating index
   - end: the end index of current partition
1. Iterate the string from the start
2. Find the last position of the current character
    - This is the minimum partition 
    - Update the `end` variable
3. if `cur` meets `end` position, it means a partition is detected.

## Time Complexity
O(n^)