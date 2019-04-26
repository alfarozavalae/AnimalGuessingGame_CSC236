/*-------------------------------------------------------------------------------
#Final Project: Animal Guessing Game Implementation
#
#Team name: <GEE>
#
#Teammates: Guillermo Cruz, Elaheh Jamali and Emely Alfaro
#
#Purpose: To use the base code about trees in order to create a game for a guessing name.
#
#Starting code taken from: http://cs.berea.edu/cppds/Trees/SearchTreeImplementation.html
#------------------------------------------------------------------------------*/

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
		/*This function will be used to get the left node of any given node.*/
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
		/*This function will be used to get the right node of any given node.*/
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

	TreeNode  *_getleftkey(int key, TreeNode *currentNode) {
		/*This function will be used to get the key of the left node of any given node.*/
		if (!currentNode) {
			return NULL;
		}
		else if (currentNode->key == key) {
			TreeNode *leftNode = currentNode->leftChild;
			return leftNode;
		}
		else if (key > currentNode->key) {
			return this->_getleftkey(key, currentNode->rightChild);
		}
		else if (key < currentNode->key) {
			return this->_getleftkey(key, currentNode->leftChild);
		}
	}

	TreeNode  *_getrightkey(int key, TreeNode *currentNode) {
		/*This function will be used to get the key of the right node of any given node.*/
		if (!currentNode) {
			return NULL;
		}
		else if (currentNode->key == key) {
			TreeNode *rightNode = currentNode->rightChild;
			return rightNode;
		}
		else if (key > currentNode->key) {
			return this->_getrightkey(key, currentNode->rightChild);
		}
		else if (key < currentNode->key) {
			return this->_getrightkey(key, currentNode->leftChild);
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
		/*This function will be used to call the function to retrive the left node, and then
		will return the string value of the left node.*/
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
		/*This function will be used to call the function to retrive the right node, and then
		will return the string value of the right node.*/
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

	int get_leftkey(int key) {
		/*This function will be used to call the function to retrive the key of the left node, and then
		will return the key value of the left node.*/
		if (this->root) {
			TreeNode *res = this->_getleftkey(key, this->root);
			if (res) {
				return res->key;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	int get_rightkey(int key) {
		/*This function will be used to call the function to retrive the key of the right node, and then
		will return the key value of the right node.*/
		if (this->root) {
			TreeNode *res = this->_getrightkey(key, this->root);
			if (res) {
				return res->key;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	void fill_tree(string questions_filename, string number_filename){
		/*This function will read two txtfiles, and use the files to fill the binary tree.
		The first file contains tha strings of the nodes, and the second file contains the
		key values of the nodes.*/
		ifstream questions(questions_filename);
		ifstream numbers(number_filename);
		string line;
		int readint;
		int linecount = 0;
		vector <string> questionvect;
		vector <int> numbersvect;
		questionvect.reserve(32);
		numbersvect.reserve(32);

		if (!questions.is_open() || !numbers.is_open()) {
			cout << " Error opening file. " << endl;
		}

		for (unsigned int i = 0; i <= 31; ++i) {
			getline(questions, line);
			questionvect.push_back(line);
		}

		for (unsigned int i = 0; i <= 31; ++i) {
			numbers >> readint;
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

	BinarySearchTree *mytree = new BinarySearchTree();  // We create an instance of the binary search tree class
	mytree->fill_tree("questions_filename.txt", "numbers_filename.txt");  //We call the method to fill the binary search try by giving it two txtfiles

	cout << "Welcome to the animal guessing game!" << endl;
	cout << "The rules are as follows:" << endl;
	cout << "\n1. From the following list, you will choose an animal: [Zebra], [Flamingo], [Penguin], [Rabbit], [Duck], [Squirrel], [Giraffe], [Shark], [Alligator], [Octopus], [Seal], [Bald Eagle], [Stork], [Panda], [Tiger]" << endl;
	cout << "2. You will answer yes or no to the following questions, and using your answers we will guess your animal!" << endl;
	cout << "\nReady? Let's play!" << endl;
	cout << "" << endl;

	char holdme;
	int key_num = 22;
	string node = mytree->get(key_num); // We get the root node of the tree
	string answer;
	string answer2;
	bool leaf = true;
	vector <string> leaf_animals{ "Zebra", "Flamingo", "Penguin","Rabbit", "Duck", "Squirrel", "Giraffe", "Shark", "Alligator", "Octopus", "Seal","Bald Eagle", "Stork","Panda", "Tiger" };

	while (leaf = true) {
		/*This if statement will run if we get to a node that contains an animal, because that node will be a leaf node and
		will need to be handled differently from a regular node.*/
		if (find(leaf_animals.begin(), leaf_animals.end(), node) != leaf_animals.end()) {
			cout << "Is your animal a(n) " << node << " ?" << endl;
			cin >> answer2;
			if (answer2 == "yes" || answer2 == "Yes") {
				cout << "Ha! We guessed it, thank you for playing!" << endl;
				break;
			}
			else if (answer2 == "no" || answer2 == "No") {
				cout << "Given your answers, we believe we guessed correctly. You will be fined for lying." << endl;
				break;
			}
		}
		/*This section of the while loop will run if the node does not contain an animal, because the node will not be a leaf
		node at this point so it needs to be handled differently.*/
		cout << node << endl;
		cin >> answer;
			if (answer == "yes" || answer == "Yes") {
				node = mytree->get_right(key_num);
				key_num = mytree->get_rightkey(key_num);
			}
			else if (answer == "no" || answer == "No") {
				node = mytree->get_left(key_num);
				key_num = mytree->get_leftkey(key_num);
			}
		}
	cout << "Thank you for playing. Close the window and try again later if you would like!" << endl;

	cin >> holdme;
	cin.get();
	return 0;
	}