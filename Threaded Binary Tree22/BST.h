// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"
#include <string>
#include "macros.h"

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key,E> {
private:

  BSTNode<Key, E>* root;   // Root of the BST <-- This is NOOOTT an array
  int nodecount;         // Number of nodes in the BST

  BSTNode<Key, E>* findPredessor(const Key& k) {

      int key = (int)k;
      if (root == NULL) {
          return NULL;
      }
      BSTNode<Key, E>* currentNode = root;
      BSTNode<Key, E>* predessor = NULL;
      while (1) {
          if (currentNode->key() > key) { //if current node is greater
              if (currentNode->leftIsChild()) { //go to the left
                  if (currentNode->key() < key) {
                      predessor = currentNode;
                  }
                  currentNode = currentNode->left();
              }
              else {
                  return predessor;
              }
          }
          else { //else the node is smaller
              if (currentNode->rightIsChild()) {
                  if (currentNode->key() < key) {
                      predessor = currentNode;
                  }
                  currentNode = currentNode->right();
              }
              else {
                  return predessor;
              }
          }
      }
  }
  BSTNode<Key, E>* findSuccessor(const Key& k) {
      int key = (int)k;
      if (root == NULL) {
          return NULL; //tree doesnt exist, so terminate
      }

      BSTNode<Key, E>* currentNode = root;
      BSTNode<Key, E>* successor = NULL;
      while (1) {
          if (currentNode->key() > key) {
              if (currentNode->leftIsChild()) {
                  if (currentNode->key() > key) {
                      successor = currentNode;
                  }
                  currentNode = currentNode->left();
              }
              else {
                  return successor;
              }
          }
          else {
              if (currentNode->rightIsChild()) {
                  if (currentNode->key() > key) {
                      successor = currentNode;
                  }
                  currentNode = currentNode->right();
              }
              else {
                  return successor;
              }
          }
      }
  }


  void predsAndSuccs(BSTNode<Key, E>* root) {
      if (root->leftIsChild()) {
          predsAndSuccs(root->left());
      }
      if (root->rightIsChild()) {
          predsAndSuccs(root->right());
      }
      if ((int)root->key() == 79) {
          int b = 0;
      }
      if (!root->leftIsChild()) {
          root->setLeft(findPredessor(root->key()));
      }
      if (!root->rightIsChild()) {
          root->setRight(findSuccessor(root->key()));
      }
      int a = 0;
  }

  // Private "helper" functions
  void clearhelp(BSTNode<Key, E>*);
  void inserthelp(const Key&, const E&);
  BSTNode<Key,E>* deletemin(BSTNode<Key, E>*);
  BSTNode<Key,E>* getmin(BSTNode<Key, E>*);
  BSTNode<Key,E>* removehelp(BSTNode<Key, E>*, const Key&);
  E* findhelp(BSTNode<Key, E>*, const Key&) const;
  void printhelp(BSTNode<Key, E>*, int) const;
  void vist(BSTNode<Key, E>*) const;

public:

  BST() {
      root = NULL;
      nodecount = 0;
  }  // Constructor
  BST(const Key& k, const E& e) {
      insert(k, e);
  }
  
  //Note from Prof Sipantzi -- I've commented out the destructor
  //since you would have to change clearhelp() to make it work with
  //doubly-threaded trees and that is not part of the assignment.
  //~BST() { clearhelp(root); }            // Destructor

  void clear() {
      clearhelp(root);
      root = NULL;
      nodecount = 0;
  }

  // Insert a record into the tree.
  // k Key value of the record.
  // e The record to insert.
  void insert(const Key& k, const E& e) {
      inserthelp(k, e);
      nodecount++;
  }

  // Remove a record from the tree.
  // k Key value of record to remove.
  // Return: The record removed, or NULL if there is none.
  E* remove(const Key& k) {
    E* temp = findhelp(root, k);   // First find it
    if (temp != NULL) {
      root = removehelp(root, k);
      nodecount--;
    }
    return temp;
  }
  // Remove and return the root node from the dictionary.
  // Return: The record removed, null if tree is empty.
  E* removeAny() {  // Delete min value
    if (root != NULL) {
      E* temp = new E;
      *temp = root->element();
      root = removehelp(root, root->key());
      nodecount--;
      return temp;
    }
    else return NULL;
  }

  // Return Record with key value k, NULL if none exist.
  // k: The key value to find. */
  // Return some record matching "k".
  // Return true if such exists, false otherwise. If
  // multiple records match "k", return an arbitrary one.
  E* find(const Key& k) const {
      return findhelp(root, k);
  }

  // Return the number of records in the dictionary.
  int size() {
      return nodecount;
  }

  void preds() {
      predsAndSuccs(root);
  }

  // Print the contents of the BST
  void print() const {
    if (root == NULL) cout << "The BST is empty.\n";
    else printhelp(root, 0);
  }
};




// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key,E>* r) const {
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key, E>* root) {
  if (root == NULL) return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}

// Insert a node into the BST, returning the updated tree

template <typename Key, typename E>

void BST<Key, E>::inserthelp(const Key& k, const E& it) {

    if (root == NULL) { //the case where nothing exists
        root = new BSTNode<Key, E>(k, it, NULL, NULL);
        return;
    }

    BSTNode<Key, E>* currentNode = root;
    BSTNode<Key, E>* newNode = new BSTNode<Key, E>(k, it, NULL, NULL);
    char nodeNotPlanted = 1;
    while (nodeNotPlanted) {

        if (k < currentNode->key()) { //go left
            if (!currentNode->leftIsChild()) { //see if we're at a leaf
                //newNode->setRight(findSuccessor(newNode->key()));

                currentNode->setLeft(newNode);
                currentNode->setLeftIsChild(1);
                nodeNotPlanted = 0;
            }
            else { //otherwise we keep going
                currentNode = currentNode->left();
            }
        }
        else { //go right
            if (!currentNode->rightIsChild()) { //see if we're at a leaf
                //newNode->setLeft(findSuccessor(newNode->key()));
                currentNode->setRight(newNode);
                currentNode->setRightIsChild(1);
                nodeNotPlanted = 0;
            }
            else { //otherwise keep going
                currentNode = currentNode->right();
            }
        }
    }
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::getmin(BSTNode<Key, E>* rt) {
  if (!rt->left()) //jz
    return rt;
  else return getmin(rt->left());
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL) // Found min
    return rt->right();
  else {                      // Continue left
    rt->setLeft(deletemin(rt->left()));
    return rt;
  }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
  if (rt == NULL) return NULL;    // k is not in tree
  else if (k < rt->key())
    rt->setLeft(removehelp(rt->left(), k));
  else if (k > rt->key())
    rt->setRight(removehelp(rt->right(), k));
  else {                            // Found: remove it
    BSTNode<Key, E>* temp = rt;
    if (rt->left() == NULL) {     // Only a right child
      rt = rt->right();         //  so point to right
      delete temp;
    }
    else if (rt->right() == NULL) { // Only a left child
      rt = rt->left();          //  so point to left
      delete temp;
    }
    else {                    // Both children are non-empty
      BSTNode<Key, E>* temp = getmin(rt->right());
      rt->setElement(temp->element());
      rt->setKey(temp->key());
      rt->setRight(deletemin(rt->right()));
      delete temp;
    }
  }
  return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
                              const Key& k) const {
  if (root == NULL) return NULL;          // Empty tree
  if (k < root->key())
    return findhelp(root->left(), k);   // Check left
  else if (k > root->key())
    return findhelp(root->right(), k);  // Check right
  else {
      E* temp = new E;
      *temp = root->element();
      return temp;  // Found it
  }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const {
  if (root == NULL) return;           // Empty tree
  if (root->leftIsChild()) {
      printhelp(root->left(), level + 1);
  }

  
  char spacer[] = "       ";
  spacer[level] = '\0';
  say(spacer);
  say("-");
  say(root->key());
  say(" ");
  say(root->element());
  if (root->isLeaf()) {
      say(" (leaf)");
  }

  if (root->key() == 90) {
      int a = 0;
  }
  if (root->left() != NULL) {
      if (!root->leftIsChild()) {
          say(" predessor is ");
          say(root->left()->key());
      }
  }
  if (root->right() != NULL) {
      if (!root->rightIsChild()) {
          say(" successor is ");
          say(root->right()->key());
      }
  }



  say("\n");

  /* //I don't know what this is
  for (int i = 0; i < level; i++) {   // Indent to level
      cout << "  ";
      cout << root->key() << "\n";        // Print node value
  }
  */
  if (root->rightIsChild()) {
      printhelp(root->right(), level + 1);  // Do right subtree
  }
}

#endif