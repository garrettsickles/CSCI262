#include <iostream>
#include <string>
#include "list.h"

using namespace std;

void print_list(list lst) {
	int i;
	for (i = 0; i < lst.size(); i++) {
		cout << lst.get(i);
	}
	cout << endl;
}

int main() {
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

	// test copy constructor
	list lst2(lst);
	string s = "this is list 2";
	for (i = 0; i < s.length(); i++) lst2.add(s.at(i));

	// check that list 2 is a copy of list 1 with s appended
	cout << "expected: 02abc468this is list 2" << endl;
	cout << "actual  : ";
	lst2.print();

	// check that list 1 is unchanged
	cout << "expected: 02abc468" << endl;
	cout << "actual  : ";
	lst.print();

	// test assignment operator
	list lst3;
	lst3 = lst;
	s = "this is list 3";
	for (i = 0; i < s.length(); i++) lst3.add(s.at(i));
	cout << "expected: 02abc468this is list 3" << endl;
	cout << "actual  : ";
	lst3.print();
	cout << "expected: 02abc468" << endl;
	cout << "actual  : ";
	lst.print();

	// test destructor (at least that it doesn't blow up -
	// hard to test if it actually does the right thing!
	list* lst4 = new list(1000);
	delete lst4;

    lst.menu();
	return 0;
}