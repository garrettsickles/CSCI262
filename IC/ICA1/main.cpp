#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum dnaType {G = 0, A, T, C, ERROR};

int main() {
    string sequence, fileName;
    char buffer;
    int letterCount[5] = {0,0,0,0,0};

	ifstream myfile;

	do {
		cout << "Please enter a valid D.N.A. filename.\n";
		cin >> fileName;
		myfile.open(fileName);
		if(!myfile)
			cout << "Unsuccessful file operation.\n";

		else {
			myfile >> sequence;
			myfile.close();
		}
		/*
		cout << "Pleasr enter a valid D.N.A. sequence.\n";
		cin >> sequence;
		*/
	} while(((sequence.size() % 3) != 0 && sequence.size() != 0) || !myfile);

    for(int i = 0; i < sequence.size(); i++) {
		buffer = toupper(sequence[i]);
		if(buffer == 'A') letterCount[A]++;
        else if(buffer == 'G') letterCount[G]++;
        else if(buffer == 'T') letterCount[T]++;
        else if(buffer == 'C') letterCount[C]++;
		else letterCount[ERROR]++;
	}
	
	cout << "G: " << letterCount[G] << "\nA: " << letterCount[A] << "\nT: " << letterCount[T] << "\nC: " << letterCount[C] << endl;
    cout << "Error Count: " <<  letterCount[ERROR] << endl;
	system("PAUSE");
    return(0);
}