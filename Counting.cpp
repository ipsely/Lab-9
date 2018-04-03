#include <iostream>
using namespace std;

struct node{
	int data;
	node *parent;
	node *leftChild;
	node *rightChild;
	//Constructor
	node() {
		parent = leftChild = rightChild = NULL;
	}
};

class binaryTree{
public:
	node *root;
	binaryTree() {
		root = NULL;
	}
	void insert(int value);
	void remove(int value);
	void display(node *temp);
	node* leftMostNode(node *temp);
	node* rightMostNode(node *temp);
	node* search(int value, node *temp);
};

node* binaryTree::leftMostNode(node *temp) {
	if (temp->leftChild == NULL) {
		return temp;
	}
	else {
		return leftMostNode(temp->leftChild);
	}
}

node* binaryTree::rightMostNode(node *temp) {
	if (temp->rightChild == NULL) {
		return temp;
	}
	else {
		return leftMostNode(temp->rightChild);
	}
}

//insert() function
void binaryTree::insert(int value) {
	node *temp = new node;
	temp->data = value;
	if (root == NULL) {
		root = temp;
	}
	else {
		node *pointer = root;
		while (temp->parent == NULL) {
			if (value <= pointer->data) {
				if (pointer->leftChild != NULL) {
					pointer = pointer->leftChild;
				}
				else {
					pointer->leftChild = temp;
					temp->parent = pointer;
				}
			}
			else {
				if (pointer->rightChild != NULL) {
					pointer = pointer->rightChild;
				}
				else {
					pointer->rightChild = temp;
					temp->parent = pointer;
				}
			}
		}
	}
}

//display() function
void binaryTree::display(node *temp) {
	if (temp != NULL) {
		display(temp->leftChild);
		cout << temp->data << " ";
		display(temp->rightChild);
	}
}

node* binaryTree::search(int value, node *temp) {
	if (temp != NULL) {
		if (temp->data == value) {
			cout << "Found";
			return temp;
		}
		else {
			if (temp->data > value) {
				return search(value, temp->leftChild);
			}
			else {
				return search(value, temp->rightChild);
			}
		}
	}
	else {
		cout << "Not found";
		return NULL;
	}
}

//remove() or delete() function
void binaryTree::remove(int value) {
	node* temp = search(value, root);
	if (temp == NULL) {
		return;
	}
	node* baap = temp->parent;
	//Three cases:
	if (baap != NULL) {
		//When a leaf needs to be removed...
		if (temp->leftChild == NULL && temp->rightChild == NULL) {
			if (value < baap->data)
				baap->leftChild = NULL;
			else
				baap->rightChild = NULL;
			temp->parent = NULL;
			delete temp;
		}
		//When an internal node needs to be removed...
		else {
			if (value < baap->data) {
				if (temp->rightChild != NULL && temp->leftChild != NULL) {
					baap->leftChild = temp->leftChild;
					temp->leftChild->parent = baap;
					node* junction = rightMostNode(temp->leftChild);
					temp->rightChild->parent = junction;
					junction->rightChild = temp->rightChild;
				}
				else if (temp->rightChild == NULL && temp->leftChild != NULL) {
					baap->leftChild = temp->leftChild;
					temp->leftChild->parent = baap;
				}
				else {
					baap->leftChild = temp->rightChild;
					temp->rightChild->parent = baap;
				}
			}
			else {
				if (value > baap->data) {
					if (temp->rightChild != NULL && temp->leftChild != NULL) {
						baap->rightChild = temp->leftChild;
						temp->leftChild->parent = baap;
						node* junction = rightMostNode(temp->leftChild);
						temp->rightChild->parent = junction;
						junction->rightChild = temp->rightChild;
					}
					else if (temp->rightChild == NULL && temp->leftChild != NULL) {
						baap->rightChild = temp->leftChild;
						temp->leftChild->parent = baap;
					}
					else {
						baap->rightChild = temp->rightChild;
						temp->rightChild->parent = baap;
					}
				}
			}
		}
	}
}

int main() {
	binaryTree treeOne;
	treeOne.insert(5);
	treeOne.insert(6);
	treeOne.insert(3);
	treeOne.insert(8);
	treeOne.display(treeOne.root);
	cout << endl;
	treeOne.remove(9);
	treeOne.display(treeOne.root);
	cout << endl;
	return 0;
}

