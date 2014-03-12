#include "linkedList.h"
#include <iostream>
#include <cmath>

using namespace std;

linked_list::~linked_list() {
	while (_head != NULL) remove_from_head();
}

linked_list::linked_list(const linked_list& source) {
	_head = NULL;
	_tail = NULL;
	_size = 0;
	_copy(source);
}

void linked_list::operator =(const linked_list& source) {
	if (this != &source) _copy(source);
}

void linked_list::insert_at_head(double d) {
	_head = new node(d, _head);
	if (_tail == NULL) _tail = _head;
	_size++;
}

void linked_list::insert_at_tail(double d) {
	if (_tail == NULL) insert_at_head(d);
	else {
		_tail->_next = new node(d);
		_tail = _tail->_next;
		_size++;
	}
}

void linked_list::insert(double d, int position) {
	if (position == 0) insert_at_head(d);
	else if (position == _size) insert_at_tail(d);
	else if (position < _size && position > 0) {
		node *p = _head;
		for (int i = 0; i < position - 1; i++) p = p->_next;
		p->_next = new node(d, p->_next);
		_size++;
	}
	// else we have an invalid insertion point
}

void linked_list::remove_from_head() {
	if (_head != NULL) {
		node* p = _head;
		_head = _head->_next;
		if (p == _tail) _tail = NULL;
		delete p;
		_size--;
	}
}

void linked_list::remove_from_tail() {
	if (_head != NULL) {
		if (_head == _tail) {
			delete _head;
			_head = _tail = NULL;
		}
		else {
			node* p = _head;
			while (p->_next != _tail) {
				p = p->_next;
			}
			delete _tail;
			_tail = p;
			_tail->_next = NULL;
		}
		_size--;
	}
}

void linked_list::erase(int position) {
	if (position == 0) remove_from_head();
	else if (position == _size - 1) remove_from_tail();
	else if (position < _size - 1 && position > 0) {
		node *p = _head;
		for (int i = 0; i < position - 1; i++) p = p->_next;
		node *t = p->_next;
		p->_next = p->_next->_next;
		delete t;
		_size--;
	}
	// else we have an invalid position
}

double linked_list::get(int position) {
	if (position < _size && position >= 0) {
		node *p = _head;
		for (int i = 0; i < position; i++) p = p->_next;
		return p->_data;
	}
	// else we have an invalid position
	return nan("");
}

void linked_list::print_list() {
	node* current = _head;
    cout << "----" << endl;
	while(current != NULL) {
		cout << current->_data << endl;
		current = current->_next;
	}
	cout << "----" << endl;
}

void linked_list::print_structure() {
	node* current = _head;
	cout << "size " << _size << " linked list:" << endl;
	cout << "_head->";
	while(current != NULL) {
		if(current->_next != NULL)
			cout << "|" << current->_data << "|*|->";
		else
			cout << "|" << current->_data << "|/|";
		current = current->_next;
	}
	cout << endl;
}

void linked_list::_copy(const linked_list& source) {
	while (_head != NULL) remove_from_head();
    
	node *p = source._head;
	while (p != NULL) {
		insert_at_tail(p->_data);
		p = p->_next;
	}
}