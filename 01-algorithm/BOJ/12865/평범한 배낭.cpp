#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

class Ascending {
public:
    bool operator()(const Item &left, const Item &right) {
        return left.weight < right.weight;
    }
};

int main() {
    int N, W;
    cin >> N >> W;

    auto items = vector<Item>(N+1);
    items[0] = Item{0, 0};

    for (int i=1; i<=N; i++) {
        int weight, value;
        cin >> weight >> value;

        items[i] = Item{weight, value};
    }
    sort(items.begin(), items.end(), Ascending());

    auto dp = vector<vector<int>>(N+1, vector<int>(W+1, 0));

    for (int r=1; r<=N; r++) {
        for (int c=1; c<=W; c++) {
            Item &item = items[r];
            // 현재 물건의 무게 이전까지는 그대로 따른다.
            if (c < item.weight) {
                dp[r][c] = dp[r-1][c];
                continue;
            }

            // 물건을 선택하는 경우, 하지 않는 경우를 고려한다.
            dp[r][c] = max(
                item.value + dp[r-1][c-item.weight],
                dp[r-1][c]
            );
        }
    }

    cout << dp[N][W] << '\n';
}