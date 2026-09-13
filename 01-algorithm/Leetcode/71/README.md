## 링크
[Simplify Path](https://leetcode.com/problems/simplify-path/)

## Concepts
* Stack

# Approach
- Split file/directory names by `/`
- Put splitted names into a stack
    - if it's `.` or empty, do nothing
    - if it's `..`, pop from the stack
- Concatenate names from the stack

# Complexity
- Time complexity: O(n)
