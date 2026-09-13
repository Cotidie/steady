## 링크
[Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)

## Topic
- Binary Search
- Two Pointers

## Approach
(Binary Search)
1. Iterate through the whole array
2. With the second pointer, use binary search for optimization

(Two Pointers)
1. Define two pointers: start and end pointers
2. If the sum of `start` and `end` is:
    - bigger than the target: move `end` pointer to the left
    - smaller than the target: move `start` pointer to the right