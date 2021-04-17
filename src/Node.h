#pragma once

// This is the Node object class for the AVL tree.

#include <iostream>
#include <string>
#include <map>
using namespace std;

class Node {
public:
	int date;
	map<string, int> assignments;
	Node* left;
	Node* right;

	Node(int date, map<string, int> assignments, Node* left, Node* right) {
		this->date = date;
		this->assignments = assignments;
		this->left = left;
		this->right = right;
	}
};