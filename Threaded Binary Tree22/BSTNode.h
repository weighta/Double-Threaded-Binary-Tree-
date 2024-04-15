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

	unsigned char isChild_Bitfield; // 0th bit left, 1st bit right
	//no use of struct or further dependencies required here

public:
	// Two constructors -- with and without initial values
	BSTNode() {
		lc = rc = NULL;
		isChild_Bitfield = 0;
	}
	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL) {
		k = K;
		it = e;
		lc = l;
		rc = r;
		isChild_Bitfield = 0;
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
		return !(isChild_Bitfield & 0x3);
	}
	bool isMaxed() {
		return ((isChild_Bitfield & 0x3) == 0x3);
	}

	// Additional getters and setters
	bool leftIsChild() const {
		return isChild_Bitfield & 0x1; //Anding the 0th bit will tell us if left has child
	}
	bool rightIsChild() const {
		return isChild_Bitfield & 0x2; //Anding the 1st bit will tell us if the right has a child
	}
	void setLeftIsChild(char a) {
		isChild_Bitfield |= 0x1; //Set 0th bit to 1 to signify left pointer is now a child
	}
	void setRightIsChild(char a) {
		isChild_Bitfield |= 0x2; //Set 1st bit to 1 to signify right pointer is now a child
	}
};

#endif