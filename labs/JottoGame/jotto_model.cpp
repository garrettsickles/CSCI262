//
//  jotto_model.cpp
//  JottoGame
//
//  Created by Garrett Frank Sickles on 9/12/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "jotto_model.h"

jotto_model::jotto_model() {
    this->guessCount = 0;
}

jotto_model::jotto_model(std::string filename) {
    this->guessCount = 0;
    this->loadWords(filename);
}

jotto_model::~jotto_model() {
    
}

unsigned int jotto_model::commmonLetters(std::string first, const std::string second) {
    unsigned int common = 0;
    std::string bcopy(second);
    for(unsigned int i = 0; i < first.size(); i++) {
        for(unsigned int j = 0; j < bcopy.size(); j++) {
            if(first[i] == bcopy[j]) {
                common++;
                bcopy[j] = '*';
                break;
            }
        }
    }
    return(common);
}

void jotto_model::eleminateWords(unsigned int common, std::string guess) {
    for(unsigned int i = 0; i < this->words.size(); i++) {
        if(common != this->commmonLetters(this->words[i], guess)) {
            this->words.remove(i);
            i--;
        }
    }
}

void jotto_model::setSecretWord() {
    srand((unsigned int)time(NULL));
    this->secretWord = this->words[rand() % this->words.size()];
}

bool jotto_model::loadWords(std::string filename) {
    std::ifstream input(filename);
    std::string buffer;
    this->filename = filename;
    if(!input.is_open()) {
        std::cout << "Error opening '" << filename << "'...\nExiting Jotto...\n";
        return(false);
    }
    else {
        while(input >> buffer)
            this->words.insert_at_head(buffer);
        return(true);
    }
	input.close();
}

std::string jotto_model::randomWord() {
    srand((unsigned int)time(NULL));
    unsigned int random = rand() % this->words.size();
    return(this->words[random]);
}

void jotto_model::play() {
    int choice = 0;
    unsigned int common = 0;
    int difficulty = 0;
    int maxGuessCount = 0;
    std::string guess;
    
    std::cout << "\n-----------------\nLet's play Jotto!\n-----------------\n";
    
    while(1) {
        if(!this->loadWords(this->filename))
            return;
		this->guessCount = 0;
        std::cout << "\nWho will be guessing this game?\n[1]\tComputer\n[2]\tHuman\n[3]\tQuit Game\nChoice:\t";
        std::cin >> choice;
        if(choice == 1) {
            std::cout << "Can you outsmart the Computer?\n";
            char yesno;
            
            while(this->words.size() > 0) {
                guess = this->randomWord();
                
                std::cout << "My guess is " << guess << ". Is that right? (y/n) ";
                std::cin >> yesno;
                this->guessCount++;
                
                if (yesno == 'y' || yesno == 'Y') {
                    std::cout << "Great! I guessed your word in ";
                    std::cout << this->guessCount << " guesses!!!\n";
                    break;
                }
                std::cout << "How many letters are in common?: ";
                std::cin >> common;
                this->eleminateWords(common, guess);
            }
			if(yesno != 'y' && yesno != 'Y') {
				std::cout << "I give up...\nThere are " << this->words.size() << " words left!\n";
				std::cout << "The word is either not in my dictionary or you can't read/count.\n";
			}
        }
        else if(choice == 2) {
            while(difficulty < 1 || difficulty > 3) {
                std::cout << "What difficulty would you like?\n[1]\tEasy\n[2]\tMedium\n[3]\tHard\n";
                std::cin >> difficulty;
                if(difficulty == 1) {
                    std::cout << "You shouldn't have a problem.\n";
                    maxGuessCount = EASY;
                }
                else if(difficulty == 2) {
                    std::cout << "This will be an interesting game...\n";
                    maxGuessCount = MEDIUM;
                }
                else if(difficulty == 3) {
                    std::cout << "I wish you luck. You'll need it.\n";
                    maxGuessCount = HARD;
                }
                else
                    std::cout << "Really?\n1, 2, and 3 are your options\n";
            }
            std::cout << "I hope you know your " << LETTER_COUNT << " letter words!!!\n";
            this->setSecretWord();
            
            while (this->guessCount < maxGuessCount) {
                std::cout << "Take a guess (" << maxGuessCount - this->guessCount << " remaining): ";
                std::cin >> guess;
                common = this->commmonLetters(guess, this->secretWord);
                if (common == 6) {
                    std::cout << "5 letters in common\n";
                    std::cout << "The secret word is " << guess << ".\n";
                    std::cout << "You won!\n";
                    return;
                }
                else {
                    std::cout << common << " letters in common\n";
                }
                this->guessCount++;
            }
            std::cout << "The secret word is " << this->secretWord << ".\n";
            std::cout << "You lose!\n";
        }
        else if(choice == 3)
            return;
        else
            std::cout << "Come on...\nIt's simple. Enter '1','2', or '3'\n";
    }
}