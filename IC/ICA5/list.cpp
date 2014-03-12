//
//  list.cpp
//  ICA5
//
//  Created by Garrett Frank Sickles on 9/10/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "list.h"

#include "list.h"

list::list(){
	_head = nullptr;
    _tail = nullptr;
}

list::~list(){
	while(_head != nullptr)
        remove_from_tail();
}

list::list(const list& source){
	*this = source;
}

void list::operator =(const list& source){
    node* iterator = source._head;
    if(iterator != nullptr) {
        do {
            this->insert_at_head(iterator->_data);
            iterator = iterator->next;
        } while(iterator != nullptr);
    }
    
}

void list::insert_at_head(char to_add){
    
	// create a new node with to_add
    node* newNode = new node(to_add);
    
	// set the next of the new node to point to the current _head
    if(_head != nullptr)
        newNode->next = _head;
    
	// set _head to be the new node
    _head = newNode;
	// TODO
}

void list::insert_at_tail(char to_add){
    node* newNode = new node(to_add);
    node* iterator = _head;
    
    if(iterator != nullptr) {
        while(iterator->next != nullptr)
            iterator = iterator->next;
        iterator->next = newNode;
        newNode->next = nullptr;
    }
    else
        _head = newNode;
}

void list::insert(char to_insert, int position){
    node* newNode = new node(to_insert);
    node* iterator = _head;
    
    for(size_t i = 0; i < position; i++)
        iterator = iterator->next;
    
    newNode->next = iterator;
    iterator->next = newNode;
    
	// TODO
}

void list::remove_from_head(){
    node* buffer;
	// remove the first Node in the linked list
    buffer = _head;
    if(_head != nullptr && _head->next != nullptr) {
        _head = _head->next;
        delete buffer;
    }
    else if(_head != nullptr && _head->next == nullptr) {
        delete _head;
        _head = nullptr;
    }
    else;
	// TODO
}

void list::remove_from_tail(){
    
    node* iterator = _head;
    node* previousNode = nullptr;
    
    if(_head != nullptr && _head->next != nullptr) {
        while(iterator->next != nullptr) {
            previousNode = iterator;
            iterator = iterator->next;
        }
        delete iterator;
        previousNode->next = nullptr;
    }
    else if(_head != nullptr && _head->next == nullptr){
        delete _head;
        _head = nullptr;
    }
    else;
}

void list::erase(int position){
    node* iterator = _head;
    node* previousNode = nullptr;
    
    for(size_t i = 0; i < position; i++) {
        previousNode = iterator;
        iterator = iterator->next;
    }
    if(iterator != nullptr && iterator->next != nullptr) {
        previousNode->next = iterator->next;
        delete iterator;
    }
    else if(iterator != nullptr && iterator->next == nullptr) {
        previousNode->next = nullptr;
        delete iterator;
    }
    else;
}

char list::get(int position){
    node* iterator = _head;
    
    for(size_t i = 0; i < position; i++)
        iterator = iterator->next;
    return(iterator->_data);
	// TODO
}

void list::print_list(){
    
	node* current = _head;
	while(current != nullptr){
        std::cout << current->_data << std::endl;
		current = current->next;
	}
    std::cout << "----" << std::endl;
}

void list::print_structure(){
    
	node* current = _head;
    std::cout << "_head->";
	while(current != nullptr){
		if(current->next != nullptr)
			std::cout << "|" << current->_data << "|*|->";
		else
			std::cout << "|" << current->_data << "|/|";
		current = current->next;
	}
    std::cout << std::endl;
}