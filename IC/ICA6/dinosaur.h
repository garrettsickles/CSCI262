//
//  dinosaur.h
//  ICA6
//
//  Created by Garrett Frank Sickles on 9/16/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __ICA6__dinosaur__
#define __ICA6__dinosaur__

#include <iostream>
#include "animal.h"

class dinosaur : public animal {
public:
    int num_teeth;
    
    void print();
    void speak();
};


#endif /* defined(__ICA6__dinosaur__) */
