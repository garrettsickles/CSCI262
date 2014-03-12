#pragma once

#include <string>
#include <unordered_set>

#include "reader.h"

class reader;

class book
{
	friend class library;
private:
	std::string author;
	std::string title;

	std::unordered_set<reader*> readers;

public:
	book(std::string, std::string);
	~book();

	std::string getAuthor();
	std::string getTitle();
};
