## Link
[Container With Most Water](https://leetcode.com/problems/container-with-most-water/description/)

## Concepts
* Two Pointers

# Approach
- Use two pointers: one from the left, the other from the right.
    - `area = min(A, B) * (pB-pA)`
    - We don't need to do brute-force by moving A or B just one step
- Move the pointer with the smaller value.

Q. How does the area at the point (pA, pB) garanttee the maximum value at the width of `(pB-pA)`?
# Complexity
- Time complexity: O(n)
