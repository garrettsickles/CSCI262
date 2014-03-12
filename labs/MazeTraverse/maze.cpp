//
//  maze.cpp
//  MazeTransverse
//
//  Created by Garrett Frank Sickles on 10/7/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "maze.h"

maze::maze(std::string filename) {
	map = NULL;
	reset();
	load(filename);
}

maze::~maze() {
    reset();
}

bool maze::load(std::string filename) {    
    mapFile.open(filename.c_str());
    if(!mapFile.is_open() || !(mapFile >> type >> rows >> columns)) {
		std::cerr << "Error Opening " << filename.c_str() << "\nPlease input a valid filename!!!\n";
        reset();
        mapFile.close();
        return(false);
    }
    else {
        map = new char*[rows];
        for(unsigned int i = 0; i < rows; i++) {
            map[i] = new char[columns];
            for(int j = 0; j < columns; j++) {
                mapFile >> map[i][j];
                if(map[i][j] == MAZE_START) {
                    start.row       = i + 1;
                    start.column    = j + 1;
                }
            }
        }
        mapFile.close();
        return(true);
    }
}

void maze::display() {
    if(mapLoaded()) {
        for(unsigned int i = 0; i < this->rows; i++) {
            for(unsigned int j = 0; j < this->columns; j++) {
                std::cout << this->map[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void maze::reset() {
    if(mapLoaded()) {
        for(int i = 0; i < this->rows; i++)
            delete[] this->map[i];
        delete[] this->map;
    }
    this->map = NULL;
    this->type = '\0';
    this->rows = 0;
    this->columns = 0;
}

void maze::setElement(maze::point p, char c) {
    if(p.valid())   map[p.row - 1][p.column - 1] = c;
}

char maze::getElement(maze::point p) {
    if(p.valid())    return(map[p.row - 1][p.column - 1]);
}

bool maze::validElement(maze::point p) {
    if(p.valid() && p.row <= rows && p.column <= columns)   return(getElement(p) == MAZE_PATH);
    else    return(false);
}

bool maze::mapLoaded() {
    return(this->map != '\0');
}

maze::point::point() {
    maze::point::row    = 0;
    maze::point::column = 0;
}

maze::point::point(unsigned int r, unsigned int c) {
    if(r > 0 && c > 0) {
        maze::point::row    = r;
        maze::point::column = c;
    }
    else {
        maze::point::row    = 0;
        maze::point::column = 0;
    }
}

void maze::traverse() {
    bool solved = false;
    unsigned int moves = 0;
    maze::point buffer;

	mapPathPush(start);
    std::cin.ignore();
    while(!mapPathEmpty()) {
        buffer = mapPathGetNext();
        moves++;
		if(!(buffer == start))	setElement(buffer, MAZE_VISITED);
		this->display();
		std::cout << "Hit the return key to procede...\n";
        std::cin.ignore();
        if(getElement(buffer.up()) == MAZE_FINISH || getElement(buffer.down()) == MAZE_FINISH || getElement(buffer.left()) == MAZE_FINISH || getElement(buffer.right()) == MAZE_FINISH) {
            while(!mapPathEmpty())
                mapPathRemoveNext();
            solved = true;
            std::cout << "Movements Made:\t" << moves << std::endl;
            break;
        }
		mapPathRemoveNext();
        if(validElement(buffer.up()))     mapPathPush(buffer.up());
        if(validElement(buffer.down()))   mapPathPush(buffer.down());
        if(validElement(buffer.left()))   mapPathPush(buffer.left());
        if(validElement(buffer.right()))  mapPathPush(buffer.right());
    }
    if(solved)
		std::cout << "Succesfully completed the maze!!!\n";
	else
		std::cout << "Failed to complete the maze...\n";
}

//	Method to check whether or not the map path data structure is empty
bool maze::mapPathEmpty() {
	if(type == 's')	return(mapStack.empty());
	else if(type = 'q')	return(mapQueue.empty());
	else	return(true);
}

//	Method to remove next element in map path data structure
void maze::mapPathRemoveNext() {
	if(type == 's')	mapStack.pop();
	else if(type = 'q')	mapQueue.pop();
	else	return;
}

//	Method to push next element on map path data structure
void maze::mapPathPush(maze::point p) {
	if(type == 's')	mapStack.push(p);
	else if(type = 'q')	mapQueue.push(p);
	else	return;
}
//	Method to get next point in map path data structure
maze::point maze::mapPathGetNext() {
	if(type == 's')	return(mapStack.top());
	else if(type = 'q')	return(mapQueue.front());
	else	return(point());
}