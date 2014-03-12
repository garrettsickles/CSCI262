//	ICA11
//	Author: Garrett Sickles
//	Class:	CSCI262 Section B
//
//	Description:
//	This project tests recursion using the power function and binary recursion

#include <iostream>

double power(double base, int exponent) {
	if(exponent == 0)
		return(1.0);
	else if(exponent == 1)
		return(base);
	else if(exponent == -1)
		return(1.0 / base);
	else
		return(power(base, exponent / 2) * power(base, exponent - exponent / 2));
}

int main() {

	for(int i = -10; i <= 10; i++) {
		std::cout << "Testing " << i << " as the base parameter:\n";
		for(int j = -3; j <= 3; j++) {
			std::cout << power(i, j) << ", " << "\n";
		}
		std::cout << "\n";
	}
	system("PAUSE");
	return(0);
}