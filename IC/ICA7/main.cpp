//
//  main.cpp
//  ICA7
//
//  Created by Garrett Frank Sickles on 9/18/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include <iostream>
#include "stack.h"

using namespace std;

int main() {
    stack alphabet;
    
    for(int i = 0; i < 10; i++) {
        alphabet.push((double)i);
        cout << alphabet.top() << " added to stack\n";
    }
    cout << '\n' << alphabet.size() << " elements in the stack\n";
    cout << "Those elements from top to bottom are...\n";
    alphabet.print_stack();
    
    while(!alphabet.empty()) {
        cout << alphabet.top() << " removed from the stack\n";
        alphabet.pop();
    }
}

