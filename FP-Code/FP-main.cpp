#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <fstream>
#include <vector>
#include "stdlib.h" // for the system command

using namespace std;


class TreeNode {

public:
	int key;
	string animal_name;
	TreeNode *leftChild;
	TreeNode *rightChild;
	TreeNode *parent;


	TreeNode(int key, string val, TreeNode *parent = NULL, TreeNode *left = NULL, TreeNode *right = NULL) {
		this->key = key;
		this->animal_name = val;
		this->leftChild = left;
		this->rightChild = right;
		this->parent = parent;
	}

	TreeNode *hasLeftChild() {
		return this->leftChild;
	}

	TreeNode *hasRightChild() {
		return this->rightChild;
	}

	bool isLeftChild() {
		return this->parent && this->parent->leftChild == this;
	}

	bool isRightChild() {
		return this->parent && this->parent->rightChild == this;
	}

	bool isRoot() {
		return !this->parent;
	}

	bool isLeaf() {
		return !(this->rightChild || this->leftChild);
	}

	bool hasAnyChildren() {
		return this->rightChild || this->leftChild;
	}

	bool hasBothChildren() {
		return this->rightChild && this->leftChild;
	}

	void spliceOut() {
		if (this->isLeaf()) {
			if (this->isLeftChild()) {
				this->parent->leftChild = NULL;
			}
			else {
				this->parent->rightChild = NULL;
			}
		}
		else if (this->hasAnyChildren()) {
			if (this->hasLeftChild()) {
				if (this->isLeftChild()) {
					this->parent->leftChild = this->leftChild;
				}
				else {
					this->parent->rightChild = this->rightChild;
				}
				this->leftChild->parent = this->parent;
			}
			else {
				if (this->isLeftChild()) {
					this->parent->leftChild = this->rightChild;
				}
				else {
					this->parent->rightChild = this->rightChild;
				}
				this->rightChild->parent = this->parent;
			}
		}
	}

	TreeNode *findSuccessor() {
		TreeNode *succ = NULL;
		if (this->hasRightChild()) {
			succ = this->rightChild->findMin();
		}
		else {
			if (this->parent) {
				if (this->isLeftChild()) {
					succ = this->parent;
				}
				else {
					this->parent->rightChild = NULL;
					succ = this->parent->findSuccessor();
					this->parent->rightChild = this;
				}
			}
		}
		return succ;
	}

	TreeNode *findMin() {
		TreeNode *current = this;
		while (current->hasLeftChild()) {
			current = current->leftChild;
		}
		return current;
	}

	void replaceNodeData(int key, string value, TreeNode *lc = NULL, TreeNode *rc = NULL) {
		this->key = key;
		this->animal_name = value;
		this->leftChild = lc;
		this->rightChild = rc;
		if (this->hasLeftChild()) {
			this->leftChild->parent = this;
		}

		if (this->hasRightChild()) {
			this->rightChild->parent = this;
		}
	}
	void preorder() {
		cout << this->key << endl;
		if (this->leftChild) {
			this->leftChild->preorder();
		}
		if (this->rightChild) {
			this->rightChild->preorder();
		}
	}
};


class BinarySearchTree {

private:
	TreeNode *root;
	int size;

	void _put(int key, string val, TreeNode *currentNode) {
		if (key < currentNode->key) {
			if (currentNode->hasLeftChild()) {
				this->_put(key, val, currentNode->leftChild);
			}
			else {
				currentNode->leftChild = new TreeNode(key, val, currentNode);
			}
		}
		else {
			if (currentNode->hasRightChild()) {
				this->_put(key, val, currentNode->rightChild);
			}
			else {
				currentNode->rightChild = new TreeNode(key, val, currentNode);
			}
		}
	}

	TreeNode  *_get(int key, TreeNode *currentNode) {
		if (!currentNode) {
			return NULL;
		}
		else if (currentNode->key == key) {
			return currentNode;
		}
		else if (key < currentNode->key) {
			return this->_get(key, currentNode->leftChild);
		}
		else {
			return this->_get(key, currentNode->rightChild);
		}
	}

	TreeNode  *_getleft(int key, TreeNode *currentNode) {
		if (!currentNode) {
			return NULL;
		}
		else if (currentNode->key == key) {
			TreeNode *leftNode = currentNode->leftChild;
			return leftNode;
		}
		else if (key > currentNode->key) {
			return this->_getleft(key, currentNode->rightChild);
		}
		else if (key < currentNode->key) {
			return this->_getleft(key, currentNode->leftChild);
		}
	}

	TreeNode  *_getright(int key, TreeNode *currentNode) {
		if (!currentNode) {
			return NULL;
		}
		else if (currentNode->key == key) {
			TreeNode *rightNode = currentNode->rightChild;
			return rightNode;
		}
		else if (key > currentNode->key) {
			return this->_getright(key, currentNode->rightChild);
		}
		else if (key < currentNode->key) {
			return this->_getright(key, currentNode->leftChild);
		}
	}

public:
	BinarySearchTree() {
		this->root = NULL;
		this->size = 0;
	}

