#include <limits.h>
#include <map>

using namespace std;

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
        return isBST(this->head);
    }

private:
    bool isBST(TreeNode *node)
    {
        if (node == nullptr)
        {
            return true;
        }
        if (isLeafNode(node))
        {
            return true;
        }

        bool isLeftGood = isBST(node->left);
        bool isRightGood = isBST(node->right);

        if (!isLeftGood || !isRightGood)
        {
            return false;
        }

        bool lessLeft = isLeftLess(node);
        bool greaterRight = isRightGreater(node);

        if ((!lessLeft) || (!greaterRight))
        {
            return false;
        }

        int leftMax = getMax(node->left);
        int rightMin = getMin(node->right);

        if (!isLeftEmpty(node) && leftMax >= node->val)
            return false;
        if (!isRightEmpty(node) && rightMin <= node->val)
            return false;

        return true;
    }

    int getMax(TreeNode *node)
    {
        if (node == nullptr)
            return INT_MIN;

        if (memoMax.find(node) != memoMax.end())
        {
            return memoMax[node];
        }

        if (isRightEmpty(node))
        {
            memoMax[node] = node->val;
            return node->val;
        }

        int rightMax = getMax(node->right);
        int leftMax = getMax(node->left);
        if (rightMax > leftMax)
        {
            memoMax[node] = rightMax;
        }
        else
        {
            memoMax[node] = leftMax;
        }

        return memoMax[node];
    }

    int getMin(TreeNode *node)
    {
        if (node == nullptr)
            return INT_MAX;

        if (memoMin.find(node) != memoMin.end())
        {
            return memoMin[node];
        }

        if (isLeftEmpty(node))
        {
            memoMin[node] = node->val;
            return node->val;
        }

        int leftMin = getMin(node->left);
        int rightMin = getMin(node->right);
        if (rightMin < leftMin)
        {
            memoMin[node] = rightMin;
        }
        else
        {
            memoMin[node] = leftMin;
        }

        return memoMin[node];
    }

    bool isLeftLess(TreeNode *node)
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

    bool isLeftEmpty(TreeNode *node)
    {
        return node->left == nullptr;
    }

    bool isRightEmpty(TreeNode *node)
    {
        return node->right == nullptr;
    }

    bool isLeafNode(TreeNode *node)
    {
        return node->left == nullptr && node->right == nullptr;
    }

    TreeNode *head;
    map<TreeNode *, int> memoMin;
    map<TreeNode *, int> memoMax;
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