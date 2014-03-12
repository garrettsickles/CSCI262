#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename DATA>
bool binary_search(DATA& item, vector<DATA>& dict, int first, int last) {
	if(last < first)
		return(false);
	if(dict[(first+last)/2].compare(item) < 0)
		return(binary_search<string>(item, dict, ((first+last)/2)+1, last));
	else if(dict[(first+last)/2].compare(item) > 0)
		return(binary_search<string>(item, dict, first, ((first+last)/2)-1));
	else if(dict[(first+last)/2].compare(item) == 0)
		return(true);
	else
		return(false);
}

int main() {
	ifstream wordlist("wordlist.txt");
	if(!wordlist.is_open()) {
		cerr << "Error opening file!\nNow exiting...\n";
		return(-1);
	}

	std::istream_iterator<string> start(wordlist), end;
	vector<string> list_O_words(start, end);
	string buffer;

	cout << "Enter a word to search for: ";
	cin >> buffer;
	if(binary_search<string>(buffer, list_O_words, 0, list_O_words.size()))
		cout << "Great! I found " << buffer << ".\n";
	else
		cout << "I did not seem to find " << buffer << " in the list...\nPerhaps another time!\n";
}


