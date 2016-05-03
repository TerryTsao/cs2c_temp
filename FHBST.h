//
//  FHBST.h
//  Naive Binary Tree (No threads or balancing)
//
//  Created by Anand Venkataraman on 4/27/16.
//  Copyright © 2016 Anand Venkataraman. All rights reserved.
//

#ifndef FHBST_h
#define FHBST_h

#include <sstream>

// --------------------- FHNode Prototype -------------------------
template <class T>
class FHNode
{
public:
    FHNode(const T& d = T(), FHNode *l = NULL, FHNode *r = NULL)
    : data(d), left(l), right(r) {}
    
    FHNode *left, *right;
    T data;
};

// ---------------------- FHBST Prototype --------------------------
template <class T>
class FHBST
{
protected:
    int mSize;
    FHNode<T> *mRoot;
    
public:
    FHBST() { mSize = 0; mRoot = NULL; }
    FHBST(const FHBST& rhs) { mRoot = NULL; mSize = 0; *this = rhs; }
    ~FHBST() { clear(); }
    
    bool isEmpty() const { return (mSize == 0); }
    int size() const { return mSize; }
    void clear() { makeEmpty(mRoot); }
    
    // Ask yourself WHY we need the below, where you pass x and get back x!
    // Hint: & has something to do with it.
    const T& find(const T& x) const;
    
    bool insert(const T& x) { return insert(mRoot, x); }
    bool remove(const T& x) { return remove(mRoot, x); }
    bool contains(const T& x) const { return find(mRoot, x) != NULL; }
    string to_string() const { return to_string(mRoot, 0); }
    
protected:
    FHNode<T> *find(FHNode<T> *node, const T& x) const;
    FHNode<T> *findMin(FHNode<T> *node) const;
    bool insert(FHNode<T> *& node, const T& x);
    bool remove(FHNode<T> *& node, const T& x);
    string to_string(const FHNode<T> *node, int level) const;
    void makeEmpty(FHNode<T>* &node);
    
public:
    // for exception throwing
    class EmptyTreeException {};
    class NotFoundException {};
};

// FHBST public method definitions -----------------------------
// Only the public find() is not inline because it throws an exception.

template <class T>
const T& FHBST<T>::find(const T& x) const {
    FHNode<T> *resultNode;
    
    resultNode = find(mRoot, x);
    if (resultNode == NULL)
        throw NotFoundException();
    return resultNode->data;
}

// FHBST private method definitions -----------------------------
//
// IMPORTANT: PONDER THIS: Below, why don't we ever check "x > node->data"
// or "x == node->data"?

template <class T>
FHNode<T>* FHBST<T>::find(FHNode<T> *node, const T& x) const {
    if (node == NULL) return NULL;
    
    if (node->data < x) return find(node->right, x);
    if (x < node->data) return find(node->left, x);
    return node;
}

template <class T>
FHNode<T>* FHBST<T>::findMin(FHNode<T> *node) const {
    if (node == NULL) return NULL;
    return node->left == NULL ? node : findMin(node->left);
}

template<class T>
bool FHBST<T>::insert(FHNode<T>* &node, const T& x) {
    if (node == NULL) {
        node = new FHNode<T>(x, NULL, NULL);
        ++mSize;
        return true;
    }
    
    if (x < node->data) return insert(node->left, x);
    if (node->data < x) return insert(node->right, x);
    return false; // Duplicate, conflict
}


template<class T>
bool FHBST<T>::remove(FHNode<T> * &node, const T& x) {
    if (node == NULL) return false; // No such x!
    
    if (x < node->data) return remove(node->left, x);
    if (node->data < x) return remove(node->right, x);
    
    // node->data == x. Replace x with the right-min (left-max is fine too)
    if (node->left != NULL && node->right != NULL) {
        FHNode<T> *rightMin = findMin(node->right);
        node->data = rightMin->data;
        return remove(node->right, rightMin->data);  // Will be true.
    }
    
    // Either L or R is NULL. Yank up the other
    FHNode<T> *temp = node;
    node = (node->left == NULL? node->right : node->left);
    delete temp;
    
    --mSize;
    return true;
}

template<class T>
string FHBST<T>::to_string(const FHNode<T> *node, int level) const {
    std::ostringstream os;
    
    static string blanks = "                                                  ";
    string indent = level > blanks.length()-1 ? (blanks + " ...") : blanks.substr(0, level);
    
    if (node == NULL) return indent + "<NULL>\n";
    
    os <<indent
       <<node->data << "\n"
       <<to_string(node->left, level+1)
       <<to_string(node->right, level+1)
    ;
    
    return os.str();
}

template<class T>
void FHBST<T>::makeEmpty(FHNode<T>* &node) {
    if (node == NULL) return;
    
    makeEmpty(node->left);
    makeEmpty(node->right);
    delete node;
    node = NULL;
}

#endif /* FHBST_h */

