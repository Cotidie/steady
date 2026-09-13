#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> result;

        int size = 1;
        size_t cur = 0;
        size_t end = 0;
        while (cur < s.length()) {
            end = max(
                end, 
                s.find_last_of(s.at(cur))
            );

            if (cur == end) {
                result.push_back(size);
                size = 0;
            }

            cur++; size++;
        }

        return result;
    }
};

int main() {
    Solution s;
    string input;

    // 9, 7, 8
    input = "ababcbacadefegdehijhklij";
    for (int size : s.partitionLabels(input)) cout << size << " ";
    cout << endl;

    // 10
    input = "eccbbbbdec";
    for (int size : s.partitionLabels(input)) cout << size << " ";
    cout << endl;
}
