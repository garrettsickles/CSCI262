//
//  dinosaur.cpp
//  ICA6
//
//  Created by Garrett Frank Sickles on 9/16/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "dinosaur.h"

void dinosaur::print() {
    animal::print();
    std::cout << "I have " << num_teeth << " teeth\n";
}
void dinosaur::speak() {
    std::cout << "Raaawwrrr!";
}