//
//  linkedList.cpp
//  JottoGame
//
//  Created by Garrett Frank Sickles on 9/11/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "linkedList.h"

linkedList::node::node(linkedListData newData) {
    next        = nullptr;
    previous    = nullptr;
    _data        = newData;
}

linkedList::node::~node() {
    
}

linkedList::iterator::iterator(linkedList::node* track) {
    this->set(track);
}

linkedList::iterator::~iterator() {
    
}

linkedList::node* linkedList::iterator::operator ++() {
    current = current->next;
    return(current);
}

linkedList::node* linkedList::iterator::operator--() {
    current = current->previous;
    return(current);
}

linkedList::node* linkedList::iterator::get() {
    return(current);
}

void linkedList::iterator::set(node* track) {
    current = track;
}

linkedList::linkedList() {
	_head = nullptr;
    _tail = nullptr;
    nodeCount = 0;
}

linkedList::linkedList(const linkedList& source){
	(*this) = source;
}

linkedList::~linkedList() {
	while(_head != nullptr)
        remove_from_head();
}

void linkedList::operator =(const linkedList& source) {
    iterator location(source._head);
    while(location.get() != nullptr) {
        insert_at_tail(location.get()->_data);
    }
}

linkedListData linkedList::operator[](linkedList::node* current) {
    return(current->_data);
}

linkedListData linkedList::operator[](unsigned int current) {
    iterator location(this->_head);
    for(size_t i = 0; i < current; i++)
        ++location;
    return(location.get()->_data);
}

linkedListData linkedList::at(linkedList::node* current) {
    return((*this)[current]);
}

linkedListData linkedList::at(unsigned int current) {
    return((*this)[current]);
}

void linkedList::insert(linkedListData to_insert, node* behind,  node* ahead) {
    node* newNode = new node(to_insert);
    
    newNode->next       = ahead;
    newNode->previous   = behind;
    newNode->next       == nullptr ? this->_tail = newNode : newNode->next->previous = newNode;
    newNode->previous   == nullptr ? this->_head = newNode : newNode->previous->next = newNode;
    nodeCount++;
}

void linkedList::insert_at_head(linkedListData to_insert){
    this->insert(to_insert, nullptr, this->_head);
}

void linkedList::insert_at_tail(linkedListData to_insert){
    this->insert(to_insert, this->_tail,nullptr);
}

void linkedList::remove(node* current) {
    if(current != nullptr) {
        current->next       == nullptr ? this->_tail = current->previous : current->next->previous = current->previous;
        current->previous   == nullptr ? this->_head = current->next : current->previous->next = current->next;
        delete current;
        nodeCount--;
    }
}

void linkedList::remove(unsigned int current) {
    iterator location(this->_head);
    for(size_t i = 0; i < current; i++)
        ++location;
    this->remove(location.get());
}

void linkedList::remove_from_head(){
    this->remove(this->_head);
}

void linkedList::remove_from_tail(){
    this->remove(this->_tail);
}

unsigned int linkedList::size() {
    return(this->nodeCount);
}