//
//  list.h
//  ICA5
//
//  Created by Garrett Frank Sickles on 9/10/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __ICA5__list__
#define __ICA5__list__

#pragma once

#include "node.h"
#include <iostream>

class list {
    
public:
	list();
	~list();
	list(const list& source);
	void operator =(const list& source);
	void insert_at_head(char to_add);
	void insert_at_tail(char to_add);
	void insert(char to_insert, int position);
	void remove_from_head();
	void remove_from_tail();
	void erase(int position);
	char get(int position);
	void print_list();
	void print_structure();
    
private:
	node* _head;
    node* _tail;
};
#endif /* defined(__ICA5__list__) */
