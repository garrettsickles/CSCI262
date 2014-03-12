//
//  PPM.cpp
//  PPMeditor
//
//  Created by Garrett Frank Sickles on 8/30/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "PPM.h"

PPM::PPM() {
    bufferSize = BUFFER_SIZE - (BUFFER_SIZE % 3);
}

bool PPM::inputFile(string fileName) {
    inputFilename = fileName;
    input.open(inputFilename.c_str());
    if (!input.is_open()) {
        cout << "Failed to open input P.P.M file:\t'" << inputFilename << "'\n!!!Aborting PPMeditor!!!\n";
        return(false);
    }
    else {
        input >> filetype >> columns >> rows >> maxColor;
        if(columns > (bufferSize / 3)) {
            cout << "Image too large for PPMeditor's filebuffer\n!!!Aborting PPM editor!!!\n";
            return(false);
        }
        else
            return(true);
    }
}

bool PPM::outputFile(string fileName) {
    outputFilename = fileName;
    output.open(outputFilename.c_str());
    if (!output.is_open()) {
        cout << "Failed to open output P.P.M file:\t'" << outputFilename << "'\n!!!Aborting PPMeditor!!!\n";
        return(false);
    }
    else {
        output << filetype << "\n" << columns << " " <<  rows << "\n" << maxColor << "\n";
        return(true);
    }
}

void PPM::editFile() {
    for(unsigned int i = 0; i < rows; i++) {
        loadBuffer();
        editBuffer();
        writeBuffer();
    }
    kill();
}

void PPM::kill() {
    input.close();
    output.close();
}

void PPM::loadBuffer() {
    if(input.is_open())
        for(unsigned int i = 0; i < columns * 3; i++)
            input >> buffer[i];
}

void PPM::editBuffer() {
    if(isApplied[0]) grey_scale();
    if(isApplied[1]) flip_horizontal();
    if(isApplied[2]) negate_red();
    if(isApplied[3]) negate_green();
    if(isApplied[4]) negate_blue();
    if(isApplied[5]) {
        flatten_green();
        flatten_blue();
    }
    if(isApplied[6]) {
        flatten_red();
        flatten_blue();
    }
    if(isApplied[7]) {
        flatten_red();
        flatten_green();
    }
    if(isApplied[8]) horizontal_blur();
    if(isApplied[9]) extreme_contrast();
    if(isApplied[10]) random_noise(DEFAULT_NOISE_RANGE);
}

void PPM::writeBuffer() {
    if(output.is_open()) {
        for(unsigned int i = 0; i < (columns * 3); i++)
            output << buffer[i] << " ";
        output << endl;
    }
}

void PPM::menu() {
    cout << "\nEnter 1 to execute the edit option...\nEnter 0 to ignore the edit option...\n";
    cout << "Here are your choices:\n";
    cout << "Convert to greyscale:\t";
    cin >> isApplied[0];
    cout << "Flip horizontally:\t";
    cin >> isApplied[1];
    cout << "Negative of red:\t";
    cin >> isApplied[2];
    cout << "Negative of green:\t";
    cin >> isApplied[3];
    cout << "Negative of blue:\t";
    cin >> isApplied[4];
    cout << "Just the reds:\t\t";
    cin >> isApplied[5];
    cout << "Just the greens:\t";
    cin >> isApplied[6];
    cout << "Just the blues:\t\t";
    cin >> isApplied[7];
    cout << "Horizontal Blur:\t";
    cin >> isApplied[8];
    cout << "Extreme Contrast:\t";
    cin >> isApplied[9];
    cout << "Random Noise:\t\t";
    cin >> isApplied[10];
}

void PPM::negate_red() {
    for(unsigned int i = 0; i < columns * 3; i+=3)
        buffer[i] = maxColor - buffer[i];
}

void PPM::negate_green() {
    for(unsigned int i = 1; i < columns * 3; i+=3)
        buffer[i] = maxColor - buffer[i];
}

