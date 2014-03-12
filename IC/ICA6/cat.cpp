//
//  cat.cpp
//  ICA6
//
//  Created by Garrett Frank Sickles on 9/16/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "cat.h"

void cat::print() {
    animal::print();
    std::cout << "I am " << attitude << '\n';
}

void cat::speak() {
    std::cout << "I say Meow..\n";
}