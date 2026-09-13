#include <vector>
#include <algorithm>

using namespace std;

class Bucket
{
public:
    void Put(int num)
    {
        if (isNewNumber(num))
            clearForNext();
        if (shouldExpand())
            expandVector();

        putNumber(num);
    }

    vector<vector<int>> &Get()
    {
        return storage;
    }

private:
    bool shouldExpand()
    {
        return storage.size() <= index;
    }

    void expandVector()
    {
        storage.push_back(vector<int>());
    }

    bool isNewNumber(int num)
    {
        return num != prevNum;
    }

    void clearForNext()
    {
        prevNum = -1;
        index = 0;
    }

    void putNumber(int num)
    {
        storage[index].push_back(num);
        prevNum = num;
        index++;
    }

    vector<vector<int>> storage;
    int prevNum = -1;
    int index = 0;
};

class Solution
{
public:
    vector<vector<int>> findMatrix(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        Bucket bucket;

        for (auto &num : nums)
        {
            bucket.Put(num);
        }

        return bucket.Get();
    }

private:
    void tryExpandResult()
    {
        if (result.size() <= index)
            result.push_back(vector<int>());
    }

    vector<vector<int>> result;
    bool isSameNumber = true;
    int prevNumber = -1;
    int index = -1;
};