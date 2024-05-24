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

