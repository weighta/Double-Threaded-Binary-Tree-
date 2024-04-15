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

  //------  My functions
  BSTNode<Key, E>* findPredessor(const Key& k);
  BSTNode<Key, E>* findSuccessor(const Key& k);
  void threads(BSTNode<Key, E>* root);
  //------

  // Private "helper" functions
  void clearhelp(BSTNode<Key, E>*);
  void inserthelp(const Key&, const E&);
  BSTNode<Key,E>* deletemin(BSTNode<Key, E>*);
  BSTNode<Key,E>* getmin(BSTNode<Key, E>*);
  BSTNode<Key,E>* removehelp(BSTNode<Key, E>*, const Key&);
  E* findhelp(BSTNode<Key, E>*, const Key&) const;
  void printhelp(BSTNode<Key, E>*, int) const;
  void printhelp() const;
  void vist(BSTNode<Key, E>*) const;

public:

  BST() { // Constructor
      root = NULL;
      nodecount = 0;
  }   
  BST(const Key& k, const E& e) { // Constructor with arguments, just allows flexability really
      root = NULL; //set root to NULL for helpful terminating conditionals later
      nodecount = 0; //set nodecount to 0; I think this came back as junk once in memory without inizialiting 0 and the for loop was buggy later
      insert(k, e); //perform the first insert
  }
  
  //Note from Prof Sipantzi -- I've commented out the destructor
  //since you would have to change clearhelp() to make it work with
  //doubly-threaded trees and that is not part of the assignment.
  //~BST() { clearhelp(root); }            // Destructor

  /// <summary>
  /// I don't think we got around to this...
  /// </summary>
  void clear() {
      clearhelp(root);
      root = NULL;
      nodecount = 0;
  }

  // Insert a record into the tree.
  // k Key value of the record.
  // e The record to insert.
  void insert(const Key& k, const E& e) {
      inserthelp(k, e); // insert the record by reference
      nodecount++; //increment the node count
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

  // Print the Tree of the BST in order with recurssion
  void print() {
      if (root == NULL) { //why bother-- if it's empty!
          sayl("The BST is empty.\n");
      }
      else {
          /// <summary>
          /// Realistically, threads doesnt *need* called here, it just saves cpu vs doing it live in the insert()
          /// </summary>
          threads(root); //do the threads first on the double-tree
          printhelp(); //then print
      }
  }


  void printInOrder(char);     // Print the BST in order withOUT recurssion
  void printInOrder();  //Overload provides a little lee-way to save the (char) declaration; default is 0 for NOT-REVERSED
  void printReverse();   // Print the contents of the BST in reverse (no recurssion)


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


// Insert a node into the BST, return void; no use of recursion
template <typename Key, typename E>
void BST<Key, E>::inserthelp(const Key& k, const E& it) {

    /// <summary>
    /// Okay, six hours later here we are
    /// </summary>

    if (root == NULL) { //the case where nothing exists
        root = new BSTNode<Key, E>(k, it, NULL, NULL); //this will be the start of things, it will only execute 1 time for initial stem
        return;
    }

    BSTNode<Key, E>* currentNode = root; //the current node will keep track of where we are during the insert
    BSTNode<Key, E>* newNode = new BSTNode<Key, E>(k, it, NULL, NULL); //this is our ACTUAL node to insert ahead of time
    while (1) { //we're looking to just solve where the node will insert at
        //just create a while loop, once a leaf is found, the node is inserted left or right, break

        if (k < currentNode->key()) { //go left since key is less than current node
            if (!currentNode->leftIsChild()) { //see if we're at a leaf
                currentNode->setLeft(newNode); //if we are, then place the node here
                currentNode->setLeftIsChild(1); //MAKE SURE the node recognizes that this is NO LONGER a thread, but a real child!
                return;
            }
            else { //otherwise we keep going
                currentNode = currentNode->left();
            }
        }
        else { //go right if the key is larger than current node
            if (!currentNode->rightIsChild()) { //see if we're at a leaf
                currentNode->setRight(newNode); 
                currentNode->setRightIsChild(1);
                return;
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
  if (!rt->leftIsChild()) //jump if not zero
    return rt;
  else return getmin(rt->left()); //recursive call
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
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const {
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


// Finds the predessor of a node in the BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::findPredessor(const Key& k) {

    /// <summary>
    /// Alright here's the predessor, a bit messy on ifs, but it's good
    /// </summary>

    if (root == NULL) {
        return NULL; //we'll just stop what we're doing if the root isnt established
    }
    BSTNode<Key, E>* currentNode = root; //The current node during the 'search' - very important
    BSTNode<Key, E>* predessor = NULL; //The actual predessor to return, this will fluctuate a bit
    while (1) {
        //Another grueling task, but it's not so bad
        //the predessor is just the largest possible number smaller than the current node's key

        if (currentNode->key() > k) { //if current node is greater
            if (currentNode->leftIsChild()) { //go to the left to shrink our findings
                if (currentNode->key() < k) { //is the node less than key size
                    predessor = currentNode; //if so, that's our candidate predessor
                }
                currentNode = currentNode->left(); //otherwise, keep shrinking
            }
            else {
                return predessor; //return predessor if the current node's left is not a child, therefor it's the largest/smallest
            }
        }
        else { //else the node is smaller
            if (currentNode->rightIsChild()) { // so we need to check if right is a child first
                if (currentNode->key() < k) { // that way well also check to see if the key is still LARGER than the node's key in question
                    predessor = currentNode; //and if so, candidate predessor found
                }
                currentNode = currentNode->right(); //keep going
            }
            else {
                return predessor; //return predessor if no more childs found to the right to keep making the predessor as large as it can
            }
        }
    }
}

// Finds the successor of a node in the BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::findSuccessor(const Key& k) {

    /// <summary>
    /// Successor is similar to finding predessor, just a couple tweaks
    /// </summary>

    if (root == NULL) {
        return NULL; //tree doesnt exist, so terminate
    }

    BSTNode<Key, E>* currentNode = root; //Similarly, create a current node for searching for the successor
    BSTNode<Key, E>* successor = NULL; //then we can have ourselves the real-time candadite successor
    while (1) {
        //like solving for predessor without recursion, we can use a while loop to solve successor

        if (currentNode->key() > k) { //make sure the node is still larger than the key
            if (currentNode->leftIsChild()) { //make sure a left child exists first
                if (currentNode->key() > k) { //then make sure the node is *still* larger
                    successor = currentNode; //if the key is still smaller than the node's, it's a candadite successor
                }
                currentNode = currentNode->left(); //keep going left to shrink the successor as much as possible
            }
            else {
                return successor; //if no more left childs, we found the successor
            }
        }
        else { //if it isnt, we need to go to the right to increase it so
            if (currentNode->rightIsChild()) { //but make sure a right child exists first
                if (currentNode->key() > k) { //and if it does, tripple-check to make sure the current node's key is larger
                    successor = currentNode; //it is, so here's our candidate successor
                }
                currentNode = currentNode->right(); //keep going to the right
            }
            else {
                return successor; //if no more right childs exist, we found it
            }
        }
    }
}

// Maps the threads with finding successors and predessors using recursion
template <typename Key, typename E>
void BST<Key, E>::threads(BSTNode<Key, E>* root) {
    //we need to assign each node a thread if possible
    //possible meaning we are at the end of each node, and it does not have any more children
    if (root->leftIsChild()) {
        threads(root->left()); //keep going
    }
    if (root->rightIsChild()) {
        threads(root->right()); //keep going
    }
    if (!root->leftIsChild()) {
        root->setLeft(findPredessor(root->key())); //there we are, find its predessor
    }
    if (!root->rightIsChild()) {
        root->setRight(findSuccessor(root->key())); //find successor
    }
}

// Print out a BST (with recursion)
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const {
    if (root == NULL) return; // Empty tree, so leave it
    if (root->leftIsChild()) { //start with minimum value
        printhelp(root->left(), level + 2); //increase level by 2 so that indent works
    }
    char spacer[0xFF]; //this will be the space array ' '
    memset(spacer, 0x20, 0xFF); //dramatic, just a fast way of setting the space array
    spacer[level] = '\0'; //null-terminated position for the spacer
    //------ setting up the scene
    say(spacer);
    say("-");
    say(root->key());
    say(" ");
    say(root->element());
    //------
    if (root->isLeaf()) { //This is helpful
        say(" (leaf)"); //, will say if the node is a leaf or not
    }
    if (root->left() != NULL) {
        if (!root->leftIsChild()) { //if not a child
            say(" predessor is "); //then we can view it's predessor! cool.
            say(root->left()->key());
        }
    }
    if (root->right() != NULL) {
        if (!root->rightIsChild()) { //same with the successor if applicable
            say(" successor is ");
            say(root->right()->key());
        }
    }
    say("\n");
    if (root->rightIsChild()) {
        printhelp(root->right(), level + 2);  // Do right subtree after the left and displaying the middle node
    }
}

// Overload for printhelp just to simplify no int level input
template <typename Key, typename E>
void BST<Key, E>::printhelp() const {
    printhelp(root, 0); //0 means it will not print reversed
}
//Print out a BST (no recursion)
template<typename Key, typename E>
void BST<Key, E>::printInOrder(char reversed) {
    int i = 0; //declar an indexer for future traversal
    BSTNode<Key, E>* nodesInOrder[0xFF]; //Okay, logistically speaking, this isn't good, I just did it to save heap,
                                        //it's only 2,040 bytes of memory so no big deal
                                        //declare a pointer array so save the nodes in order thanks to their neighboring successors/predessors
    BSTNode<Key, E>* currentNode = getmin(root); //start at the left of the tree

    while (i < nodecount) { //make sure we hit all nodecount nodes
        if (currentNode->rightIsChild()) { //start by seeing if right is child
            if (!currentNode->leftIsChild()) { //if so, make sure left is not child
                nodesInOrder[i++] = currentNode; //now we can save this node
            }
            currentNode = currentNode->right(); //...and move on!
            while (currentNode->leftIsChild()) { //if the left happens to be a child
                currentNode = currentNode->left(); //then keep going left
            }
        }
        else { //if the node has no right child, 
            nodesInOrder[i++] = currentNode; //then immediately save the node
            if (currentNode->right() != NULL) { //ensure we aren't at the end, yet...
                if (!currentNode->rightIsChild()) { //check if the right is NOT a child
                    currentNode = currentNode->right(); //then jump to its successor
                    nodesInOrder[i++] = currentNode; //save the successor
                }
            }
        }
    }

    //easy part, reminds me of the c# days
    if (reversed) { //if reversed, print backwards
        for (int j = nodecount - 1; j >= 0; j--) {
            sayl(nodesInOrder[j]->element());
        }
    }
    else { //otherwise print forwards
        for (int j = 0; j < nodecount; j++) {
            sayl(nodesInOrder[j]->element());
        }
    }
}

template <typename Key, typename E>
void BST<Key, E>::printReverse() {
    printInOrder(1);
}

template <typename Key, typename E>
void BST<Key, E>::printInOrder() {
    printInOrder(0);
}


#endif