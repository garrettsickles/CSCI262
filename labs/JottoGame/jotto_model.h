//
//  jotto_model.h
//  JottoGame
//
//  Created by Garrett Frank Sickles on 9/12/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __JottoGame__jotto_model__
#define __JottoGame__jotto_model__

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include "linkedList.h"

const int EASY = 15;
const int MEDIUM = 12;
const int HARD = 10;
const unsigned int LETTER_COUNT = 5;
class jotto_model {
private:
    linkedList words;
    unsigned int guessCount;
    std::string secretWord, filename;
    
    unsigned int commmonLetters(std::string, std::string);
    void eleminateWords(unsigned int, std::string);
    void setSecretWord();
public:
    jotto_model();
    jotto_model(std::string);
    ~jotto_model();
    
    bool loadWords(std::string);
    void play();
    unsigned int guess(std::string);
    std::string randomWord();
};
#endif /* defined(__JottoGame__jotto_model__) */
