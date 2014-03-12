/*
 postfix_calculator.cpp
 
 For CSCI 262, Fall 2013, Lab 3.
 
 Implementation of the postfix calculator.  You should modify the code
 everywhere you see a "TODO" comment!
 */

#include "postfix_calculator.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

bool postfix_calculator::evaluate(std::string expr) {
    std::istringstream input(expr);
    std::string parse;
    double parseNum;
    double operand[2] = {0.0, 0.0};
    
    _stack_underflow_flag = false;
    _invalid_operator_flag = false;
    _invalid_operator_string = "";
    
    while (input >> parse) {
        if(to_double(parse, parseNum))  _stack.push(parseNum);
        else if(parse == "sin" || parse == "cos" || parse == "tan" || parse == "log" || parse == "ln" || parse == "sqrt") {
            if(_stack.size() == 0)
                _stack_underflow_flag = true;
            else {
                operand[0] = _stack.top();
                _stack.pop();
                if(parse == "sin")      _stack.push(std::sin(operand[0]));
                else if(parse == "cos") _stack.push(std::cos(operand[0]));
                else if(parse == "tan") _stack.push(std::tan(operand[0]));
                else if(parse == "log") _stack.push(std::log10(operand[0]));
                else if(parse == "ln")  _stack.push(std::log(operand[0]));
                else if(parse == "sqrt")_stack.push(std::sqrt(operand[0]));
            }
        }
        else if(parse == "*" || parse == "/" || parse == "-" || parse == "+" || parse == "^") {
            if(_stack.size() <= 1)
                _stack_underflow_flag = true;
            else {
                operand[1] = _stack.top();
                _stack.pop();
                operand[0] = _stack.top();
                _stack.pop();
                if (parse == "*")       _stack.push(operand[0] * operand[1]);
                else if (parse == "/")  _stack.push(operand[0] / operand[1]);
                else if (parse == "-")  _stack.push(operand[0] - operand[1]);
                else if (parse == "+")  _stack.push(operand[0] + operand[1]);
                else if (parse == "^")  _stack.push(std::pow(operand[0], operand[1]));
            }
        }
        else {
            _invalid_operator_flag = true;
            _invalid_operator_string = parse;
        }
    }
	return(!(_stack_underflow_flag || _invalid_operator_flag));
}

void postfix_calculator::clear() {
	while(!_stack.empty())
        _stack.pop();
    _stack_underflow_flag = false;
    _invalid_operator_flag = false;
    _invalid_operator_string = "";
}

double postfix_calculator::top() {
	return(_stack.top() * !_stack.empty());
}

bool postfix_calculator::to_double(const std::string &s, double &d) {
    std::istringstream cvt(s);
	cvt >> d;
	return !(cvt.fail()) && cvt.eof();
}
