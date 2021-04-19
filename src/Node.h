#pragma once
#include <iostream>
#include <string>
#include <map>
using namespace std;

//This is the Node object class for the Tree objects.
//This was based off of Andres' AVL Tree project Node class.

class Node {
public:
	int date;
	map<string, int> assignments;
	Node* left;
	Node* right;

	//Node object constructor.
	Node(int date, map<string, int> assignments, Node* left, Node* right) {
		this->date = date;
		this->assignments = assignments;
		this->left = left;
		this->right = right;
	}
};