## 링크
[Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/description/)

## 관련 개념
* Heap

# Approach
- Create a min-heap to store sum and indices of two arrays.
- Insert the Sumaation (sum, idx1+1, idx2) and (sum, idx1, idx2+1) to the min-heap.
- Pop from the min-heap k times.

# Complexity
- Time complexity: O(n logn)