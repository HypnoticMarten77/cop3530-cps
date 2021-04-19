#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include "Node.h"
#include "Tree.h"
using namespace std;

void getData(set<Node*>& trees) {

    ifstream inFile;
    inFile.open("data.csv");
    string tempLine;
    getline(inFile, tempLine);

    Tree newTree;
    
    //Replace 49 with 50 for the correct number of courses.  FGZ is broken in the first semester for some reason.
    for (int j = 0; j < 49; j++) {
        getline(inFile, tempLine);

        int pos = 0;
        string course;
        while ((pos = tempLine.find(",")) != string::npos) {
            course = tempLine.substr(0, pos);
            cout << course << endl;     //To test fetching course code, can be deleted.
            tempLine.erase(0, pos + 1);
            break;
        }

        pos = 0;
        int pos2 = 0; int newDate = 0;
        string inDate, number, outDate;
        bool success;

        while ((pos = tempLine.find(",")) != string::npos) {
            inDate = tempLine.substr(0, pos);
            number = outDate = "";

            for (int i = 0; i < 2; i++) {
                size_t pos2 = inDate.find("/");
                number += inDate.substr(0, pos2);
                inDate.erase(0, pos2 + 1);
            }

            outDate = number + inDate;
            tempLine.erase(0, pos + 1);

            newDate = stoi(outDate);
            map<string, int> blank = { {} };
            success = false;

            if (newTree.searchNode(newTree.root, newDate) == nullptr)
                newTree.root = newTree.insert(newTree.root, newDate, blank, success);

            Node* node = newTree.searchNode(newTree.root, newDate);
            node->assignments[course]++;
        }

        //This section is here because there is no comma following the last date in the line, so we need to perform the previous actions one more time.
        number = outDate = "";

        for (int i = 0; i < 2; i++) {
            size_t pos2 = tempLine.find("/");
            number += tempLine.substr(0, pos2);
            tempLine.erase(0, pos2 + 1);
        }

        outDate = number + tempLine;
        newDate = stoi(outDate);
        map<string, int> blank = { {} };
        success = false;

        if (newTree.searchNode(newTree.root, newDate) == nullptr)
            newTree.root = newTree.insert(newTree.root, newDate, blank, success);

        Node* node = newTree.searchNode(newTree.root, newDate);
        node->assignments[course]++;
    }
    
    //This is where we would add the tree to the set.

}

int main() {

    set<Node*> trees;
    getData(trees);
    return 0;

}