/*
 calculator_main.cpp
 
 For CSCI 262, Fall 2013, Lab 3.
 
 Provides the user interface for the postfix calculator.
 
 author: C. Painter-Wakefield
 */

#include <iostream>
#include <string>
#include "postfix_calculator.h"

using namespace std;

int main() {
	postfix_calculator calc;
	string input;
    
	cout << "Welcome to the postfix calculator!" << endl;
	cout << "----------------------------------" << endl;
	while (true) {
		cout << "Input string:" << endl;
		getline(cin, input);
        
		if (input == "quit") {
			return 0;
		}
		else if (input == "clear") {
			calc.clear();
		}
		else if (input == "debug") {
			bool has_flags = false;
			cout << "DEBUG MODE:" << endl;
			if (calc.stack_underflow_flag()) {
				cout << "Stack underflow flag set." << endl;
				has_flags = true;
			}
			if (calc.invalid_operator_flag()) {
				cout << "Invalid operator flag set." << endl;
				cout << "Invalid operator: ";
				cout << calc.invalid_operator_string() << endl;
				has_flags = true;
			}
			if (!has_flags) {
				cout << "No flags." << endl;
			}
			if (calc.stack_underflow_flag()) {
				cout << "Stack is empty." << endl;
			} else {
				cout << "Stack contents: " << endl;
				calc.print_stack();
			}
		}
		else {
			bool success = calc.evaluate(input);
			if (success) {
				cout << "answer: " << calc.top() << endl;
			} else if (calc.stack_underflow_flag()) {
				cout << "ERROR: Stack underflow." << endl;
			} else if (calc.invalid_operator_flag()) {
				cout << "ERROR: Unrecognized operator '";
				cout << calc.invalid_operator_string();
				cout << "'." << endl;
			} else {
				cout << "ERROR: Unknown error." << endl;
			}
		}
        
		cout << "----------------------------------" << endl;
	}
    
	return 0;
}