#include <vector>
#include <queue>

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

struct NodeLevel
{
    TreeNode *node;
    int level;
};

class RightViewer
{
public:
    RightViewer(TreeNode *head) : head(head){};

    vector<int> GetRightView()
    {
        NodeLevel rootNode = {head, 0};
        q.push(rootNode);

        traverseByLevel();

        return result;
    }

private:
    void traverseByLevel()
    {
        if (q.empty())
            return;

        NodeLevel info = q.front();
        q.pop();
        if (info.node == nullptr)
            return;

        updateView(info.node, info.level);

        putLeft(info.node, info.level + 1);
        putRight(info.node, info.level + 1);

        traverseByLevel();
    }

    void putLeft(TreeNode *node, int level)
    {
        if (node->left == nullptr)
            return;

        NodeLevel nodeAndLevel = {node->left, level};
        q.push(nodeAndLevel);
    }

    void putRight(TreeNode *node, int level)
    {
        if (node->right == nullptr)
            return;

        NodeLevel nodeAndLevel = {node->right, level};
        q.push(nodeAndLevel);
    }

    void updateView(TreeNode *node, int level)
    {
        if (isVectorSmall(level))
        {
            result.push_back(node->val);
        }
        else
        {
            result[level] = node->val;
        }
    }

    bool isVectorSmall(int level)
    {
        return result.size() <= level;
    }

    TreeNode *head;
    vector<int> result;
    queue<NodeLevel> q;
};

class Solution
{
public:
    vector<int> rightSideView(TreeNode *root)
    {
        RightViewer viewer = RightViewer(root);

        return viewer.GetRightView();
    }
};