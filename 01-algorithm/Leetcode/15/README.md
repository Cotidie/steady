## Link
[3Sum](https://leetcode.com/problems/3sum/)

## Concepts
* Two Pointers

# Approach
- Prepare a set and three pointers: left, middle, right
    - `left` starts from 0
    - `middle` starts from `left + 1`
    - `right` starts from the end
- Iterate through the array for the `left` pointer
- Find two pointers that sums up to the `left` value
- If two pointers are found, add it to the set
    - `set` is to remove duplicates (try [0, 0, 0, 0])
   
