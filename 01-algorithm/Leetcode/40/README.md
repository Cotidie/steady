## Link
[Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)

## Concepts
* Back Tracking
* Hashmap

# Approach
 Usual `for` loop won't do it since it will make duplications. If a `set` is used, still it can't make a combination containing the same elements. 

 Use backtracking on a sorted array, and make sure the same elements are not used in the same level.

1. Sort the given array and prepare a hashmap to ensure uniqueness in each level
2. Iterate each element recursively
    - Don't allow the same numbers in the same level
    - Ensure visiting the numbers in ascending order by depth
3. If the sum meets `target`, save the combination and exit
4. Return the combinations after all the iterations.

