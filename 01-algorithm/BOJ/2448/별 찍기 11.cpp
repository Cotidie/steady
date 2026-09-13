#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

vector<string> stars;
vector<long> K(11);

void printStars(vector<string> &stars, int depth, int limit) {
    if (depth > limit) {
        for (string star : stars) cout << star << '\n';
        return; 
    }
    int sizeBefore = stars.size();

    for (int i=0; i<sizeBefore; i++) {
        string newStars = stars[i] + " " + stars[i];
        stars.push_back(newStars);
    }

    string spaces = string(K[depth-1], ' ');
    for (int i=0; i<sizeBefore; i++) {
        stars[i] = spaces + stars[i] + spaces;
    }

    printStars(stars, depth+1, limit);
}

void fillK() {
    for (int k=0; k<=10; k++) {
        long num = 3 * pow(2, k);
        K[k] = num;
    }
}

int findK(long num) {
    for (int k=0; k<11; k++) {
        if (num == K[k]) return k;
    }
    
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long num;
    cin >> num;

    fillK();

    vector<string> stars = {
        "  *  ",
        " * * ",
        "*****"
    };

    printStars(stars, 1, findK(num));
}