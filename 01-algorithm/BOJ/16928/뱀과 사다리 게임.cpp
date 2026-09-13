#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pair {
    int position;
    int turn;
};

class Board {
public:
    Board() {
        for (int i=0; i<=100; i++) {
            moves[i] = i;
        }
    };

    void setLadder(int from, int to) {
        moves[from] = to;
    }

    int getMinimumTurn() {
        vector<bool> visited = vector<bool>(101, false);
        queue<Pair> q;

        q.push(Pair{1, 0});
        visited[1] = true;

        while (!q.empty()) {
            Pair cur = q.front();
            q.pop();

            for (int n=1; n<=6; n++) {
                int nextPos = cur.position + n;
                int nextTurn = cur.turn + 1;
                if (nextPos >= 100) return nextTurn;
                if (visited[nextPos]) continue;
                
                nextPos = moves[nextPos];
                q.push(Pair{nextPos, nextTurn});
                visited[nextPos] = true;
            }
        }

        return 100;
    }

private:
    vector<int> moves = vector<int>(101);
};

int main() {
    int ladders, snakes;
    cin >> ladders >> snakes;

    Board board;
    for (int i=0; i<ladders+snakes; i++) {
        int from, to;
        cin >> from >> to;

        board.setLadder(from, to);
    }

    cout << board.getMinimumTurn() << '\n';
}