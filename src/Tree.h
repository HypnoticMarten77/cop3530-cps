#pragma once
#include <iostream>
#include <string>
#include <map>
#include "Node.h"
using namespace std;

class Tree {
private:
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);
	Node* rotateLeftRight(Node* node);
	Node* rotateRightLeft(Node* node);

public:
	Node* root;

	Tree() {
		root = nullptr;
	}

	Node* insert(Node* node, int date, map<string, int> assignments, bool& success);
	map<string, int> search(Node* node, int date);
	void printAssignments(Node* node, int date);
	int getHeight(Node* node);
	int getBalanceFactor(Node* node);
};

Node* Tree::rotateLeft(Node* node) {
	Node* node2 = node->right;
	node->right = node2->left;
	node2->left = node;
	return node2;
}

Node* Tree::rotateRight(Node* node) {
	Node* node2 = node->left;
	node->left = node2->right;
	node2->right = node;
	return node2;
}

Node* Tree::rotateLeftRight(Node* node) {
	Node* node2 = node->left;
	node->left = rotateLeft(node2);
	return rotateRight(node);
}

Node* Tree::rotateRightLeft(Node* node) {
	Node* node2 = node->right;
	node->right = rotateRight(node2);
	return rotateLeft(node);
}

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

map<string, int> Tree::search(Node* node, int date) {
	if (node == nullptr)
		return { {"INVALID", 99} };
	else if (node->date = date)
		return node->assignments;
	else if (date < node->date)
		return search(node->left, date);
	else
		return search(node->right, date);
}

void Tree::printAssignments(Node* node, int date) {
	map<string, int> list = search(node, date);

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

int Tree::getHeight(Node* node) {
	int height = 0;
	if (node != nullptr)
		height = 1 + (max(getHeight(node->left), getHeight(node->right)));
	return height;
}

int Tree::getBalanceFactor(Node* node) {
	return (getHeight(node->left) - getHeight(node->right));
}