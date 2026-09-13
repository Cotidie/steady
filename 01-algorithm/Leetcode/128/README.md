## 링크
[Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)

## Topic
- Union Find

## Approach
1. Build a hashmap and a disjoint set
    - hashmap: to check its existence
    - disjoint set: to merge consequtive numbers
2. Iterate the array and check if the left(-1) value exists
3. If exists, union two numbers
    - memorize the biggest size
4. return the biggest size
   
## Note
