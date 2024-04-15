// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include for access to the complete binary node
// template implementation

#include "book.h"
#include "BinNode.h"

#ifndef BSTNODE_H
#define BSTNODE_H

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
  Key k;                  // The node's key
  E it;                   // The node's value
  BSTNode* lc;            // predessor or left child
  BSTNode* rc;            // successor or right child

  char L_isChild;	  // Left
  char R_isChild;	  // Right


public:
  // Two constructors -- with and without initial values
  BSTNode() {
	  lc = rc = NULL;
  }
  BSTNode(Key K, E e, BSTNode* l =NULL, BSTNode* r =NULL) {
	  k = K;
	  it = e;
	  lc = l;
	  rc = r;
	  L_isChild = R_isChild = 0;
  }
  ~BSTNode() {}             // Destructor

  // Functions to set and return the value and key
  E& element() {
	  return it;
  }
  void setElement(const E& e) {
	  it = e;
  }
  Key& key() {
	  return k;
  }
  void setKey(const Key& K) {
	  k = K;
  }

  // Functions to set and return the children
  void setLeft(BinNode<E>* b) {
	  lc = (BSTNode*)b;
  }
  void setRight(BinNode<E>* b) {
	  rc = (BSTNode*)b;
  }
  inline BSTNode* left() const {
	  return lc;
  }
  inline BSTNode* right() const {
	  return rc;
  }

  // Return true if it is a leaf, false otherwise
  bool isLeaf() {
	  return !(L_isChild | R_isChild);
  }
  bool isMaxed() {
	  return L_isChild & R_isChild;
  }

  // Additional getters and setters
  int leftIsChild() const {
	  return L_isChild;
  }

  int rightIsChild() const {
	  return R_isChild;
  }
  void setLeftIsChild(char a) {
	  L_isChild = a;
  }
  void setRightIsChild(char a) {
	  R_isChild = a;
  }
};

#endif