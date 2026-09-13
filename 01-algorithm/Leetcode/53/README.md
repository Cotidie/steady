## Link
[Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/description/)

## Concepts
* Dynamic Programming
* Greedy Algorithm
    ! **Greedy** keeps an optimal value throughout the iteration

# Approach
![approach](https://i.imgur.com/2d4xsuI.png)  
- Iterate from the start of the array to the end
- Adds the current number to `sum`
- Once the `sum` goes below zero, reset `sum` to 0

# Complexity
- Time complexity: O(n)
