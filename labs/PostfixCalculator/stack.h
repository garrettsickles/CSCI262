/*
 stack.h
 
 For CSCI 262, Fall 2013, Lab 3.
 
 Header file for the stack wrapper class.  The methods below are
 extremely simple adaptors for methods in the linked_list class.
 You can probably write all them as single-statement inline methods
 below.
 */

#ifndef STACK_H
#define STACK_H

#include "linkedList.h"

class stack {
private:
	linked_list _stack;
public:
	int     size()          {   return(_stack.size());  }
	bool    empty()         {   return(_stack.size() == 0); }
	double  top()           {   return(_stack.get(0));  }
	void    pop()           {   _stack.remove_from_head();  }
	void    push(double val){   _stack.insert_at_head(val); }
	void    print_stack()   {   _stack.print_list();    }
};

#endif