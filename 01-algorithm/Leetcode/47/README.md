## Link
[Permutations II](https://leetcode.com/problems/permutations-ii/)

## Concepts
* Back Tracking

# Approach
1. Prepare two arrays and a set.
    - `used`: an array to mark whether it's already used
    - `permutation`: an array to build a permutation along recursion
    - `permutations`: a set to remove duplications 
2. Loop through the given array recursively
    - add unused numbers to the `permutation` array
    - mark used numbers in `used` array
3. If the length of `permutation` reaches to the desired size, exit
    - put the `permutation` set to `permutations` set
4. After all the recursions, return `permutations` set
