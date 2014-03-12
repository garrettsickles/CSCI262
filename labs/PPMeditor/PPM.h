//
//  PPM.h
//  PPMeditor
//
//  Created by Garrett Frank Sickles on 8/30/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __PPMeditor__PPM__
#define __PPMeditor__PPM__

#include <iostream>
#include <fstream>
#include <string>

const unsigned short BUFFER_SIZE = 3000;
const unsigned short PROCESS_COUNT = 11;
const unsigned short DEFAULT_NOISE_RANGE = 50;

using namespace std;

class PPM {
public:
    PPM();
    
    bool inputFile(string fileName);
    bool outputFile(string fileName);
    void editFile();
    void kill();
    
    void loadBuffer();
    void editBuffer();
    void writeBuffer();

    void menu();
    
    // Image editing
    void negate_red();                  // Its job is to negate the red number of each pixel.
    void negate_green();                // As above but change the green
    void negate_blue();                 // As above but change the blue
    void flip_horizontal();             // Flips each row horizontally
    void grey_scale();                  // Sets each pixel value to the average of the three
    void flatten_red();                 // Sets the red value to zero
    void flatten_green();               // Sets the green value to zero
    void flatten_blue();                // Sets the blue value to zero
    void horizontal_blur();             // Blurs adjacent pixels
    void extreme_contrast();            // Sets colors to their max or min values
    void random_noise(unsigned short);  // randomly changes the color of each pixel within a range
    void flip_vertical();               // Flips each column vertically
    
private:
    ifstream        input;
    ofstream        output;
    string          inputFilename, outputFilename, filetype;
    bool            isApplied[PROCESS_COUNT];
    unsigned int    rows, columns, maxColor, bufferSize;
    int             buffer[BUFFER_SIZE];
};
#endif /* defined(__PPMeditor__PPM__) */
