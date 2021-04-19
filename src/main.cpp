#include <iostream>
#include <fstream>
#include <map>
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

            // this section fetches the source code
            int pos = 0;
            string course;
            while ((pos = tempLine.find(",")) != string::npos) {
                course = tempLine.substr(0, pos);
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

            // this loop is responsible for removing the '/' from the dates
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
                map<string, int> blank = { {} };
                blank.clear();
                success = false;

                // inserting the node for the data if it isn't already in the tree,
                if (newTree.searchNode(newTree.root, newDate) == nullptr)
                    newTree.root = newTree.insert(newTree.root, newDate, blank, success);

                // increments the count in the nodes map
                Node* node = newTree.searchNode(newTree.root, newDate);
                node->assignments[course]++;

            }

            //This section is here because there is no comma following the last date in the line, so we need to perform the previous actions one more time.
            number = outDate = "";

            for (int i = 0; i < 2; i++) {
                size_t pos2 = tempLine.find("/");
                if ((i == 1) && (stoi(tempLine.substr(0, pos2)) < 10)) {
                    number = number + "0" + tempLine.substr(0, pos2);
                }
                else {
                    number += tempLine.substr(0, pos2);
                }
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

        //This is where we add the tree to the map
        trees.insert(pair<string, Tree>(semesterName, newTree));
        getline(inFile, tempLine);
        getline(inFile, tempLine);

    }

    cout << "Done!\n" << endl;
}

// this function simply returns and int* that can be printed to output the passed in date
int* printDate(int date) {
    int* array = new int[8];
    int remainder;
    int i = 0;

    while (date != 0) {
        remainder = date % 10;
        array[i] = remainder;
        i++;
        date = date / 10;
    }

    return array;
}

// this function prints the dates of all of the nodes that have assignments due - it also utilizes preOrder traversal to do so
void listDates(Node* node) {
    if (node == nullptr)
        return;
    else {
        if (node->assignments.empty() == false) {
            int* a = printDate(node->date);
            if (to_string(node->date).length() == 7)
                cout << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << endl;
            else
                cout << a[7] << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << endl;
        }
        listDates(node->left);
        listDates(node->right);
    }
}

