#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    string str, bomb;
    cin >> str >> bomb;

    if (str.length() < bomb.length()) {
        cout << str << '\n';
        return 0;
    }

    stack<char> stck;
    vector<char> compare(bomb.length());

    char lastChar = bomb.at(bomb.length()-1);
    for (int i=0; i<str.length(); i++) {
        stck.push(str.at(i));

        if (stck.size() >= bomb.length() && str.at(i) == lastChar) {
            for (int j=bomb.length()-1; j>=0; j--) {
                compare[j] = stck.top();
                stck.pop();
            }

            if (string(compare.begin(), compare.end()) != bomb) {
                for (char ch : compare) stck.push(ch);
            }
        }
    }

    if (stck.size() == 0) cout << "FRULA" << '\n';
    else {
        vector<char> result(stck.size());
        for (int j=stck.size()-1; j>=0; j--) {
            result[j] = stck.top();
            stck.pop();
        }

        cout << string(result.begin(), result.end()) << '\n';
    }
}