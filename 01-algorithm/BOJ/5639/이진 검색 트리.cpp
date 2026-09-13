#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node *left, *right;
};

class Tree {
public:
    Tree(vector<int>& preorder): preorder(preorder) {};

    void construct() {
        root = recurse(0, preorder.size()-1);
    }

    void printPostorder() {
        postTraverse(root);
    }

private:
    Node* recurse(int left, int right) {
        if (left > right) return nullptr;
        if (left == right) return new Node{preorder[left]};
        
        int rightRoot = findRightRoot(left, right);

        Node *child = new Node{preorder[left]};
        if (rightRoot == -1) {
            child->left = recurse(left+1, right);
        } else {
            child->left = recurse(left+1, rightRoot-1);
            child->right = recurse(rightRoot, right);
        }

        return child;
    }

    int findRightRoot(int left, int right) {
        int root = preorder[left];

        for (int i=left+1; i<=right; i++) {
            if (preorder[i] > root) return i;
        }

        return -1;
    }

    void postTraverse(Node *root) {
        if (root == nullptr) return;

        postTraverse(root->left);
        postTraverse(root->right);
        cout << root->val << '\n';
    }

    vector<int>& preorder;
    Node *root;
};

int main() {
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

    vector<int> nums;
    
    int num;
    while (cin >> num) {
        nums.push_back(num);    
    }

    Tree tree(nums);

    tree.construct();

    tree.printPostorder();
}