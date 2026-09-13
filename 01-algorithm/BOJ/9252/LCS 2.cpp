#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string A, B;
    cin >> A >> B;

    auto dp = vector<vector<int>>(
        A.length()+1, vector<int>(
            B.length()+1, 0
        )
    );
    auto chars = vector<vector<char>>(
        A.length()+1, vector<char>(
            B.length()+1, ' '
        )
    );

    for (int r=1; r<=A.length(); r++) {
        for (int c=1; c<=B.length(); c++) {
            if (A.at(r-1) == B.at(c-1)) {
                dp[r][c] = dp[r-1][c-1]+1;
                chars[r][c] = A.at(r-1);
                continue;
            }

            if (dp[r][c-1] > dp[r-1][c]) {
                dp[r][c] = dp[r][c-1];
                chars[r][c] = chars[r][c-1];
            } else {
                dp[r][c] = dp[r-1][c];
                chars[r][c] = chars[r-1][c];
            }
        }
    }

    cout << dp[A.length()][B.length()] << '\n';
    
    vector<char> result;

    int r=A.length(), c=B.length();
    int prev = dp[r][c];
    while (r>0 && c>0) {
        if (A.at(r-1) == B.at(c-1)) {
            result.push_back(A.at(r-1));
            r--; c--;
            continue;
        }

        if (dp[r][c-1] > dp[r-1][c]) c--;
        else r--;
    }

    for (int i=result.size()-1; i>=0; i--) {
        cout << result[i];
    }
}