int main() {

    // introduction to the software
    map<string, Tree> trees;
    cout << "Course Planning Software v1.0" << endl;
    cout << "By: Andres Maldonado-Martin and David DeVore" << endl;
    cout << "=================================================================\n" << endl;
    
    cout << "Importing data from data.csv... ";
    getData(trees);
    cout << "Welcome to CPS! Use the commands below to perform your requested action.\n" << endl;
    int option;

    // this is the menu of options
    while (true) {
        cout << "1. Insert new date into the database" << endl;
        cout << "2. Insert new assignment for a given date" << endl;
        cout << "3. Remove an assignment from a given date" << endl;
        cout << "4. View assignment list for a given date" << endl;
        cout << "5. View dates with assignments due in a given semester" << endl;
        cout << "6. Exit\n" << endl;
        cout << "Your choice: ";
        cin >> option;
        
        string inputString, semester;
        int inputInt;
        bool success;

        switch (option) {

        // this is where we insert a new date into the database
        case 1:
            cout << "\nPlease input the semester you wish to add a date to. (Fall/Spring): ";
            cin >> inputString;
            semester = inputString + " Semester ";

            cout << "Please input the year for the semester. (YYYY): ";
            cin >> inputString;
            semester += inputString;

            if (trees.find(semester) == trees.end()) {
                cout << "\nThis semester does not exist.\n" << endl;
            }
            else {
                cout << "\nSemester found. Please input the date you would like to add. (MMDDYYYY): ";
                cin >> inputInt;

                if (trees[semester].searchNode(trees[semester].root, inputInt) != nullptr)
                    cout << "\nThis date already exists in this semester.\n" << endl;
                else {
                    success = false;
                    map<string, int> blank = { {} };
                    blank.clear();
                    trees[semester].root = trees[semester].insert(trees[semester].root, inputInt, blank, success);
                    if (success) {
                        int* a = printDate(inputInt);
                        if (to_string(inputInt).length() == 7)
                            cout << "\nThe date " << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << " was added to " << semester << "!\n" << endl;
                        else
                            cout << "\nThe date " << a[7] << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << " was added to " << semester << "!\n" << endl;
                    }
                }
            }
            break;

        // this is where we insert a new assignment for a given date
        case 2:
            cout << "\nPlease input the semester you wish to add an assignment to. (Fall/Spring): ";
            cin >> inputString;
            semester = inputString + " Semester ";

            cout << "Please input the year for the semester. (YYYY): ";
            cin >> inputString;
            semester += inputString;

            if (trees.find(semester) == trees.end()) {
                cout << "\nThis semester does not exist.\n" << endl;
            }
            else {
                cout << "\nSemester found. Please input the date you would like to add an assignment to. (MMDDYYYY): ";
                cin >> inputInt;

                if (trees[semester].searchNode(trees[semester].root, inputInt) == nullptr)
                    cout << "\nThis date isn't in this semester. Please add it before adding an assignment.\n" << endl;
                else {
                    int* a = printDate(inputInt);
                    if (to_string(inputInt).length() == 7)
                        cout << "\nAssignment list for " << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << ": " << endl;
                    else
                        cout << "\nAssignment list for " << a[7] << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << ": " << endl;
                    trees[semester].printAssignments(trees[semester].root, inputInt);
                    cout << "\nPlease indicate which course you would like to add an assignment for. (XXX): ";
                    cin >> inputString;

                    trees[semester].searchNode(trees[semester].root, inputInt)->assignments[inputString]++;
                    cout << "\nAn assignment for " << inputString << " was added on this day.\n" << endl;
                }
            }
            break;

        // this is where we remove an assignment from a given date
        case 3:
            cout << "\nPlease input the semester you wish to remove an assignment from. (Fall/Spring): ";
            cin >> inputString;
            semester = inputString + " Semester ";

            cout << "Please input the year for the semester. (YYYY): ";
            cin >> inputString;
            semester += inputString;

            if (trees.find(semester) == trees.end()) {
                cout << "\nThis semester does not exist.\n" << endl;
            }
            else {
                cout << "\nSemester found. Please input the date you would like to remove an assignment from. (MMDDYYYY): ";
                cin >> inputInt;

                if (trees[semester].searchNode(trees[semester].root, inputInt) == nullptr)
                    cout << "\nThis date isn't in this semester. Please add it before removing an assignment.\n" << endl;
                else {
                    int* a = printDate(inputInt);
                    if (to_string(inputInt).length() == 7)
                        cout << "\nAssignment list for " << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << ": " << endl;
                    else
                        cout << "\nAssignment list for " << a[7] << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << ": " << endl;
                    trees[semester].printAssignments(trees[semester].root, inputInt);
                    Node* node = trees[semester].searchNode(trees[semester].root, inputInt);
                    if (node->assignments.empty() == false) {
                        cout << "\nPlease indicate which course you would like to remove an assignment from. (XXX): ";
                        cin >> inputString;


                        node->assignments[inputString]--;
                        cout << "\nAn assignment from " << inputString << " was removed from this day.\n" << endl;

                        int sum = 0;
                        for (auto it = node->assignments.begin(); it != node->assignments.end(); it++)
                            sum += it->second;

                        if (sum == 0)
                            node->assignments.clear();
                    }
                    else
                        cout << endl;

                }
            }
            break;

        // this is where we view the assignment list for a given date
        case 4:
            cout << "\nPlease input the semester of the date you wish to look at. (Fall/Spring): ";
            cin >> inputString;
            semester = inputString + " Semester ";

            cout << "Please input the year for the semester. (YYYY): ";
            cin >> inputString;
            semester += inputString;

            if (trees.find(semester) == trees.end()) {
                cout << "\nThis semester does not exist.\n" << endl;
            }
            else {
                cout << "\nSemester found. Please input the date you would like to view the assignment list for. (MMDDYYYY): ";
                cin >> inputInt;

                if (trees[semester].searchNode(trees[semester].root, inputInt) == nullptr)
                    cout << "\nThis date isn't in this semester. Please add it before viewing information regarding it.\n" << endl;
                else {
                    int* a = printDate(inputInt);
                    if (to_string(inputInt).length() == 7)
                        cout << "\nAssignment list for " << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << ": " << endl;
                    else
                        cout << "\nAssignment list for " << a[7] << a[6] << "/" << a[5] << a[4] << "/" << a[3] << a[2] << a[1] << a[0] << ": " << endl;
                    trees[semester].printAssignments(trees[semester].root, inputInt);
                    cout << endl;
                }
            }
            break;

        // this is where we view dates with assignments due in any given semester
        case 5:
            cout << "\nPlease input the semester of the you wish to look at. (Fall/Spring): ";
            cin >> inputString;
            semester = inputString + " Semester ";

            cout << "Please input the year for the semester. (YYYY): ";
            cin >> inputString;
            semester += inputString;

            if (trees.find(semester) == trees.end()) {
                cout << "\nThis semester does not exist.\n" << endl;
            }
            else {
                cout << "\nSemester found. Below are the dates that have assignments due: " << endl;
                listDates(trees[semester].root);
                cout << endl;
            }
            break;

        // finally, this is where we exit the program
        case 6:
            return 0;
        default:
            cout << "\nPlease make a valid selection.\n" << endl;
            break;
        }
    }

    return 0;

}