#include "library.h"

library::library()
{

}

library::~library()
{
	clear();
}

bool library::load(std::string book_file, std::string reader_file)
{
	return(loadBooks(book_file) && loadReaders(reader_file));
}

void library::save(std::string book_file, std::string reader_file)
{
	saveReaders(reader_file);
	saveBooks(book_file);
}

bool library::loadReaders(std::string filename)
{
	std::ifstream input(filename);
	if(!input.is_open()) {
		return false;
	}
	else {
		int j = 0;
		int rating = 0;
		std::string username;
		while(!input.eof()) {
			getline(input, username, '\n');
			j = addReader(username);
			for(int i = 0; i < catalog.size() && (input >> rating); i++) {
				if(rating != 0) {
					setRating(j, i, rating);
				}
			}
			input.ignore(255, '\n');
		}
		input.close();
		return true;
	}
}

bool library::loadBooks(std::string filename)
{
	std::ifstream input(filename);
	if(!input.is_open())
	{
		return false;
	}
	else
	{
		std::string author, title;
		int index = 0;
		while(input.good())
		{
			getline(input, author, ',' );
			getline(input, title, '\n' );
			addBook(author, title);
		}
		input.close();
		return true;
	}
}

void library::saveReaders(std::string filename)
{
	std::ofstream output(filename);
	if(!output.is_open())
	{
		return;
	}
	else
	{
		for(int i = 0; i < directory.size(); i++)
		{
			output << directory[i]->getName() << '\n';
			for(int j = 0; j < catalog.size(); j++)
			{
				output << getRating(i, j) << ' ';
			}
			if(i != directory.size() - 1)
			{
				output << '\n';
			}
		}
		output.close();
	}
}

void library::saveBooks(std::string filename)
{
	std::ofstream output(filename);
	if(!output.is_open())
	{
		return;
	}
	else
	{
		for(int i = 0; i < catalog.size(); i++)
		{
			output << catalog[i]->getAuthor() << ',' << catalog[i]->getTitle();
			if(i != catalog.size() - 1)
			{
				output << '\n';
			}
		}
		output.close();
	}
}

void library::clear()
{
	for(int i = 0; i < catalog.size(); i++)
	{
		delete catalog[i];
	}
	catalog.clear();
	for(int i = 0; i < directory.size(); i++)
	{
		delete directory[i];
	}
	directory.clear();
	catalog_index.clear();
	directory_index.clear();
}

int library::catalogSize()
{
	return catalog.size();
}

int library::directorySize()
{
	return directory.size();
}

void library::printReaders()
{
	for(int i = 0; i < directory.size(); i++)
	{
		std::cout << directory[i]->getName() << '\n';
	}
}
void library::printBooks()
{
	for(int i = 0; i < catalog.size(); i++)
	{
		std::cout << i << ": " << catalog[i]->getAuthor() << ", " << catalog[i]->getTitle() << '\n';
	}
}

bool library::isBook(std::string author, std::string title)
{
	return(catalog_index.find(author + title) != catalog_index.end());
}

int library::findBook(std::string author, std::string title)
{
	if(isBook(author, title))
		return catalog_index[author + title];
	else
		return -1;
}

std::pair<std::string, std::string> library::getBook(int id)
{
	if(id >= 0 && id < catalog.size())
	{
		return(std::pair<std::string, std::string>(catalog[id]->getAuthor(), catalog[id]->getTitle()));
	}
	else
	{
		return(std::pair<std::string, std::string>("INVALID", "INVALID"));
	}
}

int library::addBook(std::string author, std::string title)
{
	if(!isBook(author, title))
	{
		catalog_index[author + title] = catalog.size();
		catalog.push_back(new book(author, title));
		return(catalog.size() - 1);
	}
	else
	{
		return(findBook(author, title));
	}
}

void library::deleteBook(std::string author, std::string title)
{
	int index;
	if(isBook(author, title))
	{
		index = catalog_index[author + title];
		for(std::unordered_set<reader*>::iterator i = catalog[index]->readers.begin(); i != catalog[index]->readers.end(); i++)
		{
			(*i)->books.erase(catalog[index]);
		}
		delete catalog[index];
		catalog.erase(catalog.begin() + index);
		catalog_index.erase(author + title);
	}
}

