//
//  main.cpp
//  ICA3
//
//  Created by Garrett Frank Sickles on 8/28/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include <iostream>

#include "list.h"

using namespace std;

int main()
{
    list lst;
    
	// fill list with digits 0 - 9
	int i;
	for (i = 0; i < 10; i++) {
		lst.add('0' + i);
	}
	cout << "expected: 0123456789" << endl;
	cout << "actual  : ";
    lst.print();
    
	// should delete every other digit, I hope
	for (i = 1; i < lst.size(); i++) {
		lst.erase(i);
	}
	cout << "expected: 02468" << endl;
	cout << "actual  : ";
	lst.print();
    
	// insert 'abc' after second char
	for (i = 0; i < 3; i++) {
		lst.insert('a'+i, 2+i);
	}
	cout << "expected: 02abc468" << endl;
	cout << "actual  : ";
	lst.print();
    
    lst.menu();
    
	system("pause");
	return 0;
}

