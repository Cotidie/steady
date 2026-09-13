#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Constructor {
public:
    Constructor(vector<int>& preorder, vector<int>& inorder):preorder(preorder), inorder(inorder) {};

    void Construct(TreeNode* head) {
        construct(head, 0, inorder.size()-1);
    }

private:
    bool construct(TreeNode* node, int lIn, int uIn) {
        if (lIn > uIn) return false;
        if (lIn == uIn) {
            node->val = getRootValue();
            return true;
        }
        
        int valRoot = getRootValue();
        int idxRoot = findInorderIndex(valRoot, lIn, uIn);

        node->val = valRoot;
        node->left = new TreeNode();
        node->right = new TreeNode();

        bool isLeftExist = construct(node->left, lIn, idxRoot-1);
        bool isRightExist = construct(node->right, idxRoot+1, uIn);

        if (!isLeftExist) node->left = nullptr;
        if (!isRightExist) node->right = nullptr;

        return true;                      
    }

    int findInorderIndex(int val, int low, int high) {
        for (int i=low; i<=high; i++) {
            if (inorder[i] == val) return i;
        }

        return -1;
    }

    int getRootValue() {
        return preorder[idxPreorder++];
    }

    vector<int>& preorder;
    vector<int>& inorder;
    int idxPreorder = 0;
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        Constructor constructor = Constructor(preorder, inorder);
        TreeNode* head = new TreeNode();

        constructor.Construct(head);

        return head;
    }
};
