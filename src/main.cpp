#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Node.h"
#include "Tree.h"
using namespace std;

void getData() { //pass in a set as reference

    ifstream inFile;
    inFile.open("data.csv");
    string tempLine;
    getline(inFile, tempLine);

    // make a map to use for making the nodes
    string tempCode;
    string tempAssignment;
    while (!inFile.eof()) {

        getline(inFile, tempCode, ',');

        for (int i = 0; i < 25; i++) {

            getline(inFile, tempAssignment, ',');
            // continue from here

        }

    }



}

int main() {

    // make a set
    getData();
    return 0;

}