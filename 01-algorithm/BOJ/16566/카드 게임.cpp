#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Disjoint {
public:
    Disjoint() {};
    Disjoint(int size) {
        parents = vector<int>(size+1, -1);
    }

    int find(int n) {
        if (parents[n] < 0) return n;

        int root = find(parents[n]);
        parents[n] = root;

        return root;
    }

    bool unite(int a, int b) {
        int aRoot = find(a);
        int bRoot = find(b);

        if (aRoot == bRoot) return true;

        parents[aRoot] = bRoot;

        return false;
    }
private:
    vector<int> parents;
};

class Deck {
public:
    Deck(int size): max(size) {
        cards = vector<int>();
        cards.push_back(0);
    }

    void set(int card) { cards.push_back(card); }

    void analyze() {
        sort(cards.begin(), cards.end());
        distSet = Disjoint(max+1);
        
        for (int i=1; i<cards.size(); i++) {
            for (int c=cards[i-1]+1; c<cards[i]; c++) {
                distSet.unite(c, cards[i]);
            }
        }
    }

    int select(int opponent) {
        int selected = distSet.find(opponent);
        distSet.unite(selected, selected+1);

        return selected;
    }
private:
    int max;
    vector<int> cards;
    Disjoint distSet;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int nums, cards, turns;
    cin >> nums >> cards >> turns;

    Deck deck(nums);
    for (int i=0; i<cards; i++) {
        int card;
        cin >> card;

        deck.set(card);
    }

    deck.analyze();

    for (int t=0; t<turns; t++) {
        int card;
        cin >> card;

        cout << deck.select(card+1) << '\n';
    }

    return 0;
}