## Link
[Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

## Concepts
* Binary Search

# Approach
- First, search for the target in the array using binary search
- From there, find the left most index and the right most index each
    -  For the left part, only shrink the search range to the left side
    -  For the right part, only shrink the search range to the right side
- if it reaches to the end or to a different element, its the left/right most index