bool library::isReader(std::string name)
{
	return(directory_index.find(name) != directory_index.end());
}

int library::findReader(std::string name)
{
	if(isReader(name))
	{
		return directory_index[name];
	}
	else
	{
		return -1;
	}
}

std::string library::getReader(int id)
{
	if(id >= 0 && id < directory.size())
	{
		return(directory[id]->getName());
	}
	else
	{
		return "INVALID";
	}
}

int library::addReader(std::string name)
{
	if(!isReader(name))
	{
		directory_index[name] = directory.size();
		directory.push_back(new reader(name));
		return(directory.size() - 1);
	}
	else
	{
		return -1;
	}
}

void library::deleteReader(std::string name)
{
	int index;
	if(isReader(name))
	{
		index = directory_index[name];
		for(std::unordered_map<book*, int>::iterator i = directory[index]->books.begin(); i != directory[index]->books.end(); i++)
		{
			i->first->readers.erase(directory[index]);
		}
		delete directory[index];
		directory.erase(directory.begin() + index);
		directory_index.erase(name);
	}
}

int library::getRating(int reader_id, int book_id)
{
	if(directory[reader_id]->books.find(catalog[book_id]) != directory[reader_id]->books.end())
		return(directory[reader_id]->books[catalog[book_id]]);
	else
		return(0);
}

int library::getRatingIndex(int reader_id, int book_id)
{
	int rating = getRating(reader_id, book_id);
	for(int i = 0; i < RATINGS_COUNT; i++)
	{
		if(rating == RATINGS[i])
		{
			return i;
		}
	}
}

std::string library::getRatingDescription(int reader_id, int book_id)
{
	return RATINGS_DESCRIPTION[getRatingIndex(reader_id, book_id)];
}
bool library::setRating(int reader_id, int book_id, int rating)
{
	if(reader_id >= 0 && book_id >= 0 && reader_id < directory.size() && book_id < catalog.size())
	{
		directory[reader_id]->books[catalog[book_id]] = rating;
		return(catalog[book_id]->readers.insert(directory[reader_id]).second);
	}
	else
	{
		return false;
	}
}

bool library::setRatingIndex(int reader_id, int book_id, int index)
{
	if(index >= 0 && index < RATINGS_COUNT)
	{
		return setRating(reader_id, book_id, RATINGS[index]);
	}
	else
	{
		return false;
	}
}

std::stack<std::pair<std::string, int> > library::getRecommendations(int id)
{
	int sim = 0;
	std::map<book*, int> numeric;
	std::multimap<int, book*> inverse;
	std::stack<std::pair<std::string, int> > matches;
	matches.push(std::pair<std::string, int>("No books Availiable.\nPlease rate more books.", 0));
	for(std::unordered_map<book*, int>::iterator i = directory[id]->books.begin(); i != directory[id]->books.end(); i++)
	{
		sim = 0;
		for(std::unordered_set<reader*>::iterator j = (i->first)->readers.begin(); j != (i->first)->readers.end(); j++)
		{
			sim = i->second * (*j)->books.at(i->first);
			if(sim > 0)
			{
				for(std::unordered_map<book*, int>::iterator k = (*j)->books.begin(); k != (*j)->books.end(); k++)
				{
					if(numeric.find(k->first) == numeric.end())
					{
						numeric[k->first] = 0;
					}
					numeric[k->first] += sim * k->second;
				}
			}
		}
	}
	matches.pop();
	for(std::map<book*, int>::iterator i = numeric.begin(); i != numeric.end(); i++)
	{
		inverse.insert(std::pair<int, book*>(i->second, i->first));
	}
	for(std::multimap<int, book*>::iterator i = inverse.begin(); i != inverse.end(); i++)
	{
		if(directory[id]->books.find(i->second) == directory[id]->books.end())
		{
			if(i->first > 0)
			{
				matches.push(std::pair<std::string, int>(i->second->getTitle() + " by " + i->second->getAuthor(), i->first));
			}
		}
	}
	return matches;
}