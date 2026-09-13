#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <ctime>

using namespace std;

class Twit {
public:
    Twit(int userId, int twitId, int tick):userId(userId), id(twitId), time(tick) {};

    bool operator<(const Twit& other) const {
        return time < other.time;
    }

    int id, userId, time;
};

class User {
public:
    User() {};
    User(int id): id(id) {};

    bool operator==(const User& user) {
        return this->id == user.id;
    }

    void addFollowee(User& user) {
        for (auto followee : followees) {
            if (followee->id == user.id) return;
        }

        followees.push_back(&user);
    }

    void removeFollowee(User& user) {
        auto followee = remove(followees.begin(), followees.end(), &user);
        followees.erase(followee, followees.end());
    }

    void post(int twitId, int time) {
        Twit twit = Twit(id, twitId, time);
        twits.push_back(twit);
    }

    vector<Twit> getTwits(int num) {
        vector<Twit> result;

        int idx = twits.size();
        while (idx>0 && result.size() < num) {
            idx--;
            result.push_back(twits[idx]);
        }

        return result;
    }

    vector<int> getNewsFeed(int num) {
        vector<int> feed;
        priority_queue<Twit> pq;

        for (Twit& t : twits) pq.push(t);

        for (auto user: followees) {
            vector<Twit> twits = user->getTwits(num);

            for (Twit& t : twits) pq.push(t);
        }

        while (!pq.empty() && feed.size() < 10) {
            Twit t = pq.top(); pq.pop();
            feed.push_back(t.id);
        }

        return feed;
    }
private:
    int id;

    vector<Twit> twits = vector<Twit>();
    vector<User*> followees = vector<User*>();
};

class Twitter {
public:
    Twitter() {}
    
    void postTweet(int userId, int tweetId) {
        if (isNewUser(userId)) {
            createUser(userId);
        }

        users[userId].post(tweetId, tick++);
    }
    
    vector<int> getNewsFeed(int userId) {
        if (isNewUser(userId)) return vector<int>();

        return users[userId].getNewsFeed(10);
    }
    
    void follow(int followerId, int followeeId) {
        if (isNewUser(followerId)) createUser(followerId);
        if (isNewUser(followeeId)) createUser(followeeId);
        User& follower = users[followerId];
        User& followee = users[followeeId];

        follower.addFollowee(followee);
    }
    
    void unfollow(int followerId, int followeeId) {
        if (isNewUser(followerId)) createUser(followerId);
        if (isNewUser(followeeId)) createUser(followeeId);
        User& follower = users[followerId];
        User& followee = users[followeeId];

        follower.removeFollowee(followee);
    }

private:
    bool isNewUser(int userID) { 
        return users.find(userID) == users.end();
    }

    void createUser(int userID) {
        users[userID] = User(userID);
    }

    map<int, User> users;
    int tick = 0;
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

int main() {
    Twitter twitter;

    twitter.postTweet(1, 5);

    for (auto twit: twitter.getNewsFeed(1)) cout << twit << " ";
    cout << '\n';

    twitter.follow(1, 2);

    twitter.postTweet(2, 6);

    for (auto twit: twitter.getNewsFeed(1)) cout << twit << " ";
    cout << '\n';

    twitter.unfollow(1, 2);

    for (auto twit: twitter.getNewsFeed(1)) cout << twit << " ";
    cout << '\n';
}