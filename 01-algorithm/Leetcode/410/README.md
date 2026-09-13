## Link
[Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

## Topic
* Binary Search (Parametric)

## Approach
Get the target value to check if you can split into subarray under the sum of the target, then count it. If you can make less or equal to `m` subarrays, reduce the target value and keep searching.

1. Find a minimum sum and a maximum sum from the array
    - **minimum**: the biggest number 
    - **maximum**: the sum of the array
2. Take the minimum as lower bound, and the maximum as upper bound
3. Take the mid target and check if the array can split into `m` subarrays under the mid target
    - If it can, update the max value to `mid-1` 
    - If it can't, update the min value to `mid+1`
4. Iterate until `min` goes over `max`
    - This is when the very next value is the minimum since the current max is updated from `mid-1`

