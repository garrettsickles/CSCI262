//
//  list.cpp
//  ICA4
//
//  Created by Garrett Frank Sickles on 9/6/13.
//  Copyright (c) 2013 Garrett Frank Sickles. All rights reserved.
//

#include "list.h"

list::list(void) {
    this->_data = nullptr;
    this->resize(DEFAULT_CAPACITY);
	this->_size = 0;
}

list::list(size_t initialCapacity) {
    this->_data = nullptr;
    this->resize(initialCapacity);
	this->_size = 0;
}

list::list(const list& copy) {
    this->_data = nullptr;
	*this = copy;
}

list::~list() {
    if(this->_data != nullptr)
        delete[] this->_data;
}

list& list::operator =(const list& copy) {
    this->resize(copy._size);
	for(size_t i = 0; i < this->_capacity; i++) {
        this->_data[i] = copy._data[i];
        this->_size++;
    }
    return *this;
}

size_t list::size() {
    return(this->_size);
}

char list::get(size_t position) {
	if(position < this->_size)
		return(this->_data[position]);
	else {
		cout << "Please enter a valid position!\n";
        return('\0');
    }
}

void list::add(char c) {
	++this->_size;
    if(this->_size == this->_capacity)
        this->resize(++this->_capacity);
    this->_data[this->_size - 1] = c;
}

void list::insert(char c, size_t position) {
    ++this->_size;
    if(this->_size < _capacity && position < _capacity) {
        for(size_t i = this->_size; i > position; i--)
            this->_data[i] = this->_data[i - 1];
        this->_data[position] = c;
    }
    else {
        cout << "Please enter a valid position!\n";
        --this->_size;
    }
}

void list::erase(size_t position) {
	if(this->_size > 0 && position < _capacity) {
		for(size_t i = position; i < this->_size; i++) {
            this->_data[i] = this->_data[i + 1];
        }
        --this->_size;
	}
	else {
        cout << "Please enter a valid position!\n";
    }
}

void list::print() {
	for (int i = 0; i < this->size(); i++) {
		cout << this->get(i);
	}
	cout << endl;
}

void list::resize(size_t newCapacity) {
    char* temp;
    this->_size > newCapacity ? this->_size = newCapacity : 0 ;
    this->_capacity = newCapacity;
    if((this->_data) != nullptr) {
        temp = new char[this->_capacity];
        for(size_t i = 0; i < this->_size; i++)
            temp[i] = this->_data[i];
        delete[] this->_data;
        this->_data = new char[this->_capacity];
        for(size_t i = 0; i < this->_size; i++)
            this->_data[i] = temp[i];
        delete[] temp;
    }
    else
        this->_data = new char[this->_capacity];
}

int list::menu() {
    int choice, position;
    char c;
    
    this->menuItems.push_back("Get a character at a specified index");
    this->menuItems.push_back("Add a character to the end of the list");
    this->menuItems.push_back("Insert a character into the list at a specific position");
    this->menuItems.push_back("Erase a character from the list at a specific position");
    this->menuItems.push_back("Print the current character list");
    this->menuItems.push_back("Exit");
    
    while (1) {
        cout << "\n--------- Menu ---------\n";
        for(int i = 0; i < this->menuItems.size(); i++) {
            cout << (i + 1) << ":\t" << this->menuItems[i] << endl;
        }
        cout << "------------------------\nChoice:\t";
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "Get the character at position...\n";
                cin >> position;
                cout << "The character at position " << position << " is...\n" << "'" << get(position) << "'\n";
                break;
            case 2:
                cout << "At the end of the list add...\n";
                cin >> c;
                add(c);
                cout << "The character '" << c << "' was added to the end of the list\n";
                break;
            case 3:
                cout << "At position...\n";
                cin >> position;
                cout << "Add the character...\n";
                cin >> c;
                insert(c, position);
                cout << "The character '" << c << "' was inserted at the position " << position << endl;
                break;
            case 4:
                cout << "Erase the character at position...\n";
                cin >> c;
                erase(c);
                cout << "The character '" << c << "' at position " << position << " was erased\n";
                break;
            case 5:
                cout << "Printing the list...\n";
                this->print();
                break;
            case 6:
                return(-1);
                break;
            default:
                return(-1);
        }
    }
}