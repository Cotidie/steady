#include <vector>
#include <queue>
#include <set>

using namespace std;

class Summation
{
public:
    Summation(int sum, int idx1, int idx2) : index1(idx1), index2(idx2), sum(sum){};

    bool operator<(const Summation &obj) const
    {
        return index1 < obj.index1 || (index1 == obj.index1 && index2 < obj.index2);
    }

    int index1, index2;
    int sum;
};

class Compare
{
public:
    bool operator()(Summation &a, Summation &b)
    {
        return a.sum > b.sum;
    }
};

class MinHeap
{
public:
    MinHeap(vector<int> &nums1, vector<int> &nums2) : nums1(nums1), nums2(nums2)
    {
        Push(0, 0);
    };

    void Push(int idx1, int idx2)
    {
        int s = nums1[idx1] + nums2[idx2];
        Summation sum = Summation(s, idx1, idx2);

        if (exists(sum))
        {
            return;
        }

        heap.push(sum);
        set.insert(sum);
    }

    Summation Pop()
    {
        Summation res = heap.top();
        heap.pop();

        return res;
    }

    bool Empty()
    {
        return heap.empty();
    }

    void TestPush(Summation &s)
    {
        heap.push(s);
    }

private:
    bool exists(Summation &sum)
    {
        return set.find(sum) != set.end();
    }

    priority_queue<Summation, vector<Summation>, Compare> heap;
    set<Summation> set;
    vector<int> nums1, nums2;
};

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        vector<vector<int>> result;
        MinHeap heap = MinHeap(nums1, nums2);

        for (int i = 0; i < k; i++)
        {
            if (heap.Empty())
            {
                break;
            }

            Summation s = heap.Pop();
            vector<int> res = vector<int>{nums1[s.index1], nums2[s.index2]};
            result.push_back(res);

            if (s.index1 + 1 < nums1.size())
            {
                heap.Push(s.index1 + 1, s.index2);
            }
            if (s.index2 + 1 < nums2.size())
            {
                heap.Push(s.index1, s.index2 + 1);
            }
        }

        return result;
    }
};