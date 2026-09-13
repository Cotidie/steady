## Link
[Time Needed to Inform All Employees](https://leetcode.com/problems/time-needed-to-inform-all-employees/description/)

## Concepts
* Tree
* Recursion

## Approach
![approach](https://i.imgur.com/ZTSH5Oh.png)  
1. Prepare a n-ary tree node
2. Construct a tree using the managers array
3. Traverse the tree left to right, returning inform times of each.
4. Compare which subordinate has the longest inform time.
5. Sum up the longest inform times when going up to the root.

