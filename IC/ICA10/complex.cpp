//
//  complex.cpp
//  ICA10
//
//  Created by Garrett Frank Sickles on 10/2/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "complex.h"

complex::complex(double a, double b) {
    this->real = a;
    this->imaginary = b;
}

complex complex::operator +(complex c) {
    complex d(this->real + c.real, this->imaginary + c.imaginary);
    return(d);
}

complex complex::operator -(complex c) {
    complex d(this->real - c.real, this->imaginary - c.imaginary);
    return(d);
}

complex complex::operator *(complex c) {
    complex d((this->real * c.real) - (this->imaginary * c.imaginary), (this->real * c.imaginary) + (this->imaginary * c.real));
    return(d);
}

complex complex::operator /(complex c) {
    double denominator = (this->real * c.real) + (this->imaginary * c.imaginary);
    complex d(((*this) * c).real / denominator, ((*this) * c).imaginary / denominator);
    return(d);
}

bool complex::operator ==(complex c) {
    return(this->real == c.real && this->imaginary == c.imaginary);
}

void complex::print() {
    std::cout << this->real << "r " << this->imaginary << "i" << std::endl;
}