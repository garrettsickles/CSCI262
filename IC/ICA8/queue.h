/*
	queue.h

	For CSCI 262, Fall 2013, Lab 3.

	Header file for the queue wrapper class.  The methods below are
	extremely simple adaptors for methods in the linked_list class.
	You can probably write all them as single-statement inline methods
	below.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

class queue {
public:
	int 	size()		{	return(this->_queue.size());	}
	bool 	empty()		{	return(this->_queue.size() == 0);	}
	char 	front()		{	return(this->_queue.get(0));	}
	void 	dequeue()	{	this->_queue.remove_from_head();}
	void 	enqueue(char val)	{	this->_queue.insert_at_tail(val);	}
	void 	print_queue()	{	this->_queue.print_list();	}

private:
	linked_list _queue;
};

#endif