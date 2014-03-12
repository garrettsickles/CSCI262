#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
class binary_tree_node {
	public:
		binary_tree_node(T);
		~binary_tree_node();
		T data;
		binary_tree_node<T>* left;
		binary_tree_node<T>* right;
};

template <class T>
binary_tree_node<T>::binary_tree_node(T data) {
	this->data = data;
	left = NULL;
	right = NULL;	
}

template <class T>
binary_tree_node<T>::~binary_tree_node() {
	
}

template <class T>
void print_preorder(binary_tree_node<T>* root) {
	if (root != NULL) {
		cout << (*root).data << ' ';
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

template <class T>
void print_inorder(binary_tree_node<T>* root) {
	if(root != NULL) {
		print_inorder(root->left);
		cout << (*root).data << ' ';
		print_inorder(root->right);
	}
}

template <class T>
void print_postorder(binary_tree_node<T>* root){
	if(root != NULL) {
		print_postorder(root->left);
		print_postorder(root->right);
		cout << (*root).data << ' ';
	}
}

int main(){

	binary_tree_node<int>* r = new binary_tree_node<int>(42);		// level 0
	r->left = new binary_tree_node<int>(31);					// level 1
	r->right = new binary_tree_node<int>(22);
	r->left->left = new binary_tree_node<int>(55);			// level 2
	r->left->right = new binary_tree_node<int>(32);
	r->right->left = new binary_tree_node<int>(77);
	r->right->right = new binary_tree_node<int>(1);

	cout << "Expected:\t42 31 55 32 22 77 1" << endl << "Actual:\t\t";
	print_preorder(r);
	cout << endl << "Expected:\t55 31 32 42 77 22 1" << endl << "Actual:\t\t";
	print_inorder(r);
	cout << endl << "Expected:\t55 32 31 77 1 22 42" << endl << "Actual:\t\t";
	print_postorder(r);
	cout << endl;


}