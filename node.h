//this is the node.h file for the setter and getters
//firaol 
#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  Node(); // Cnstructor
  ~Node(); // Destrctor

  // Geters
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  int getData();
  int getColor();

  // Settrs
  void setLeft(Node*);
  void setRight(Node*);
  void setParent(Node*);
  void setData(int);
  void setColor(int);
//leave this as private so the dont get messed up 
 private:
  Node* leftChild;
  Node* rightChild;
  Node* parentNode;
  int nodeData;
  int nodeColor; // 0 = black, 1 = red
};
#endif

