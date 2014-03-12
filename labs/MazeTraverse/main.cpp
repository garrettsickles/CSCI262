//
//  main.cpp
//  MazeTransverse
//
//  Created by Garrett Frank Sickles on 10/7/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include <iostream>
#include <string>

#include "maze.h"

using namespace std;

int main()
{
	string filename;

    cout << "========== Welcome to Maze Solver ==========" << endl << endl;
    cout << "Please enter the filename of your Maze data file: ";
    cin >> filename;

	maze myMaze(filename);
    myMaze.traverse();
    
    return 0;
}

