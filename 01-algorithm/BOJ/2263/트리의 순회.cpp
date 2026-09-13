#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int id;
    Node *left = nullptr;
    Node *right = nullptr;
};

class TreeMaker {
public:
    TreeMaker(vector<int> inorder, vector<int> postorder) {
        this->inorder = inorder;
        this->postorder = postorder;

        iRoot = postorder.size()-1;
        root = new Node{postorder[iRoot], nullptr, nullptr};
    }

    void construct() {
        int inRoot = findRootIndex(0, inorder.size()-1, root->id);
        iRoot -= 1;
        
        root->right = _construct(inRoot+1, inorder.size()-1);
        root->left = _construct(0, inRoot-1);
    }

    void traverse() {
        _traverse(root);
    }
private:
    void _traverse(Node *node) {
        if (node == nullptr) return;

        cout << node->id << " ";
        _traverse(node->left);
        _traverse(node->right);
    }

    Node* _construct(int iLow, int iHigh) {
        if (iLow > iHigh) return nullptr;
        
        int root = findRootIndex(iLow, iHigh, postorder[iRoot]);
        if (root < 0) return nullptr;

        iRoot -= 1;

        Node *cur = new Node{inorder[root], nullptr, nullptr};
        cur->right = _construct(root+1, iHigh);
        cur->left = _construct(iLow, root-1);

        return cur;
    }

    int findRootIndex(int iLow, int iHigh, int id) {
        for (int i=iLow; i<=iHigh; i++) {
            if (inorder[i] == id) return i;
        }

        return -1;
    }

    vector<int> inorder;
    vector<int> postorder;

    Node* root;
    int iRoot;
};

int main() {
    int length;
    cin >> length;

    vector<int> inorder(length);
    for (int i=0; i<length; i++) {
        cin >> inorder[i];
    }

    vector<int> postorder(length);
    for (int i=0; i<length; i++) {
        cin >> postorder[i];
    }

    TreeMaker tree(inorder, postorder);
    tree.construct();
    tree.traverse();
}