#include "TwentyQuestions.h"

const std::string QUESTION = "#Q";
const std::string ANSWER = "#A";
const std::string YES = "Yes";
const std::string NO = "No";

void TwentyQuestions::loadPreorder(binaryTreeNode<std::string>** node) {
	inputFile >> buffer;
	inputFile.ignore();
	if(buffer == QUESTION) {
		getline(inputFile, buffer);
		*node = new binaryTreeNode<std::string>(buffer);
		loadPreorder(&(*node)->left);
		loadPreorder(&(*node)->right);
	}
	else if(buffer == ANSWER) {
		getline(inputFile, buffer);
		*node = new binaryTreeNode<std::string>(buffer);
	}
}

void TwentyQuestions::savePreorder(binaryTreeNode<std::string>** node) {
	if((*node) != NULL) {
		if((*node)->left == NULL && (*node)->right == NULL) {
			outputFile << ANSWER << ' ' << *((*node)->data) << '\n';
		}
		else {
			outputFile << QUESTION << ' ' << *((*node)->data) << '\n';
			savePreorder(&(*node)->left);
			savePreorder(&(*node)->right);
		}
	}
}

TwentyQuestions::TwentyQuestions(std::string filename) {
	load(filename);
}

TwentyQuestions::~TwentyQuestions() {
	delete root;
}

bool TwentyQuestions::load(std::string filename) {
	inputFile.open(filename);
	if(!inputFile.is_open()) {
		std::cerr << "Error opening file " << filename << ".\nNow exiting...\n";
		return(false);
	}
	loadPreorder(&root);
	inputFile.close();
	return(true);
}

bool TwentyQuestions::play() {
	char answer;
	binaryTreeNode<std::string>* node = this->root;
	if(this->root == NULL) {
		std::cerr << "No game file loaded!\n Please load a valid file then try again.\nNow exiting gameplay...\n";
		return(false);
	}
	while(node->left != NULL && node->right != NULL) {
		std::cout << *(node->data) << "(y/n): ";
		question.push(*(node->data));
		std::cin >> answer;
		if(answer == 'n' || answer == 'N') {
			this->answer.push(YES);
			node = node->right;
		}
		else if(answer == 'y' || answer == 'Y') {
			this->answer.push(NO);
			node = node->left;
		}
		else {
			std::cout << "Please enter a valid choice. (y/n)\n";
		}
	}
	std::cout << *(node->data) << "(y/n): ";
	question.push(*(node->data));
	std::cin >> answer;
	if(answer == 'n' || answer == 'N') {
		std::cout << "BOO! I don't know!\n";
		this->answer.push(NO);
		std::cout << "Would you like to expand the game tree (y/n)?: ";
		std::cin >> answer;
		if(answer == 'y' || answer == 'Y') {
			ammend(&node);
		}
		else if(answer == 'n' || answer == 'N') {
			std::cout << "Okay then...\nThanks for playing!\n";
		}
	}
	else if(answer == 'y' || answer == 'Y') std::cout << "YAY! I guessed your animal!\n";
	else std::cout << "Hmmmm...\nI am not sure what's going on but good game!\n";
	return(true);
}

bool TwentyQuestions::ammend(binaryTreeNode<std::string>** node) {
	(*node)->right = new binaryTreeNode<std::string>((*(*node)->data));
	std::cout << "I asked the following:\n";
	while(!answer.empty() && !question.empty()) {
		std::cout << question.front() << ' ' << answer.front() << '\n';
		question.pop();
		answer.pop();
	}
	getline(std::cin, buffer);
	std::cout << "Enter a new animal in the form of a question,\ne.g., 'Is it a whale?':\n";
	getline(std::cin, buffer);
	(*node)->left = new binaryTreeNode<std::string>(buffer);
	std::cout << "Now enter a question for which the answer is 'yes' for your new animal, and which does not contradict your previous answers:\n";
	getline(std::cin, buffer);
	*((*node)->data) = buffer;
	return(true);
}

bool TwentyQuestions::save(std::string filename) {
	outputFile.open(filename);
	savePreorder(&root);
	outputFile.close();
	return(true);
}