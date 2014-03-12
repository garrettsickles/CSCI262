#include "reader.h"

reader::reader(std::string name)
{
	this->name = name;
}

reader::~reader() {
}

std::string reader::getName()
{
	return name;
}