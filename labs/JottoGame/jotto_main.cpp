//
//  main.cpp
//  JottoGame
//
//  Created by Garrett Frank Sickles on 9/12/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "jotto_model.h"

int main() {
    jotto_model newGame("jwords.txt");
    
    newGame.play();
}