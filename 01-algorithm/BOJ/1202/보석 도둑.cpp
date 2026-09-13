#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Gem {
    int weight;
    int value;
};

class DescendingByValue {
public:
    bool operator()(const Gem &left, const Gem &right) {
        return left.value < right.value;
    }
};

class AscendingByWeight {
public:
    bool operator()(const Gem &left, const Gem &right) {
        return left.weight < right.weight;
    }
};

class Thief {
public:
    Thief(int gems, int bags) {
        this->gems = vector<Gem>(gems);
        this->bags = vector<int>(bags);
    }

    void setGem(int weight, int value, int num) {
        gems[num] = {weight, value};
    }

    void setBag(int cap, int num) {
        bags[num] = cap;
    }

    long put() {
        sort(gems.begin(), gems.end(), AscendingByWeight());
        sort(bags.begin(), bags.end());
        priority_queue<Gem, vector<Gem>, DescendingByValue> pq;

        int iGem = 0;
        long sum = 0;
        for (int cap : bags) {
            while (iGem < gems.size()) {
                if (gems[iGem].weight > cap) break;
                
                pq.push(gems[iGem]);
                iGem++;
            }

            if (!pq.empty()) {
                sum += pq.top().value;
                pq.pop();
            }
        }

        return sum;
    }

private:
    vector<Gem> gems;
    vector<int> bags;
};

int main() {
    int gems, bags;
    cin >> gems >> bags;

    Thief thief(gems, bags);
    for (int i=0; i<gems; i++) {
        int weight, value;
        cin >> weight >> value;
        
        thief.setGem(weight, value, i);
    }

    for (int i=0; i<bags; i++) {
        int cap;
        cin >> cap;

        thief.setBag(cap, i);
    }

    cout << thief.put() << '\n';
}