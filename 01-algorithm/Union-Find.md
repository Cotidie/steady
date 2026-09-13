# Disjoint Set

## Overview
![union-find](https://miro.medium.com/v2/resize:fit:1200/1*IZAScQTp3yRh4J6Kt6VmGg.png)  
Union-Find is another name of a data structure `disjoint set`, which has `union()` and `find()` methods to **detect a cycle** between two sets/trees. A cycle can be detected by checking whether two sets/trees have the same root. 
  - union-find can also handle a problem where it needs propagation of status change
  - union-find can't get the length of a cycle (=> DFS of BFS)

## Implementation
Either linked list or array can be used for implementation. Note that when merging, parent should be the one whose size/rank is bigger to avoid unbalanced tree. It optimizes `find()` operation by reducing the number of travel. 

### Steps
Prepare an array that records each node's parent.
    - minus value indicates the root node.
    - the root's absolute value indicates the set's size.

  - `find()`: Find which set an element `k` belongs => find root.
  - `union()`: Merge two disjoint sets/trees => connect to one's root.
    1. find the root of each node
    2. if roots are the same, abort
    3. update the root of the node which has smaller size (merge to the bigger one)
    4. update the size of the parent node


### Array
```cpp
void Find(vector<int>& parent, int i) {
    if (parent[i] < 0) return i;
    
    int result = find(parent[i]);
    
    parent[i] = result;

    return result;
} 

void Union(vector<int>& parent, int i, int j) {
    int iRoot = find(parent, i);
    int jRoot = find(parent, j);

    if (iRoot == jRoot) return;

    int iSize = -1 * parent[iRoot];
    int jSize = -1 * parent[jRoot];

    if (iSize > jSize) {
        parent[j] = iRoot;
        parent[iRoot] -= jSize;
    } else {
        parent[i] = jRoot;
        parent[jRoot] -= iSize;
    }
}
```

### Linked List
```cpp
class Node {
public:
    Node* parent;
    int val;
    int size;
};

class DisjointSet {
public:
    Node& Find(int val) {
        Node& node = set[val];

        if (node.next == nullptr) {
            return node;
        }

        Node& rootNode = Find(node.parent->val);
        node.parent = &rootNode;

        return rootNode;
    }

    bool Union(int a, int b) {
        Node& aRoot = Find(a);
        Node& bRoot = Find(b);

        if (aRoot.val == bRoot.val) return false;

        if (aRoot.size > bRoot.size) {
            bRoot.parent = &aRoot;
            aRoot.size += bRoot.size;
        } else {
            aRoot.parent = &bRoot;
            bRoot.size += aRoot.size;
        }

        return true;
    }

private:
    map<int, Node> set;
}
```
