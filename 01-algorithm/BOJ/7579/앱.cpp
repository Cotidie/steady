#include <iostream>
#include <vector>

using namespace std;

struct App {
    long memory = 0;
    int cost = 0;
};

class Collector {
public:
    Collector(int size) {
        apps = vector<App>(size);
    }

    void setMemory(int app, int mem) {
        apps[app].memory = mem;
    }

    void setCost(int app, int cost) {
        apps[app].cost = cost;
        totalCost += cost;
    }

    int getMinimumCost(long target) {
        auto dp = vector<vector<long>>(apps.size()+1, vector<long>(totalCost+1, 0));

        for (int r=1; r<=apps.size(); r++) {
            int curCost = apps[r-1].cost;
            long curMem = apps[r-1].memory;

            for (int c=0; c<=totalCost; c++) {
                if (curCost > c) {
                    dp[r][c] = dp[r-1][c];
                    continue;
                }

                dp[r][c] = max(
                    dp[r-1][c], 
                    dp[r-1][c-curCost] + curMem   
                );
            }
        }

        int minCost = 0;
        for (int c=0; c<=totalCost; c++) {
            if (dp[apps.size()][c] >= target) {
                minCost = c;
                break;
            }
        }

        return minCost;
    }
private:
    vector<App> apps;
    int totalCost = 0;
};

int main() {
    int apps, target;
    cin >> apps >> target;

    Collector collector(apps);
    for (int i=0; i<apps; i++) {
        long mem;
        cin >> mem;

        collector.setMemory(i, mem);
    }

    for (int i=0; i<apps; i++) {
        int cost;
        cin >> cost;
        collector.setCost(i, cost);
    }

    cout << collector.getMinimumCost(target) << '\n';
}