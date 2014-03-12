#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <cstdlib>

class node {

friend class linked_list;

public:
	node() 			{ _next = NULL; }
	node(char d, node* n = NULL) 	
				{ _next = n; _data = d; }

private:
	node* 		_next;
	char	 	_data;
};


class linked_list {
public:
	linked_list()			{ _head = NULL; _tail = NULL; _size = 0; }
	~linked_list();
	linked_list(const linked_list&);

	void operator =(const linked_list&);

	int size() 			{ return _size; }
	char get(int position);

	void insert_at_head(char);
	void insert_at_tail(char);
	void insert(char, int);
	void add(char d) 		{ insert_at_tail(d); }

	void remove_from_head();
	void remove_from_tail();
	void erase(int position);

	void print_list();
	void print_structure();

private:
	node* _head;
	node* _tail;
	int   _size;
	
	void _copy(const linked_list&);
};

#endif