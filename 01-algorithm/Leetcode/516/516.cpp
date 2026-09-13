#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        init(s);

        int lastIdx = s.length() - 1;
        for (int idx1 = lastIdx; idx1 >= 0; idx1--)
        {
            for (int idx2 = lastIdx; idx2 >= 0; idx2--)
            {
                dp[idx1][idx2] = solveProblem(idx1, idx2);
            }
        }

        return dp[0][0];
    }

private:
    void init(string s)
    {
        dp = vector(s.length() + 1, vector(s.length() + 1, 0));
        original = s;
        reversed = s;
        reverse(reversed.begin(), reversed.end());
    }

    bool isSameChar(int &idx1, int &idx2)
    {
        return original[idx1] == reversed[idx2];
    }

    int solveProblem(int &idx1, int &idx2)
    {
        if (isSameChar(idx1, idx2))
        {
            return 1 + dp[idx1 + 1][idx2 + 1];
        }

        return max(dp[idx1 + 1][idx2], dp[idx1][idx2 + 1]);
    }

    vector<vector<int>> dp;
    string original, reversed;
};