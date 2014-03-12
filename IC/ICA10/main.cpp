//
//  main.cpp
//  ICA10
//
//  Created by Garrett Frank Sickles on 10/2/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//


#include <iostream>
#include <string>
#include "complex.h"

using namespace std;

int main(){
    complex a(4.0, 7.5);
    complex b(0.0, 1.0);
    complex c(1.5, 0.0);
    
    cout << "a + b = ";
    (a + b).print();
    (a - b).print();
    (a * b).print();
    (a / b).print();
    // optional:
    // test mixed type (double/complex) binary operations
    // test cout << a << endl;
    
    return 0;
}