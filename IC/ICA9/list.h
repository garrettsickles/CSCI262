#ifndef LIST_H
#define LIST_H
#include <string>
#include <iostream>

using namespace std;

template <class T>
class list {
public:
	// constructors and destructor
	list();	                    // constructs list with capacity of 4
	list(int initial_capacity); // constructs list with specified capacity
	list(const list&);          // copy constructor
	~list();

	// assignment operator
	void operator =(const list&);

	// return current size of list
	int size();

	// return Tacter at position; should return NUL ('\0')
	// if position is greater than or equal to _size.
	T get(int position);

	// append a Tacter to the end of the list.  If the list
	// size is full, this method should create a new array that
	// is twice as big as the _capacity, copy the values from 
	// _data into the new array, add the Tacter c at the end of
	// the new array, and set _data equal to the new array.
	void add(T c);

	// insert a Tacter before the Tacter at position; e.g.,
	// if the list is
	//    a b c d
	// then insert('z', 2) should result in
	//    a b z c d
	// If the list size is full, this method should create a 
	// new array that is twice as big as the _capacity, 
	// copy the values from _data into the new array, insert the
	// Tacter c at the correct location in the new array, and 
	// set _data equal to the new array.
	void insert(T c, int position);

	// remove the Tacter at position; e.g., if the list is
	//    a b c d
	// then erase(2) should result in
	//    a b d
	// The method should do nothing if position is greater than 
	// or equal to the _size of the list.
	void erase(int position);

	// print function
	void print_list();

private:
	int _size;		// stores the current size of the list
	T* _data;		// stores the list data
	int _capacity;	// private member var to track how big the array 
				    // currently is
};

template<class T>
list<T>::list() {
	_size = 0;
	_capacity = 4;
	_data = new T[4];
}

template<class T>
list<T>::list(int cap) {
	_size = 0;
	_capacity = cap;
	_data = new T[cap];
}

template<class T>
list<T>::list(const list& lst) {
	_size = lst._size;
	_capacity = lst._capacity;
	_data = new T[lst._capacity];
	for (int i = 0; i < lst._size; i++) {
		_data[i] = lst._data[i];
	}
}

template<class T>
list<T>::~list() {
	delete[] _data;
}

template<class T>
void list<T>::operator =(const list& lst) {
	if (this == &lst) return;

	delete[] _data;

	_size = lst._size;
	_capacity = lst._capacity;
	_data = new T[lst._capacity];
	for (int i = 0; i < lst._size; i++) {
		_data[i] = lst._data[i];
	}
}

template<class T>
int list<T>::size() {
	return _size;
}

template<class T>
T list<T>::get(int pos) {
	if (pos < _size) {
		return _data[pos];
	} else {
		return '\0';
	}
}

template<class T>
void list<T>::add(T c) {
	if (_size == _capacity) {
		_capacity *= 2;
		T* new_data = new T[_capacity];
		for (int i = 0; i < _size; i++) {
			new_data[i] = _data[i];
		}
		delete[] _data;
		_data = new_data;
	}
	_data[_size] = c;	
	_size++;
}

template<class T>
void list<T>::insert(T c, int pos) {
	if (pos > _size) return; // not a valid insert position
	if (_size == _capacity) {
		_capacity *= 2;
		T* new_data = new T[_capacity];
		for (int i = 0; i < _size; i++) {
			new_data[i] = _data[i];
		}
		delete[] _data;
		_data = new_data;
	}

	// copy tail of list one position right
	int i;
	for (i = _size-1; i >= pos ; i--) {
		_data[i+1] = _data[i];
	}

	_data[pos] = c;
	_size++;
}

template<class T>
void list<T>::erase(int pos) {
	if (pos < _size) {
		// copy everything to right of pos one position left
		int i;
		for (i = pos; i < _size; i++) {
			_data[i] = _data[i + 1];
		}

		// clean up just to make debugging easier
		_data[_size] = '\0';

		_size--;
	}
}

template<class T>
void list<T>::print_list() {
	int i;
	for (i = 0; i < _size; i++) {
		cout << get(i);
	}
	cout << endl;
}

#endif