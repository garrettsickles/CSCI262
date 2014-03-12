//
//  main.cpp
//  PPMeditor
//
//  Created by Garrett Frank Sickles on 8/27/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "PPM.h"

using namespace std;

int main() {
    //  Data objects storing information about the input and output P.P.M. data files
    PPM image;
    string inputFilename, outputFilename;
    
    cout << "---------- PPMeditor by Garrett Sickles ----------\n";
    
    //  Get an input P.P.M. image filename from the user
    //  Abort PPMeditor if the file is unsuccesfully opened
    cout << "Please enter an input filename:\t\t";
    cin >> inputFilename;
    if(!image.inputFile(inputFilename))
        return(-1);
    
    //  Get an output P.P.M. image filename from the user
    //  Abort PPMeditor if the file is unsuccesfully opened
    cout << "Please enter an output filename:\t";
    cin >> outputFilename;
    if(!image.outputFile(outputFilename))
        return(-1);

    
    image.menu();
    image.editFile();
}

