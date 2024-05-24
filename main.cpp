//Firaol Berehanu
//
//Red Black Tree - mde for inserting nodes into a tree with color cordiantion
/* I used  the follwiong for help:
                             https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
                        https://en.wikipedia.org/wiki/Tree_rotation
I also got help from my uncle for traversting the tree
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

//Color codes
#define RESET "\033[0m"
#define RED   "\033[31m"
#define BLUE  "\033[34m" //Substitute for black

using namespace std;
 
struct Branch { //Helper structure for printing
    Branch* previous;
    char* str;

    Branch(Branch* previous, char* str) {
        this->previous = previous;
        this->str = str;
    }
};

void showBranches(Branch* p) { //Helper function for printing
    if (p == NULL)
        return;

    showBranches(p->previous);

    cout << p->str;



}


void insertNode(Node*& root, Node*& current, Node*& parent, int value);
void printTree(Node* root, Branch* previous, bool isLeft);
void parseInput(char* input, int* values, int& count);
void fileInsert(Node*& root);

void balanceTree(Node*& root, Node*& current);
void rotateLeft(Node*& root, Node*& current);
void rotateRight(Node*& root, Node*& current);

int main() {
    cout << "Red-Black Tree: Insertion" << endl << endl;
    bool running = true;
    char command[15];
    Node* root = NULL;
    while (running) {
        cout << "Options: Add, FileAdd, Print, Quit" << endl;
        cin.get(command, 15);
        cin.clear();
        cin.ignore(10000, '\n');
        if (strcmp(command, "Add") == 0) { //Manually add a value to the tree
            int value;
            cout << "Add value >> ";
            cin >> value;
            cin.clear();
            cin.ignore(10000, '\n');
            Node* current = root;
            Node* parent = NULL;
            insertNode(root, current, parent, value);
            if (current != root) {
                balanceTree(root, current);
            }
            cout << endl << value << " added to tree." << endl << endl;
        }
        else if (strcmp(command, "FileAdd") == 0) { //Add values from a file
            fileInsert(root);
        }
        else if (strcmp(command, "Print") == 0) { //Print the tree
            cout << endl;
            printTree(root, NULL, false);
            cout << endl;
        }
        else if (strcmp(command, "Quit") == 0) { //Exit the program
            cout << endl << "Exiting Red-Black Tree: Insertion Edition" << endl;
            running = false;
        }
        else {
            cout << "Invalid input, try again." << endl << endl;
        }
    }
}

void insertNode(Node*& root, Node*& current, Node*& parent, int value) { //Insert a node manually
    if (root == NULL) {
        root = new Node();
        current = root;
        root->setData(value);
        root->setColor(0); //Root is always black
    }
    else {
        if (value < current->getData()) {
            parent = current;
            current = current->getLeft();
            if (current == NULL) {
                current = new Node();
                current->setData(value);
                parent->setLeft(current);
                current->setParent(parent);
                balanceTree(root, current);
                return;
            }
            else {
                insertNode(root, current, parent, value);
            }
        }
        else {
            parent = current;
            current = current->getRight();
            if (current == NULL) {
                current = new Node();
                current->setData(value);
                parent->setRight(current);
                current->setParent(parent);
                balanceTree(root, current);
                return;
            }
            else {
                insertNode(root, current, parent, value);
            }
        }
    }
}
void printTree(Node* root, Branch* previous, bool isLeft) { //Print the tree
    if (root == NULL) {
        return;
    }
    char* prevStr = (char*)("    ");
    Branch* branch = new Branch(previous, prevStr);
    printTree(root->getLeft(), branch, true);
    //Formatting tree
    if (!previous) {
        branch->str = (char*)("---");
    }
    else if (isLeft) {
        branch->str = (char*)(".---");
        prevStr = (char*)("   |");
    }
    else {
        branch->str = (char*)("'---");
        previous->str = prevStr;
    }
    showBranches(branch);
    if (root->getColor() == 0) { //if Black
        cout << BLUE << root->getData() << RESET << endl;
    }
    else { //Red
        cout << RED << root->getData() << RESET << endl;
    }
    if (previous) {
        previous->str = prevStr;
    }
    branch->str = (char*)("   |");
    printTree(root->getRight(), branch, false);
}

void parseInput(char* input, int* values, int& count) { //Parse input string into integer values
    int x = 0;  //keeps track of # of chars before space
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {
            if (x == 1) {
                int temp = 0;
                temp = input[i - 1] - '0';
                values[count] = temp;
                count++;
                x = 0;
            }
            else {
                int temp = 0;
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (input[i - x + a] - '0');
                }
                values[count] = temp;
                count++;
                x = 0;
            }
        }
        else {
            int temp = 0;
            x++;
            if (i == strlen(input) - 1) {  //last possible pair of chars
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (input[i + a + 1 - x] - '0');
                }
                values[count] = temp;
                count++;
            }
        }
    }
}
void fileInsert(Node*& root) { //Insert nodes from a file
    char input[10000];
    char fileName[100];
    int values[100];
    int valueCount = 0;
    int count = 0;
    memset(input, 0, 10000);
    memset(fileName, 0, 100);
    memset(values, 0, 100);

    cout << endl << "Enter the file name: ";
    cin.get(fileName, 30);
    cin.clear();
    cin.ignore(100000, '\n');
    streampos size;
    ifstream file(fileName, ios::in | ios::binary | ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        file.seekg(0, ios::beg);
        file.read(input, size);
        file.close();
        parseInput(input, values, count); //Parse input into values array
        cout << "Input: ";
        for (int i = 0; i < 100; i++) {
            if (values[i] != 0) {
                cout << values[i] << " ";
                valueCount++;
            }
        }
        cout << endl << "Count: " << valueCount << endl;
        Node* current = NULL;
        Node* parent = NULL;
        for (int i = 0; i < valueCount; i++) {
            if (values[i] == 0) break;
            current = root;
            insertNode(root, current, parent, values[i]);
        }
    }
}

