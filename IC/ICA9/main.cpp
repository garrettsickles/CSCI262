#include <iostream>
#include <string>
#include "list.h"
#include <sstream>

int main() {
	list<char> lst;

	// fill list with digits 0 - 9
	int i;
	for (i = 0; i < 10; i++) {
		lst.add('0' + i);
	}
	cout << "expected: 0123456789" << endl;
	cout << "actual  : ";
	lst.print_list();

	// should delete every other digit, I hope
	for (i = 1; i < lst.size(); i++) {
		lst.erase(i);
	}
	cout << "expected: 02468" << endl;
	cout << "actual  : ";
	lst.print_list();

	// insert 'abc' after second char
	for (i = 0; i < 3; i++) {
		lst.insert('a'+i, 2+i);
	}
	cout << "expected: 02abc468" << endl;
	cout << "actual  : ";
	lst.print_list();

	// test copy constructor
	list<char> lst2(lst);
	string s = "this is list 2";
	for (i = 0; i < s.length(); i++) lst2.add(s.at(i));

	// check that list 2 is a copy of list 1 with s appended
	cout << "expected: 02abc468this is list 2" << endl;
	cout << "actual  : ";
	lst2.print_list();

	// check that list 1 is unchanged
	cout << "expected: 02abc468" << endl;
	cout << "actual  : ";
	lst.print_list();

	// test assignment operator
	list<char> lst3;
	lst3 = lst;
	s = "this is list 3";
	for (i = 0; i < s.length(); i++) lst3.add(s.at(i));
	cout << "expected: 02abc468this is list 3" << endl;
	cout << "actual  : ";
	lst3.print_list();
	cout << "expected: 02abc468" << endl;
	cout << "actual  : ";
	lst.print_list();

	// test destructor (at least that it doesn't blow up -
	// hard to test if it actually does the right thing!
	list<char>* lst4 = new list<char>(1000);
	delete lst4;

	list<string> lst5;

	// fill list with digits 0 - 9
	
	for (i = 0; i < 10; i++) {
		stringstream ss;
		ss << i;
		lst5.add("str"+ss.str());
		ss.clear();
	}
	cout << "expected: str0str1str2str3str4str5str6str7str8str9" << endl;
	cout << "actual  : ";
	lst5.print_list();

	// should delete every other digit, I hope
	for (i = 1; i < lst.size(); i++) {
		lst5.erase(i);
	}
	cout << "expected: str0str2str4str6str8" << endl;
	cout << "actual  : ";
	lst5.print_list();

	// insert 'abc' after second char
	for (i = 0; i < 3; i++) {
		stringstream ss;
		char to_add = 'a' + i;
		ss << to_add;
		lst5.insert(ss.str(), 2+i);
	}
	cout << "expected: str0str2abcstr4str6str8" << endl;
	cout << "actual  : ";
	lst5.print_list();

	// test copy constructor
	list<string> lst6(lst5);
	s = "this is list 6";
	for (i = 0; i < s.length(); i++){
		lst6.add(s.substr(i, 1));
	}

	// check that list 2 is a copy of list 1 with s appended
	cout << "expected: str0str2abcstr4str6str8this is list 6" << endl;
	cout << "actual  : ";
	lst6.print_list();

	// check that list 1 is unchanged
	cout << "expected: str0str2abcstr4str6str8" << endl;
	cout << "actual  : ";
	lst5.print_list();

	// test assignment operator
	list<string> lst7;
	lst7 = lst5;
	s = "this is list 7";
	for (i = 0; i < s.length(); i++) lst7.add(s.substr(i,1));
	cout << "expected: str0str2abcstr4str6str8this is list 7" << endl;
	cout << "actual  : ";
	lst7.print_list();
	cout << "expected: str0str2abcstr4str6str8" << endl;
	cout << "actual  : ";
	lst5.print_list();

	system("PAUSE");
	return 0;
}