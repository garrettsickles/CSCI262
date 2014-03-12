#include <iostream>
#include <fstream>
#include <queue>
#include "binaryTreeNode.hpp"

class TwentyQuestions {
private:
	std::queue<std::string> question;
	std::queue<std::string> answer;
	std::string buffer;
	std::ifstream inputFile;
	std::ofstream outputFile;
	binaryTreeNode<std::string>* root;

	void loadPreorder(binaryTreeNode<std::string>**);
	void savePreorder(binaryTreeNode<std::string>**);
public:
	TwentyQuestions(std::string);
	~TwentyQuestions();

	bool load(std::string);
	bool play();
	bool ammend(binaryTreeNode<std::string>**);
	bool save(std::string);
};

