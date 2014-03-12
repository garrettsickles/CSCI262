//
//  animal.h
//  ICA6
//
//  Created by Garrett Frank Sickles on 9/16/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __ICA6__animal__
#define __ICA6__animal__

#include <string>
#include <iostream>

class animal{
public:
    std::string name;
    int age;
    
	virtual void print();
	virtual void speak() = 0;
    
};

#endif /* defined(__ICA6__animal__) */
