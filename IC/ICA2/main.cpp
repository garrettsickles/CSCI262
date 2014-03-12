#include <iostream>

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
	print_list(lst);
    
	// should delete every other digit, I hope
	for (i = 1; i < lst.size(); i++) {
		lst.erase(i);
	}
	cout << "expected: 02468" << endl;
	cout << "actual  : ";
	print_list(lst);
    
	// insert 'abc' after second char
	for (i = 0; i < 3; i++) {
		lst.insert('a'+i, 2+i);
	}
	cout << "expected: 02abc468" << endl;
	cout << "actual  : ";
	print_list(lst);
    
    lst.menu();
	return 0;
}