//this is my node dot cpp for for complie all my 
//the vars this is th outline for all the headers in the node h

#include <iostream>
#include "node.h"

using namespace std;
//sett all the childern intaly to null
Node::Node() { //Constructor
  leftChild = NULL;
  rightChild = NULL;
  parentNode = NULL;
  nodeData = 0;
  nodeColor = 1;
}

Node::~Node() { //Destructor
  leftChild = NULL;
  rightChild = NULL;
  parentNode = NULL;
}

//Setters- this is all teh vars im setting-
void Node::setLeft(Node* newLeft) {
  leftChild = newLeft;
}

void Node::setRight(Node* newRight) {
  rightChild = newRight;
}

void Node::setParent(Node* newParent) {
  parentNode = newParent;
}

void Node::setData(int newData) {
  nodeData = newData;
}

void Node::setColor(int newColor) {
  nodeColor = newColor;
}

//Getters- make sure to add the returns later
Node* Node::getLeft() {
  return leftChild;
}

Node* Node::getRight() {
  return rightChild;
}

Node* Node::getParent() {
  return parentNode;
}

int Node::getData() {
  return nodeData;
}

int Node::getColor() {
  return nodeColor;
}

