using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Reverser
{
public:
    Reverser(ListNode *head) : head(head) {}

    void Reverse(int left, int right)
    {
        nodeLeft = findNode(left);

        this->idxMid = (left + right) / 2;
        reverse(1, right, this->head);
    }

private:
    void reverse(int current, int right, ListNode *nodeRight)
    {
        if (current > right)
            return;

        reverse(current + 1, right, nodeRight->next);

        if (current <= idxMid)
            return;

        swap(nodeLeft, nodeRight);
        this->nodeLeft = nodeLeft->next;
    }

    ListNode *findNode(int index)
    {
        ListNode *target = head;

        for (int i = 1; i < index; i++)
        {
            target = target->next;
        }

        return target;
    }

    void swap(ListNode *left, ListNode *right)
    {
        int val = left->val;

        left->val = right->val;
        right->val = val;
    }

    ListNode *head = nullptr;
    ListNode *nodeLeft = nullptr;
    int idxMid = 0;
};

class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        Reverser reverser = Reverser(head);

        reverser.Reverse(left, right);

        return head;
    }
};