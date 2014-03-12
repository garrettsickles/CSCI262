#include "book.h"

book::book(std::string author, std::string title)
{
	this->author = author;
	this->title = title;
}

book::~book(){};

std::string book::getAuthor()
{
	return this->author;
}

std::string book::getTitle()
{
	return this->title;
}