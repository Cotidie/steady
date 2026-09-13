#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        this->dp = vector(text1.length() + 1, vector(text2.length() + 1, 0));
        this->text1 = text1;
        this->text2 = text2;

        int lastText1 = text1.length() - 1;
        int lastText2 = text2.length() - 1;

        for (int idx1 = lastText1; idx1 >= 0; idx1--)
        {
            for (int idx2 = lastText2; idx2 >= 0; idx2--)
            {
                dp[idx1][idx2] = solveSubproblem(idx1, idx2);
            }
        }
        return dp[0][0];
    }

private:
    bool isSameChar(int idx1, int idx2)
    {
        return text1[idx1] == text2[idx2];
    }

    int solveSubproblem(int idx1, int idx2)
    {
        if (isSameChar(idx1, idx2))
        {
            return 1 + dp[idx1 + 1][idx2 + 1];
        }

        return max(dp[idx1 + 1][idx2], dp[idx1][idx2 + 1]);
    }

    vector<vector<int>> dp;
    string text1, text2;
};