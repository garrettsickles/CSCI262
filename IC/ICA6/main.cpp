//
//  main.cpp
//  ICA6
//
//  Created by Garrett Frank Sickles on 9/16/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "dog.h"
#include "cat.h"
#include "dinosaur.h"

using namespace std;
int main(){
    
	dog d;
	d.name = "Emily";
	d.age = 2;
	d.breed = "Dachshund";
    
	cat c;
	c.name = "Mr. Tinkles";
	c.age = 13;
	c.attitude = "evil!";
    
	dinosaur t;
	t.name = "Rex";
	t.age = 42;
	t.num_teeth = 500;
    
    
	cout << "Should be: " << endl;
	cout << "My name is Emily and I am 2 years old." << endl;
	cout << "I am a Dachshund" << endl;
	cout << "I say Bark!" << endl << endl;
	cout << "Actual: " << endl;
	d.print();
	d.speak();
	cout << endl;
    
	cout << "Should be: " << endl;
	cout << "My name is Mr. Tinkles and I am 13 years old." << endl;
	cout << "I am evil!" << endl;
	cout << "I say Meow.." << endl << endl;
	cout << "Actual: " << endl;
	c.print();
	c.speak();
	cout << endl;
    
	cout << "Should be: " << endl;
	cout << "My name is Rex and I am 42 years old." << endl;
	cout << "I have 500 teeth" << endl;
	cout << "I say Raaawwrrr!" << endl << endl;
	cout << "Actual: " << endl;
	t.print();
	t.speak();
    
	return 0;
}