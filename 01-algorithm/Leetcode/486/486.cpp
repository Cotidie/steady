#include <vector>

using namespace std;

class Solution
{
public:
    bool PredictTheWinner(vector<int> &nums)
    {
        init(nums);

        // Loop through diagonally.
        for (int i = 0; i < nums.size(); i++)
        {
            int lastIdx = nums.size() - i;
            for (int j = 0; j < lastIdx; j++)
            {
                int row = j;
                int col = row + i + 1;

                int partialSum = getSum(row, col);
                int chooseFirst = partialSum - dp[row + 1][col];
                int chooseLast = partialSum - dp[row][col - 1];

                dp[row][col] = max(chooseFirst, chooseLast);
            }
        }

        int scorePlayer1 = dp[0][nums.size()];
        int scorePlayer2 = getSum(0, nums.size()) - scorePlayer1;
        return scorePlayer1 >= scorePlayer2;
    }

private:
    void init(vector<int> &nums)
    {
        dp = vector(nums.size() + 1, vector(nums.size() + 1, 0));
        summation.push_back(0);

        int sum = 0;
        for (int num : nums)
        {
            sum += num;
            summation.push_back(sum);
        }
    }

    int getSum(int row, int col)
    {
        return summation[col] - summation[row];
    }

    vector<vector<int>> dp;
    vector<int> summation;
};