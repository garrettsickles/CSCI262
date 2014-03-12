//
//  maze.h
//  MazeTransverse
//
//  Created by Garrett Frank Sickles on 10/7/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __MazeTransverse__maze__
#define __MazeTransverse__maze__

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

// Characters expected and used in Maze Traversing
const char MAZE_WALL	= '#';
const char MAZE_PATH	= '.';
const char MAZE_START	= 'o';
const char MAZE_FINISH	= '*';
const char MAZE_VISITED = '@';
const char MAZE_INVALID = '!';

class maze {
private:

    //  Implementation of the point class used to reference elements in the maze
    //  A valid point is one that refers to a row and column greater than or equal to 1
    class point {
    public:
        //  Instantiates point object and sets row and column to 0 indicating an invalid point
        point(); 
        //  Instantiates point object and sets row and column to specified values if they are valid                         
		point(unsigned int, unsigned int);
        
        //  Operator to check whether or not two points refer to the same row and column
        bool operator ==(point p)   {   return(row == p.row && column == p.column);    }

        //  Methods used to access neighboring elements
        //  If the point is invalid, the method will return the point (0,0)
        point up()      {   return(point(this->point::row - 1, this->point::column));   }
        point down()    {   return(point(this->point::row + 1, this->point::column));   }
        point left()    {   return(point(this->point::row, this->point::column - 1));   }
        point right()   {   return(point(this->point::row, this->point::column + 1));   }
        
        //  Method to check whether or not this point is valid or invalid
        bool valid()    {   return(this->point::row > 0 && this->point::column > 0);    }

        //  Method tho check whether or not this point neighbors (shares a side) with another point
        bool neighbor(point p)    {   return(*this == p.up() || *this == p.down() || *this == p.left() || *this == p.right()); }
        
        //  Variables storing the row and column of this point
        unsigned int row;
        unsigned int column;
    };
    
    //  Method to edit the maze map buffer by accesing a maze::point and setting it to a character value
    void setElement(maze::point, char);

    //  Method to access an element of the maze map buffer using a maze::point
    char getElement(maze::point);

    //  Method to check if the element of the maze at the maze::point reference is a valid maze charecter
    bool validElement(maze::point);
    
    //  Method to traverse through the maze map buffer using a stack (depth first search)
    bool stackTraverse();

    //  Method to traverse through the maze map buffer using a queue (breadth first search)
    bool queueTraverse();

	//	Method to check whether or not the map path data structure is empty
	bool mapPathEmpty();

	//	Method to remove next element in map path data structure
	void mapPathRemoveNext();

	//	Method to push next element on map path data structure
	void mapPathPush(maze::point);

	//	Method to get next point in map path data structure
	maze::point mapPathGetNext();

    //  Method to check whether or not the maze map buffer is validly filled from a maze map file stream
    bool mapLoaded();
    
    //  Variable storing the double pointer for the maze map buffer
    char**  map;

    //  Variable storing the type of maze tranverse method
	char    type;
	
    //  Variables storing the size of the maze map buffer
    unsigned int rows;
    unsigned int columns;
    
    //  Object storing the starting point in the maze
    point start;

    //  Object to extract a maze map from a sqpecified file
	std::ifstream       mapFile;

    //  Objects to manage the search path throuhg the maze map buffer
	std::stack<point>   mapStack;
	std::queue<point>   mapQueue;
    
public:
    // Instantiates a maze object with a given map file
    maze(std::string);
    
    // Destructor, nuf' said
    ~maze();

    // Reload a map file for the maze object into the buffer
    bool load(std::string);

    // Display an image of the maze buffer to the screen
    void display();

    // Resets the maze buffer to NULL, and rows and columns to 0
	void reset();

    // Traverses through the maze buffer, updating the map as it goes
    void traverse();
};

#endif /* defined(__MazeTransverse__maze__) */
