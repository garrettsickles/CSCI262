/*
 postfix_calculator.h
 
 For CSCI 262, Fall 2013, Lab 3.
 
 Header file for the postfix calculator.  You shouldn't need to
 modify anything in here, although you may add functions, etc.
 
 author: C. Painter-Wakefield
 */

#ifndef POSTFIX_CALCULATOR_H
#define POSTFIX_CALCULATOR_H

#include "stack.h"
#include <string>

class postfix_calculator {
public:
	// Take in and process a string query such as "7 14 * 3 /".
	// The string is read left to right.  Numbers are pushed onto
	// the stack.  All other strings are assumed to be operators.
	// If the operator is a binary operator such as "+", then two
	// numbers are popped off the stack, the binary operator is
	// applied, and the answer is pushed back on the stack.  If
	// the operator is a unary operator such as "sin" (if
	// implemented), then only one number is popped off and the
	// answer pushed.
	//
	// IF the query causes a stack underflow situation (i.e.,
	// an operator requires an operand but the stack is empty),
	// then the _stack_underflow_flag is set to true and the
	// method returns false.
	//
	// IF any operator is not recognized, then the method returns
	// false, the _invalid_operator_flag is set to true, and the
	// _invalid_operator_string is set to the unknown operator.
	//
	// When either flag has been set, the behavior of evaluate
	// is unspecified until the clear() function is called.
	bool evaluate(std::string);
    
	// Clear flags and invalid operator string, if set, and remove
	// all items from the current stack.
	void clear();
    
	// Return the number at the top of the stack (this will be the
	// answer if a valid query was passed to evaluate).  If the
	// stack is empty, returns 0.0.  The number  should *not* be
	// popped from the stack (this allows further  calculations
	// using this number).
	double top();
    
	// Errors
	bool stack_underflow_flag()
    { return _stack_underflow_flag; }
	bool invalid_operator_flag()
    { return _invalid_operator_flag; }
	std::string invalid_operator_string()
    { return _invalid_operator_string; }
    
	// Debugging
	void print_stack()
    { _stack.print_stack(); }
    
	// Constructor
	postfix_calculator() {
		_stack_underflow_flag = false;
		_invalid_operator_flag = false;
		_invalid_operator_string = "";
	}
    
	// Utility
	// If the contents of string s are recognizable as a real
	// number, then the value of d is set to the number and
	// true is returned.  If not, d is set to 0.0 and false is
	// returned.
	static bool to_double(const std::string& s, double &d);
    
private:
	stack 		_stack;
	bool		_stack_underflow_flag;
	bool		_invalid_operator_flag;
	std::string	_invalid_operator_string;
};

#endif