//
//  linkedList.h
//  JottoGame
//
//  Created by Garrett Frank Sickles on 9/11/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#ifndef __JottoGame__linkedList__
#define __JottoGame__linkedList__

#include <iostream>

typedef std::string linkedListData;

class linkedList {
private:
    class node {
        friend class linkedList;
        friend class iterator;
    private:
        node* next;
        node* previous;
        linkedListData _data;
    public:
        node(linkedListData);
        ~node();
    };
    
    class iterator {
    public:
        friend class linkedList;
        friend class node;
        iterator(node*);
        ~iterator();
        
        node* operator ++();
        node* operator --();
        
        node* get();
        void set(node*);
    private:
        node* current;
    };
    
    unsigned int nodeCount;
	node* _head;
    node* _tail;
    
public:
	linkedList();
	linkedList(const linkedList& source);
    ~linkedList();
    
	void operator =(const linkedList& source);
    linkedListData at(node*);
    linkedListData operator [](node*);
    linkedListData at(unsigned int);
    linkedListData operator [](unsigned int);
    
    void insert(linkedListData, node*, node*);
	void insert_at_head(linkedListData);
	void insert_at_tail(linkedListData);
    
    void remove(node*);
    void remove(unsigned int);
	void remove_from_head();
	void remove_from_tail();
    
    unsigned int size();
};

#endif /* defined(__JottoGame__linkedList__) */
