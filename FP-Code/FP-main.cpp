/**
L07: Game of War
enhancements by <cruzg>
Purpose: To create a War class that would work similar to the card game War.
The War class needed to be constructed using only stacks, queues, and deques.
This is the work of the authors: cruzg.
ASCII sign found at http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20 */


#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <string>
using namespace std;


class TreeNode {

public:
	int key;
	int payload;
	TreeNode *leftChild;
	TreeNode *rightChild;
	TreeNode *parent;

	TreeNode(int key, int val, TreeNode *parent = NULL, TreeNode *left = NULL, TreeNode *right = NULL) {
		this->key = key;
		this->payload = val;
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

	void replaceNodeData(int key, int value, TreeNode *lc = NULL, TreeNode *rc = NULL) {
		this->key = key;
		this->payload = value;
		this->leftChild = lc;
		this->rightChild = rc;
		if (this->hasLeftChild()) {
			this->leftChild->parent = this;
		}

		if (this->hasRightChild()) {
			this->rightChild->parent = this;
		}
	}
};


class BinarySearchTree {

private:
	TreeNode *root;
	int size;

	void _put(int key, int val, TreeNode *currentNode) {
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
		else if (key > currentNode->key) {
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

	void put(int key, int val) {
		if (this->root) {
			this->_put(key, val, this->root);
		}
		else {
			this->root = new TreeNode(key, val);
		}
		this->size = this->size + 1;
	}

	int get(int key) {
		if (this->root) {
			TreeNode *res = this->_get(key, this->root);
			if (res) {
				return res->payload;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	int get_left(int key) {
		// New method we will use to get the left node
		// We need to access the left child, and then call _get()
		if (this->root) {
			TreeNode *res = this->_getleft(key, this->root);
			if (res) {
				return res->payload;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	int get_right(int key) {
		// New method we will use to get the right node
		if (this->root) {
			TreeNode *res = this->_getright(key, this->root);
			if (res) {
				return res->payload;
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
			currentNode->payload = succ->payload;
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
						currentNode->leftChild->payload,
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
						currentNode->rightChild->payload,
						currentNode->rightChild->leftChild,
						currentNode->rightChild->rightChild);
				}
			}
		}
	}
};

int main() {

	BinarySearchTree *mytree = new BinarySearchTree();
	mytree->put(8, 8);
	mytree->put(4, 4);
	mytree->put(12, 12);
	mytree->put(2, 2);
	mytree->put(6, 6);
	mytree->put(10, 10);
	mytree->put(14, 14);
	mytree->put(1, 1);
	mytree->put(3, 3);
	mytree->put(5, 5);
	mytree->put(7, 7);
	mytree->put(9, 9);
	mytree->put(11, 11);
	mytree->put(13, 13);
	mytree->put(15, 15);

	cout << "Let's play the number guessing game!" << endl;
	cout << "\nThink of a number between 1-15. Then, using yes or no question we'll guess your number!" << endl;
	bool x = true;
	string answer = "something";
	string answertwo = "something";
	int currentnode = 8;
	char stopme;
	while (x == true) {
		cout << "Is your number " << currentnode << " (yes or no)?" << endl;
		cin >> answer;
		if (answer == "yes") {
			x = false;
		}
		else if (answer == "no") {
			cout << "Is your number higher or lower than " << currentnode << " (high or low)?" << endl;
			cin >> answertwo;
			if (answertwo == "high") {
				int rightnode = mytree->get_right(currentnode);
				currentnode = rightnode;
			}
			else if (answertwo == "low") {
				int leftnode = mytree->get_left(currentnode);
				currentnode = leftnode;
			}
		}
	}

	//cin.get();
	cout << "Wow, we're good. That'll be 20 Berea Bucks!" << endl;
	cin >> stopme;

	return 0;
}