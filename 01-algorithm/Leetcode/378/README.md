## Link
[Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)

## Topic
* Heap (Priority Queue)

## Approach
![approach](https://assets.leetcode.com/users/images/dc1a846a-126c-49cb-b9fa-e7a529d86182_1614142241.31893.png)  
1. Prepare a priority queue and a custom class
    - priority queue: to find the next smallest number
    - custom class: a pair of number and coordination
2. Push the very first number to the queue (0, 0)
3. Pop from the queue, and push two adjacent numbers
    - numbers on the left and the bottom side.
    - they are guarenteed since all the rows and cols are sorted.
4. Stop after popping `k` times.
