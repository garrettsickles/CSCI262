//
//  complex.h
//  ICA10
//
//  Created by Garrett Frank Sickles on 10/2/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __ICA10__complex__
#define __ICA10__complex__

#include <iostream>

class complex {
public:
    complex(double, double);
    
    complex operator +(complex);
    complex operator -(complex);
    complex operator *(complex);
    complex operator /(complex);
    bool    operator ==(complex);
    void    print();
    
    double real, imaginary;
};
#endif /* defined(__ICA10__complex__) */
