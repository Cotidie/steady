#include <iostream>
#include <vector>

using namespace std;

class DP {
public:
    DP(string input): input(input) {
        int len = input.length();
        table = vector<vector<bool>>(len, 
            vector<bool>(len, false)
        );
    }

    void init() {
        int len = table.size();
        for (int i=0; i<len-1; i++) {
            table[i][i] = true;
            table[i][i+1] = (input.at(i) == input.at(i+1));
        }
        table[len-1][len-1] = true;
    }

    void fill() {
        int len = table.size();
        for (int r=len-3; r>=0; r--) {
            for (int c=r+2; c<len; c++) {
                table[r][c] = isPalindrome(r, c);
            }
        }
    }

    int split() {
        vector<int> dp(length(), length()+1);

        for (int end=0; end<length(); end++) {
            if (get(0, end)) {
                dp[end] = 1;
                continue;
            }
            for (int start=1; start<=end; start++) {
                if (!get(start, end)) continue;
                dp[end] = min(dp[end], dp[start-1]+1);
            }
        }

        return dp[length()-1];
    }

    bool get(int i, int j) { return table[i][j]; }
    int length() { return input.length(); }

private:
    bool isPalindrome(int i, int j) {
        if (!table[i+1][j-1]) return false;

        return input.at(i) == input.at(j);
    }

    string input;
    vector<vector<bool>> table;
};

class Backtrack {
public:
    Backtrack(DP &dp): dp(dp) {};

    int split() {
        for (int size=1; size<=dp.length(); size++) {
            bool found = backtrack(0, 1, size);
            if (found) break;
        }

        return count;
    }

private:
    bool backtrack(int i, int depth, int size) {
        if (size == depth) {
            bool isPalindrom = dp.get(i, dp.length()-1);
            if (isPalindrom) count = size;

            return isPalindrom;
        }

        // i~j 사이에 임의의 점을 찍어본다.
        for (int idx=i+1; idx<dp.length(); idx++) {
            if (!dp.get(i, idx-1)) continue;

            bool found = backtrack(idx, depth+1, size);
            if (found) return true;
        }

        return false;
    }

    DP &dp;
    int count = 0;
};

int main() {
    string input;
    cin >> input;

    DP dp(input);
    dp.init();
    dp.fill();

    // Backtrack backtrack(dp);
    // cout << backtrack.split() << '\n';

    cout << dp.split() << '\n';
}