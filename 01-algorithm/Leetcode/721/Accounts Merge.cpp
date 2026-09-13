#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

class DisjointSet {
public:
    DisjointSet(int size) {
        parents = vector<int>(size, -1);
    }

    int Find(int val) {
        if (parents[val] < 0) return val;

        int root = Find(parents[val]);
        parents[val] = root;

        return root;
    }

    bool Union(int a, int b) {
        int aRoot = Find(a);
        int bRoot = Find(b);

        if (aRoot == bRoot) return false;

        int aSize = -1 * parents[aRoot];
        int bSize = -1 * parents[bRoot];

        if (aSize > bSize) {
            parents[bRoot] = aRoot;
            parents[aRoot] -= bSize;
        } else {
            parents[aRoot] = bRoot;
            parents[bRoot] -= aSize;
        }

        return true;
    }

private:
    vector<int> parents;
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        map<string, int> owners;
        DisjointSet disjoint(accounts.size());

        for (int i=0; i<accounts.size(); i++) {
            for (int j=1; j<accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (owners.find(email) == owners.end()) owners[email] = i;
                
                disjoint.Union(owners[email], i);
            }
        }

        map<int, vector<string>> process;
        for (auto elem : owners) {
            string email = elem.first;
            int rootID = disjoint.Find(elem.second);

            process[rootID].push_back(email);
        }

        vector<vector<string>> result;
        for (auto elem : process) {
            string name = accounts[elem.first][0];
            vector<string>& emails = elem.second;
            // sort(emails.begin(), emails.end());

            vector<string> account(emails.size()+1);
            account[0] = name;
            for (int i=1; i<account.size(); i++) {
                account[i] = emails[i-1];
            }

            result.push_back(account);
        }

        return result;
    }
};

int main() {
    Solution s;
    vector<vector<string>> accounts;

    /*
    [
        ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
        ["Mary","mary@mail.com"],
        ["John","johnnybravo@mail.com"],
    ]
    */
    accounts = {{"John","johnsmith@mail.com","john_newyork@mail.com"},{"John","johnsmith@mail.com","john00@mail.com"},{"Mary","mary@mail.com"},{"John","johnnybravo@mail.com"}};
    for (auto emails : s.accountsMerge(accounts)) {
        for (auto email : emails) cout << email << ", ";
        cout << endl;
    }
}