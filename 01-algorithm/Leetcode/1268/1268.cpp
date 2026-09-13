#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Node {
public:
	Node() : value(' '), isTerminal(false) {}
	Node(char value) : value(value) {}

	bool isEmpty() {
		return childs.size() == 0;
	}

	char value = ' ';
	map<char, Node> childs;
	bool isTerminal = false;
};

class Trie {
public:
	void insert(string word) {
		Node* current = &root;

		for (char ch : word) {
			if (!isChild(*current, ch)) {
				Node* newNode = new Node(ch);
				current->childs[ch] = *newNode;
			}

			current = &(current->childs[ch]);
		}

		current->isTerminal = true;
	}

	void insert(vector<string>& words) {
		for (string word : words) {
			insert(word);
		}
	}

	void remove(string word) {
		if (!contains(word))
			return;

		_remove(&root, word, 0);
	}

	void remove(vector<string> words) {
		for (string word : words)
			remove(word);
	}

	// 해당 접두사가 Trie에 존재하는지 검사
	bool contains(string prefix) {
		Node* current = &root;

		for (const char& ch : prefix) {
			if (!isChild(*current, ch))
				return false;

			current = &(current->childs[ch]);
		}

		return true;
	}

	// 접두사가 일치하는 것을 찾는다.
	vector<string> search(string prefix, int num=-1) {
		vector<string> result;
		Node* current = &root;
		// 첫 글자가 없으면 빈 벡터 반환
		if (!isChild(root, prefix.at(0)))
			return result;

		for (char ch : prefix) {
			if (!isChild(*current, ch)) return result;

			current = &(current->childs[ch]);
		}

		_getWords(result, prefix, *current, num);

		return result;
	}

private:
	Node root = Node(' ');

	bool isChild(Node& node, char ch) {
		return !(node.childs.find(ch) == node.childs.end());
	}

	// 백트래킹으로 하위에 저장중인 단어들을 반환한다.
	void _getWords(vector<string>& result, string word, Node& node, int num=-1) {
		if (num >= 0 && result.size() >= num)
			return;
		if (node.isTerminal)
			result.push_back(word);
		if (node.childs.empty())
			return;

		for (const auto& key : node.childs) {
			char value = key.first;
			_getWords(result, word + value, node.childs[value], num);
		}
	}

	// 단어를 삭제한다. node를 해제한 경우 true 반환
	bool _remove(Node* node, string word, int depth = 0) {
		// 탈출조건: 단어의 끝
		if (depth == word.length()) {
			node->isTerminal = false;

			if (node->isEmpty())
				return true;

			return false;
		}

		// Descending: 계속 탐색한다.
		char ch = word.at(depth);
		Node* child = &(node->childs[ch]);
		bool deleted = _remove(child, word, depth + 1);

		// Ascending: 분기점까지 계속 해제한다.
		if (!deleted)
			return false;
		node->childs.erase(ch);

		if (node->isEmpty())	return true;
		else					return false;
	}
};

bool isPrefix(string prefix, string word) {
	if (prefix.size() > word.size()) 
		return false;

	auto res = mismatch(prefix.begin(), prefix.end(), word.begin());

	return (res.first == prefix.end());
}

vector<string> containsPrefix(vector<string>& words, string prefix) {
	vector<string> result;
	
	for (string word : words) {
		if (isPrefix(prefix, word)) result.push_back(word);
	}

	return result;
}

void extendVector(vector<string>& dest, vector<string>& src, int num = -1) {
	if (num < 0)
		num = src.size();
	if (src.size() == 0)
		return;

	dest.insert(dest.end(), src.begin(), src.begin() + num);
}

int leetcode_1268() {
	vector<string> words = { "mobile","mouse","moneypot","monitor","mousepad" };
	string searchWord = "mouse";
	vector<vector<string>> results;
	vector<string> lastResult;
	Trie trie = Trie();

	trie.insert(words);

	string searchString = "";
	searchString.append(1, searchWord.at(0));
	lastResult = trie.search(searchString, 3);
	trie.remove(lastResult);
	results.push_back(lastResult);

	for (int i = 1; i < searchWord.length(); i++) {
		char ch = searchWord.at(i);
		searchString.append(1, ch);
		vector<string> stored = containsPrefix(lastResult, searchString);

		int maxResultSize = lastResult.size();
		int storedSize = stored.size();
		if (storedSize < maxResultSize) {
			lastResult = trie.search(searchString, maxResultSize - storedSize);
			trie.remove(lastResult);
			for (string word : lastResult)
				stored.push_back(word);
			lastResult = stored;
		}

		results.push_back(lastResult);
	}

	return 0;
}