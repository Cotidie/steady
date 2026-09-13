## 링크
[Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/)

## Topic
- Tree
- Recursion

## Approach
![img](https://i.imgur.com/Qtgiiar.png)

Those two are the keys for the approach.
- The first element of pre-order traverse is always the root node.
- The left side and the right side of the root node in in-order traverse is its left sub-tree and its right sub-tree

1. First, set the first element of pre-order as current root node
  - then take it out from the array
2. Find the index of the root node from in-order array. 
  - left side becomes its left sub-tree
  - right side becomes its right sub-tree
4. Repeat 1 & 2  on the left sub-tree and the right sub-tree
  - until no element is left in either pre-ordere array or in-order array

## 비고/남길말
