#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

const string FILENAME = "wordlist.txt";
int main() {
	string buffer;
	ifstream wordlist(FILENAME);
	map<int, vector<string> > wordlength;
	if(!wordlist.is_open()) {
		cerr << "Error opening " << FILENAME << ".\nNow Exiting...\n";
		return(0);
	}
	while(wordlist >> buffer) {
		wordlength[buffer.length()].push_back(buffer);
	}
	wordlist.close();
	for (map<int, vector<string> >::iterator it = wordlength.begin(); it != wordlength.end(); ++it)
		cout << "There are " << it->second.size() <<" words of length " << it->first << '\n';
	return(0);
}