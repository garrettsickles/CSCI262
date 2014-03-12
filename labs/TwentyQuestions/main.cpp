#include "TwentyQuestions.h"

using namespace std;

const string FILENAME = "animal.txt";

int main() {
	char menu_choice = 0;
	bool playing = true;
	TwentyQuestions game(FILENAME);
	while(playing) {
		cout << "Welcome to 20 questions!\n";
		cout << "\t1) Play the game\n";
		cout << "\t2) Save the game file\n";
		cout << "\t3) Quit\n";
		cout << "Please make your selection: ";
		cin >> menu_choice;
		switch(menu_choice) {
			case '1':
			game.play();
			break;
			case '2':
			game.save(FILENAME);
			break;
			
			case '3':
			playing = false;
			cout << "Now exiting Twenty Questions...\nThanks for playing!\n";
			break;

			default:
			cout << "Enter a value from 1-3...\n";
		}
	}
	return(0);
}