#include <cstdlib>

template <typename DATA>
class binaryTreeNode {
public:
	binaryTreeNode(DATA data) {
		this->left = NULL;
		this->right = NULL;
		this->data = new DATA(data);
	}

	~binaryTreeNode() {
		if(this->right != NULL) delete this->right;
		if(this->left != NULL) delete this->left;
		delete this->data;
		this->left = NULL;
		this->right = NULL;
		this->data = NULL;
	}

	DATA* data;
	binaryTreeNode<DATA>* left;
	binaryTreeNode<DATA>* right;
};