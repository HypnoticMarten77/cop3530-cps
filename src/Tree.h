#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Node.h"
using namespace std;

//This is the Tree object class.  Contains constructors and all relevant Tree functions.
//This was based off Andres' AVL Tree project AVL class.

class Tree {
private:
	//Private functions for tree balancing.
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);
	Node* rotateLeftRight(Node* node);
	Node* rotateRightLeft(Node* node);

public:
	Node* root;

	//Tree object constructor.
	Tree() {
		root = nullptr;
	}

	//Function prototypes.  These are mostly based off Andres' AVL Tree project functions.
	Node* insert(Node* node, int date, map<string, int> assignments, bool& success);
	map<string, int> searchMap(Node* node, int date);
	Node* searchNode(Node* node, int date);
	void printAssignments(Node* node, int date);
	int getHeight(Node* node);
	int getBalanceFactor(Node* node);
};

//Performs a left rotation at the given node.
Node* Tree::rotateLeft(Node* node) {
	Node* node2 = node->right;
	node->right = node2->left;
	node2->left = node;
	return node2;
}

//Performs a right rotation at the given node.
Node* Tree::rotateRight(Node* node) {
	Node* node2 = node->left;
	node->left = node2->right;
	node2->right = node;
	return node2;
}

//Performs a left-right rotation at the given node by performing a left rotation
//at the left child, then right rotates the current node.
Node* Tree::rotateLeftRight(Node* node) {
	Node* node2 = node->left;
	node->left = rotateLeft(node2);
	return rotateRight(node);
}

//Performs a right-left rotation at the given node by performing a right rotation
//at the right child, then left rotates the current node.
Node* Tree::rotateRightLeft(Node* node) {
	Node* node2 = node->right;
	node->right = rotateRight(node2);
	return rotateLeft(node);
}

//Inserts a new node with the given date and assignment list. Also takes in a bool
//that determines if it was successful. Also performs balancing by checking balance
//factor at the node and its children.
Node* Tree::insert(Node* node, int date, map<string, int> assignments, bool& success) {
	if (node == nullptr) {
		node = new Node(date, assignments, nullptr, nullptr);
		success = true;
		return node;
	}
	if (date < node->date)
		node->left = insert(node->left, date, assignments, success);
	else if (date > node->date)
		node->right = insert(node->right, date, assignments, success);

	if (getBalanceFactor(node) == 2 && getBalanceFactor(node->left) == 1)
		node = rotateRight(node);
	else if (getBalanceFactor(node) == -2 && getBalanceFactor(node->right) == -1)
		node = rotateLeft(node);
	else if (getBalanceFactor(node) == -2 && getBalanceFactor(node->right) == 1)
		node = rotateRightLeft(node);
	else if (getBalanceFactor(node) == 2 && getBalanceFactor(node->left) == -1)
		node = rotateLeftRight(node);

	return node;
}

//Searches the tree with the given node for a node that matches the given date, and
//returns the assignment map associated with it. If for some reason no node was
//found, returns an invalid map.
map<string, int> Tree::searchMap(Node* node, int date) {
	if (node == nullptr)
		return { {"INVALID", 99} };
	else if (node->date == date)
		return node->assignments;
	else if (date < node->date)
		return searchMap(node->left, date);
	else
		return searchMap(node->right, date);
}

//Searches the tree with the given node for a node that matches the given date and
//returns it. If a node is not found with the given date, return nullptr.
Node* Tree::searchNode(Node* node, int date) {
	if (node == nullptr)
		return nullptr;
	else if (node->date == date)
		return node;
	else if (date < node->date)
		return searchNode(node->left, date);
	else
		return searchNode(node->right, date);
}

//Prints all assignments from a node with the given date. Calls searchMap to find the
//map, then iterate through it to show all assignments.
void Tree::printAssignments(Node* node, int date) {
	map<string, int> list = searchMap(node, date);

	if (list.empty() == true) {
		cout << "There are no assignments due on this day." << endl;
		return;
	}
	if (list.find("INVALID") != list.end()) {
		cout << "This date could not be found in the database." << endl;
	}
	else {
		for (auto it = list.begin(); it != list.end(); it++)
			cout << it->first << ": " << it->second << " assignment(s)" << endl;
	}
}

//Gets the height of a given node.
int Tree::getHeight(Node* node) {
	int height = 0;
	if (node != nullptr)
		height = 1 + (max(getHeight(node->left), getHeight(node->right)));
	return height;
}

//Gets the balance factor of a given node.
int Tree::getBalanceFactor(Node* node) {
	return (getHeight(node->left) - getHeight(node->right));
}