void PPM::negate_blue() {
    for(unsigned int i = 2; i < columns * 3; i+=3)
        buffer[i] = maxColor - buffer[i];
}

void PPM::flip_horizontal() {
    unsigned short temp[3];
    for(unsigned int i = 0; i < (columns / 2); i++) {
        temp[0] = buffer[(i * 3)];
        temp[1] = buffer[(i * 3) + 1];
        temp[2] = buffer[(i * 3) + 2];
        buffer[(i * 3)] = buffer[((columns - 1) * 3) - (i * 3)];
        buffer[(i * 3) + 1] = buffer[((columns - 1) * 3) - (i * 3) + 1];
        buffer[(i * 3) + 2] = buffer[((columns - 1) * 3) - (i * 3) + 2];
        buffer[((columns - 1) * 3) - (i * 3)] = temp[0];
        buffer[((columns - 1) * 3) - (i * 3) + 1] = temp[1];
        buffer[((columns - 1) * 3) - (i * 3) + 2] = temp[2];
    }
}

void PPM::grey_scale() {
    unsigned short mean;
    for(unsigned int i = 0; i < columns * 3; i+=3) {
        mean = (buffer[i] + buffer[i + 1] + buffer[i + 2]) / 3;
        buffer[i] = mean;
        buffer[i + 1] = mean;
        buffer[i + 2] = mean;
    }
}

void PPM::flatten_red() {
    for(unsigned int i = 0; i < columns * 3; i+=3)
        buffer[i] = 0;
}     // Sets the red value to zero

void PPM::flatten_green() {
    for(unsigned int i = 0; i < columns * 3; i+=3)
        buffer[i + 1] = 0;
}

void PPM::flatten_blue() {
    for(unsigned int i = 0; i < columns * 3; i+=3)
        buffer[i + 2] = 0;
}

void PPM::horizontal_blur() {
    unsigned short temp[2][3];
    unsigned int i = 0;

    temp[0][0] = buffer[0];
    temp[0][1] = buffer[1];
    temp[0][2] = buffer[2];

    buffer[0] = (buffer[0] + buffer[3]) / 2;
    buffer[1] = (buffer[1] + buffer[4]) / 2;
    buffer[2] = (buffer[2] + buffer[5]) / 2;

    for(i = 3; i < ((columns - 1) * 3); i += 3) {
        temp[1][0] = buffer[i];
        buffer[i] = (buffer[i] + temp[0][0] + buffer[i + 3]) / 3;
        temp[1][1] = buffer[i + 1];
        buffer[i + 1] = (buffer[i + 1] + temp[0][1] + buffer[(i + 1) + 3]) / 3;
        temp[1][2] = buffer[i + 2];
        buffer[i + 2] = (buffer[i + 2] + temp[0][2] + buffer[(i + 2) + 3]) / 3;
        temp[0][0] = temp[1][0];
        temp[0][2] = temp[1][1];
        temp[0][1] = temp[1][2];
    }

    buffer[i] = (buffer[i] + temp[0][0]) / 2;
    buffer[i + 1] = (buffer[i + 1] + temp[0][1]) / 2;
    buffer[i + 2] = (buffer[i + 2] + temp[0][2]) / 2;
}

void PPM::extreme_contrast() {
    for(unsigned int i = 0; i < (columns * 3); i++)
        buffer[i] > 127 ? buffer[i] = 255 : buffer[i] = 0; 
}

void PPM::random_noise(unsigned short range) {
    short sign = rand() % 2;
    unsigned short value = rand() % range;

    sign ? sign = 1 : sign = -1;

    for(unsigned int i = 0; i < columns * 3; i+=3) {
        sign = rand() % 2;
        value = rand() % range;
        sign ? sign = 1 : sign = -1;
        ((buffer[i] + (sign * value)) < 0) ? buffer[i] = 0 : (buffer[i] += (sign * value));
        buffer[i] > 255 ? buffer[i] = 255 : 1;
    }
}