// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Weight {
    char ch;
    int weight=0;
};

class Descending {
public:
    bool operator()(const Weight &a, const Weight &b) {
        return a.weight > b.weight;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<string> words(n);
    for (int i=0; i<n; i++) {
        cin >> words[i];
    }

    vector<Weight> weights(26);
    for (int c=0; c<26; c++) {
        char ch = c+'A';
        weights[c] = {ch, 0};
    }

    for (string word : words) {
        for (int i=0; i<word.length(); i++) {
            int power = pow(10, word.length()-1-i);
            weights[word.at(i)-'A'].weight += power;
        }
    }

    sort(weights.begin(), weights.end(), Descending());

    long sum = 0;
    int num = 9;

    for (int i=0; i<9; i++) {
        sum += weights[i].weight * num;
        num--;
    }

    cout << sum << '\n';
}
