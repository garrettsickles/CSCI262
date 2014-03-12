//
//  node.cpp
//  ICA5
//
//  Created by Garrett Frank Sickles on 9/10/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "node.h"

#include "node.h"

node::node(char to_add){
	next = nullptr;
	_data = to_add;
}

node::~node(){
	// There is currently no dynamic
	// memory to destruct.
}