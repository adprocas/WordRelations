#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

vector<string> splitString(string line) {
	stringstream ss(line);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;

	vector<string> vstrings(begin, end);
	//copy(vstrings.begin(), vstrings.end(), ostream_iterator<string>(cout, "\n"));

	return vstrings;
}

class Words {
public:
	Words() {}

	int fullCountUnder = 0;
	bool isFullWord = false;
	map<char, Words*> m;

	//insert - takes a string and inserts
	void insert(string text) {
		Words* word = this;
		word->fullCountUnder++;

		for (char &c : text) {
			Words* prev = word;
			word = word->has(c);

			if (word == NULL) {
				Words * newWord = new Words();
				prev->m.insert(pair<char, Words*>(c, newWord));
				word = newWord;
			}

			word->fullCountUnder++;
		}

		if (word != this) {
			word->isFullWord = true;
		}
	}

	Words* has(char c) {
		map<char, Words*>::iterator it = this->m.find(c);

		if (it != this->m.end()) {
			return it->second;
		}

		return NULL;
	}

	int matchCount(string partial) {
		Words* word = this;

		for (char& c : partial) {
			word = word->has(c);

			if (word == NULL) {
				return 0;
			}
		}

		return word->fullCountUnder;
	}

	void insertWords(string line) {
		vector<string> lines = splitString(line);

		for (string l : lines) {
			this->insert(l);
		}
	}
};

int main() {
	Words* word = new Words();

	word->insertWords("hack hackerrank hackathon hakr this is a hacking thing about haks");

	//word->insert("hack");
	//word->insert("hackerrank");

	cout << word->matchCount("hac") << endl;
	cout << word->matchCount("hak") << endl;
}