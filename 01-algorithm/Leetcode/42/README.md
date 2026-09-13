## Link
[Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/description/)

## Concepts
* Two Pointers

# Approach
![Approach](https://i.imgur.com/N9MBMrj.png)  
- Use two pointers: one from the left, the other from the right.
    - pointers will meet at the common wall
- Move a pointer with smaller value
- Record max values while moving pointers
    - max value is the wall of its side
- If the current value is smaller than the max value of its side, it will trap rain water.
    - `water += max(0, max value - current value)`
- Stop when the two pointers are met.

# Complexity
- Time complexity: O(n)
