#include <vector>
#include <string>
#include <stack>

using namespace std;

vector<string> Split(string s, string delim) {
    vector<string> result;
    string token;
    int pos = s.find(delim);
    
    while (pos != string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos+delim.length());
        pos = s.find(delim);
    }

    result.push_back(s);
    return result;
}

class Explorer {
public:
    Explorer() {};

    void GoParent() {
        if (explorer.size() != 0) explorer.pop();
    }

    void Go(string name) {
        if (name == "..") GoParent();
        else if (name == ".") return;
        else if (name == "") return;
        else explorer.push(name);
    }

    string GetPath() {
        string path = "";

        while (!explorer.empty()) {
            path = "/" + explorer.top() + path;
            explorer.pop();
        }

        return (path == "") ? "/" : path; 
    }

private:
    stack<string> explorer;
};

class Solution {
public:
    string simplifyPath(string path) {
        Explorer explorer;

        vector<string> tokens = Split(path, "/");

        for (string token : tokens) {
            explorer.Go(token);
        }

        return explorer.GetPath();
    }
};