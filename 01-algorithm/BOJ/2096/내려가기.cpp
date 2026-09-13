#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int rows;
    cin >> rows;

    vector<int> maxScore;
    vector<int> minScore;

    int left, middle, right;
    cin >> left >> middle >> right;
    
    maxScore = {left, middle, right};
    minScore = {left, middle, right};

    for (int r=1; r<rows; r++) {
        cin >> left >> middle >> right;

        int newLeftMax = max(maxScore[0] + left, maxScore[1] + left);
        int newLeftMin = min(minScore[0] + left, minScore[1] + left);

        int newMiddleMax = max(maxScore[0]+middle, maxScore[1]+middle);
        newMiddleMax = max(newMiddleMax, maxScore[2]+middle);
        int newMiddleMin = min(minScore[0]+middle, minScore[1]+middle);
        newMiddleMin = min(newMiddleMin, minScore[2]+middle);

        int newRightMax = max(maxScore[1]+right, maxScore[2]+right);
        int newRightMin = min(minScore[1]+right, minScore[2]+right);

        maxScore[0] = newLeftMax; maxScore[1] = newMiddleMax; maxScore[2] = newRightMax;
        minScore[0] = newLeftMin; minScore[1] = newMiddleMin; minScore[2] = newRightMin;
    }

    cout << *max_element(maxScore.begin(), maxScore.end());
    cout << " ";
    cout << *min_element(minScore.begin(), minScore.end());
    cout << '\n';
}   