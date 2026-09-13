#include <limits.h>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Validator
{
public:
    Validator(TreeNode *head) : head(head){};

    bool Validate()
    {
        return isBST(head, LLONG_MIN, LLONG_MAX);
    }

private:
    bool isBST(TreeNode *node, long long int lbound, long long int ubound)
    {
        if (node == nullptr)
            return true;
        if (node->val <= lbound)
            return false;
        if (node->val >= ubound)
            return false;
        if (!isPartialBST(node))
            return false;

        int newUpperBound = ubound;
        int newLowerBound = lbound;
        if (node->val < ubound)
            newUpperBound = node->val;
        if (node->val > lbound)
            newLowerBound = node->val;

        bool isLeftOK = isBST(node->left, lbound, newUpperBound);
        bool isRightOK = isBST(node->right, newLowerBound, ubound);

        return isLeftOK && isRightOK;
    }

    bool isPartialBST(TreeNode *node)
    {
        return isLeftLesser(node) && isRightGreater(node);
    }

    bool isLeftLesser(TreeNode *node)
    {
        if (node->left == nullptr)
            return true;

        return node->left->val < node->val;
    }

    bool isRightGreater(TreeNode *node)
    {
        if (node->right == nullptr)
            return true;

        return node->right->val > node->val;
    }

    TreeNode *head;
};

class Solution
{
public:
    bool isValidBST(TreeNode *node)
    {
        Validator validator = Validator(node);

        return validator.Validate();
    }
};