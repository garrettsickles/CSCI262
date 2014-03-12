#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "book.h"
#include "reader.h"

static const int RATINGS_COUNT = 6;
static const int RATINGS[RATINGS_COUNT] = {-5, -3, 0, 1, 3, 5};
static const std::string RATINGS_DESCRIPTION[RATINGS_COUNT] = {"Hated it!", "Didn\'t like it.", "Haven\'t read it.", "It was OK.", "Liked it.", "Loved it!"};

class library {
private:
	std::vector<book*> catalog;
	std::vector<reader*> directory;
	std::unordered_map<std::string, int> catalog_index;
	std::unordered_map<std::string, int> directory_index;

	bool loadReaders(std::string);
	bool loadBooks(std::string);

	void saveReaders(std::string);
	void saveBooks(std::string);
public:
	library();
	~library();

	bool load(std::string, std::string);
	void save(std::string, std::string);
	void clear();

	int catalogSize();
	int directorySize();

	void printReaders();
	void printBooks();

	bool isBook(std::string, std::string);
	int findBook(std::string, std::string);
	std::pair<std::string, std::string> getBook(int);
	int addBook(std::string, std::string);
	void deleteBook(std::string, std::string);

	bool isReader(std::string);
	int findReader(std::string);
	std::string getReader(int);
	int addReader(std::string);
	void deleteReader(std::string);

	int getRating(int, int);
	int getRatingIndex(int, int);
	std::string getRatingDescription(int, int);
	bool setRating(int, int, int);
	bool setRatingIndex(int, int, int);

	std::stack<std::pair<std::string, int> > getRecommendations(int);
};
