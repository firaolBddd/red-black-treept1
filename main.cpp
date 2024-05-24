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