	int length() {
		return this->size;
	}

	void put(int key, string val) {
		if (this->root) {
			this->_put(key, val, this->root);
		}
		else {
			this->root = new TreeNode(key, val);
		}
		this->size = this->size + 1;
	}

	string get(int key) {
		if (this->root) {
			TreeNode *res = this->_get(key, this->root);
			if (res) {
				return res->animal_name;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	string get_left(int key) {
		// New method we will use to get the left node
		// We need to access the left child, and then call _get()
		if (this->root) {
			TreeNode *res = this->_getleft(key, this->root);
			if (res) {
				return res->animal_name;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	string get_right(int key) {
		// New method we will use to get the right node
		if (this->root) {
			TreeNode *res = this->_getright(key, this->root);
			if (res) {
				return res->animal_name;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}


	void del(int key) {
		if (this->size > 1) {
			TreeNode *nodeToRemove = this->_get(key, this->root);
			if (nodeToRemove) {
				this->remove(nodeToRemove);
				this->size = this->size - 1;
			}
			else {
				cerr << "Error, key not in tree" << endl;
			}
		}
		else if (this->size == 1 && this->root->key == key) {
			this->root = NULL;
			this->size = this->size - 1;
		}
		else {
			cerr << "Error, key not in tree" << endl;
		}
	}

	void remove(TreeNode *currentNode) {
		if (currentNode->isLeaf()) { //leaf
			if (currentNode == currentNode->parent->leftChild) {
				currentNode->parent->leftChild = NULL;
			}
			else {
				currentNode->parent->rightChild = NULL;
			}
		}
		else if (currentNode->hasBothChildren()) { //interior
			TreeNode *succ = currentNode->findSuccessor();
			succ->spliceOut();
			currentNode->key = succ->key;
			currentNode->animal_name = succ->animal_name;
		}
		else { // this node has one child
			if (currentNode->hasLeftChild()) {
				if (currentNode->isLeftChild()) {
					currentNode->leftChild->parent = currentNode->parent;
					currentNode->parent->leftChild = currentNode->leftChild;
				}
				else if (currentNode->isRightChild()) {
					currentNode->leftChild->parent = currentNode->parent;
					currentNode->parent->rightChild = currentNode->leftChild;
				}
				else {
					currentNode->replaceNodeData(currentNode->leftChild->key,
						currentNode->leftChild->animal_name,
						currentNode->leftChild->leftChild,
						currentNode->leftChild->rightChild);

				}
			}
			else {
				if (currentNode->isLeftChild()) {
					currentNode->rightChild->parent = currentNode->parent;
					currentNode->parent->leftChild = currentNode->rightChild;
				}
				else if (currentNode->isRightChild()) {
					currentNode->rightChild->parent = currentNode->parent;
					currentNode->parent->rightChild = currentNode->rightChild;
				}
				else {
					currentNode->replaceNodeData(currentNode->rightChild->key,
						currentNode->rightChild->animal_name,
						currentNode->rightChild->leftChild,
						currentNode->rightChild->rightChild);
				}
			}
		}
	}
	
	/*void preorder(){
		root.preorder();
			}
	*/
	void fill_tree(string questions_filename, string number_filename)
	{
		ifstream questions(questions_filename);
		ifstream numbers(number_filename);
		string line;
		int readint;
		int linecount = 0;
		vector <string> questionvect;
		vector <int> numbersvect;
		//int x = numbersvect.size();
		questionvect.reserve(32);
		numbersvect.reserve(32);



		if (!questions.is_open() || !numbers.is_open()) {
			cout << " Error opening file. " << endl;
		}

		for (unsigned int i = 0; i <= 31; ++i) {
			getline(questions, line);
			//cout << line << endl;
			questionvect.push_back(line);
		}

		for (unsigned int i = 0; i <= 31; ++i) {
			numbers >> readint;
			//cout << readint << endl;
			numbersvect.push_back(readint);
		}

		for (unsigned int i = 0; i <= 31; ++i) {
			int num = numbersvect[i];
			string ques = questionvect[i];
			put(num, ques );
		
		}
		questions.close();
		numbers.close();
	}
};

int main() {

	BinarySearchTree *mytree = new BinarySearchTree();
	mytree->fill_tree("questions_filename.txt", "numbers_filename.txt");
	//cout << mytree -> root << endl;
	/*for (int i = 1, i < mytree.length, ++i);
	cout << mytree << endl;
	
*/
	int num = 4;
	string x = mytree->get(num);
	string y = mytree->get_left(num);
	string z = mytree->get_right(num);
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	cin.get();
	return 0;
}
