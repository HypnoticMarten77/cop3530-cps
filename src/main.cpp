#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include "Node.h"
#include "Tree.h"
using namespace std;

void getData(map<string, Tree>& trees) {

    ifstream inFile;
    inFile.open("data.csv");

    while (!inFile.eof()) {

        string semesterName;
        string tempLine;
        getline(inFile, semesterName, ',');
        getline(inFile, tempLine);


        Tree newTree;
        for (int j = 0; j < 50; j++) {

            getline(inFile, tempLine);

            int pos = 0;
            string course;
            while ((pos = tempLine.find(",")) != string::npos) {
                course = tempLine.substr(0, pos);
                // cout << course << endl;     //To test fetching course code, can be deleted.
                tempLine.erase(0, pos + 1);
                break;
            }

            pos = 0;
            int pos2 = 0;
            int newDate = 0;
            string inDate = "";
            string number = "";
            string outDate = "";
            bool success;

            while ((pos = tempLine.find(",")) != string::npos) {
                inDate = tempLine.substr(0, pos);
                number = outDate = "";

                for (int i = 0; i < 2; i++) {
                    size_t pos2 = inDate.find("/");
                    if ((i == 1) && (stoi(inDate.substr(0, pos2)) < 10)) {
                        number = number + "0" + inDate.substr(0, pos2);
                    }
                    else {
                        number += inDate.substr(0, pos2);
                    }
                    inDate.erase(0, pos2 + 1);
                }

                outDate = number + inDate;
                tempLine.erase(0, pos + 1);

                newDate = stoi(outDate);
                map<string, int> blank = {{}};
                success = false;

                if (newTree.searchNode(newTree.root, newDate) == nullptr)
                    newTree.root = newTree.insert(newTree.root, newDate, blank, success);

                Node *node = newTree.searchNode(newTree.root, newDate);
                node->assignments[course]++;
            }

            //This section is here because there is no comma following the last date in the line, so we need to perform the previous actions one more time.
            number = outDate = "";

            for (int i = 0; i < 2; i++) {
                size_t pos2 = tempLine.find("/");
                if ((i == 2) && (stoi(tempLine.substr(0, pos2)) < 10)) {
                    number = number + "0" + tempLine.substr(0, pos2);
                }
                else {
                    number += tempLine.substr(0, pos2);
                }
                tempLine.erase(0, pos2 + 1);
            }

            outDate = number + tempLine;
            newDate = stoi(outDate);
            map<string, int> blank = {{}};
            success = false;

            if (newTree.searchNode(newTree.root, newDate) == nullptr)
                newTree.root = newTree.insert(newTree.root, newDate, blank, success);

            Node *node = newTree.searchNode(newTree.root, newDate);
            node->assignments[course]++;

        }

        //This is where we add the tree to the map.
        trees.insert(pair<string, Tree>(semesterName, newTree));
        getline(inFile, tempLine);
        getline(inFile, tempLine);

    }

}

int main() {

    map<string, Tree> trees;
    getData(trees);

    return 0;

}