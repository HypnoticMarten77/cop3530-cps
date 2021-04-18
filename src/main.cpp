#include <iostream>
#include <fstream>
using namespace std;

void getData() {

    ifstream inFile;
    inFile.open("data.csv");
    string tempLine;
    getline(inFile, tempLine);

}

int main() {

    getData();
    return 0;

}