//
//  dog.cpp
//  ICA6
//
//  Created by Garrett Frank Sickles on 9/16/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "dog.h"

void dog::print() {
    animal::print();
    std::cout << "I am a " << this->breed << '\n';
}

void dog::speak() {
    std::cout << "I say Bark!\n";
}