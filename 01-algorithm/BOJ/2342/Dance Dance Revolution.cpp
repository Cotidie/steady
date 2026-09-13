#include <iostream>
#include <vector>

using namespace std;

const int INTMAX = 10000000;

int getCost(int from, int to) {
    if (from == 0 || to == 0) return 2;
    if (abs(from-to) == 2) return 4;
    if (from == to) return 1;

    return 3; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> inputs;
    int input;
    while (cin >> input, input != 0) {
        inputs.push_back(input);
    }

    int size = inputs.size();

    vector<vector<vector<int>>> memo = vector<vector<vector<int>>>(
        size+1, vector<vector<int>>(
            5, vector<int>(
                5, INTMAX
            )
        )
    );
    memo[0][0][0] = 0;

    for (int i=1; i<=size; i++) {
        int input = inputs[i-1];
        for (int left=0; left<5; left++) {
            for (int right=0; right<5; right++) {
                // 왼쪽 발을 left -> input으로 옮긴다.
                memo[i][input][right] = min(
                    memo[i][input][right], 
                    memo[i-1][left][right] + getCost(left, input)
                );

                // 오른쪽 발을 right -> input으로 옮긴다. 
                memo[i][left][input] = min(
                    memo[i][left][input],
                    memo[i-1][left][right] + getCost(right, input)
                );
            }
        }
    }

    int minCost = 10000000;
    for (int left=0; left<5; left++) {
        for (int right=0; right<5; right++) {
            minCost = min(minCost, memo[size][left][right]);
        }
    }

    cout << minCost << '\n';
}