#include <set>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const string filename = "wordlist.txt";

int main() {
	srand((unsigned int)NULL);
	int 	n[9] = {10,50,100,500,1000,5000,10000,50000,0};
	vector<unsigned int>	v_graph;
	vector<unsigned int>	s_graph;

	string			random = "       ";
	string			buffer;
	vector<string>	v;
	set<string>		s;
	fstream			wordlist(filename);

	clock_t t1,t2;
	clock_t t3,t4;
	double diff;

	if(!wordlist.is_open()) {
		cerr << "Error opening " + filename + "\nNow exiting...\n";
		return(-1);
	}


	// Read the dictionary into a set and a vector
	while(wordlist >> buffer) {
		v.push_back(buffer);
		s.insert(buffer);
	}

	wordlist.close();

	n[8] = s.size();

	ofstream	comparison("compare.csv");
	if(!comparison.is_open()) {
		cerr << "Error opening compare.csv\nNow exiting...\n";
		return(-1);
	}
	for(int index = 0; index < 9; index++) {
		for(int i = 0; i < 7; i++)	random[i] = (rand() % 26) + 97;
		comparison << n[index] << ",";
		t1=clock();

		// Perform your random string lookup n times for the set_dictionary
		for(int i = 0; i < n[index]; i++)	s.find(random);
		
		t2=clock();

		diff = ((double)t2-(double)t1); // Number of CPU clock ticks from t1 to t2
		cout<< "Set Dictionary: " << diff << endl;
		comparison << diff << ",";
		t3=clock();
		

		// Perform your random string lookup n times for the vect_dictionary
		for(int i = 0; i < n[index]; i++)
			for(int j = v.size(); j > 0; j--)
				if(v[j] == random)
					break;
		
		t4=clock();

		diff = ((double)t4-(double)t3); // Number of CPU clock ticks from t3 to t4
		cout<< "Vector Dictionary: " << diff << endl;
		comparison << diff << "\n";
	}
	comparison.close();
	return 0;

}