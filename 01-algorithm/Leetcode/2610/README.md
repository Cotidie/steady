## 링크
[Convert an Array Into a 2D Array With Conditions](https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/description/)

## 관련 개념
* Recursion

# Approach
- Sort the numbers in ascending order.
- Put numbers one by one into vectors.
  - expand the vector during iteration.
  - clear the points(index, prevNum) if it's not the same number

# Complexity
- Time complexity: O(n logn)