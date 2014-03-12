//
//  dog.h
//  ICA6
//
//  Created by Garrett Frank Sickles on 9/16/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __ICA6__dog__
#define __ICA6__dog__

#include <iostream>
#include "animal.h"

class dog : public animal {
public:
    std::string breed;
    void print();
    void speak();
};

#endif /* defined(__ICA6__dog__) */
