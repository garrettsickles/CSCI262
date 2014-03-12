#pragma once

#include <string>
#include <unordered_map>

#include "book.h"

class book;

class reader
{
	friend class library;
private:
	std::string name;

	std::unordered_map<book*, int> books;

public:
	reader(std::string);
	~reader();

	std::string getName();
};
