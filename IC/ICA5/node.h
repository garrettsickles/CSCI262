//
//  node.h
//  ICA5
//
//  Created by Garrett Frank Sickles on 9/10/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __ICA5__node__
#define __ICA5__node__

#pragma once

#include <cstdlib>

class node{
    
    friend class list;
    
public:
	node(char to_add);
	~node();
    
private:
	node* next;
	char _data;
	// Note that our data could be anything we wanted
	// We just decided to make it a char for this node implementation
};

#endif /* defined(__ICA5__node__) */
