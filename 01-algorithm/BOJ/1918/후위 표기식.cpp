#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class Converter {
public:
    Converter() {};

    string convert(string exp) {
        stck = stack<string>();
        string result = "";

        bool clearNext = false;
        for (int i=0; i<exp.length(); i++) {
            string ch = string(1, exp.at(i));

            if (ch == "(") {
                stck.push(ch);
                continue;
            }

            if (ch == ")") {
                result += clearParenthesis();
                continue;
            }

            if (!isOperator(ch)) {
                result += ch;
                continue;
            }

            if (stck.empty()) {
                stck.push(ch);
                continue;
            }

            if (priority[ch] <= priority[stck.top()]) result += clearStack(priority[ch]);
            stck.push(ch);
        }

        if (!stck.empty()) result += clearStack(0);
    
        return result;
    }

private:
    bool isOperator(string ch) {
        return priority.find(ch) != priority.end();
    }

    string clearParenthesis() {
        string result = "";

        string ch = "";
        while (ch = stck.top(), stck.pop(), ch != "(") {
            result += ch;
        }

        return result;
    }

    string clearStack(int uBound) {
        string result = "";

        while (!stck.empty()) {
            if (stck.top() == "(") return result;
            if (priority[stck.top()] < uBound) return result;
            result += stck.top();
            stck.pop();
        }

        return result;
    }

    map<string, int> priority = {
        {"+", 0}, {"-", 0},
        {"*", 1}, {"/", 1}
    };

    stack<string> stck;
};

int main() {
    string exp;
    cin >> exp;

    Converter c;

    cout << c.convert(exp) << '\n';
}