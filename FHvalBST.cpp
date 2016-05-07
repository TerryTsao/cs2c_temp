#ifndef FHVALBSTH
#define FHVALBSTH
#include "FHBST.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstring>
using std::string;
using std::vector;
using std::cout;
using std::endl;
template <class Comparable>
class FHvalNode : public FHNode<Comparable>
{
private:
   int height;
   
public:
   FHvalNode(const Comparable &d = Comparable(),
             FHvalNode<Comparable> *ltf = NULL,
             FHvalNode<Comparable> *rt = NULL,
             int height =0 )
   : FHvalNode<Comparable>(d, ltf, rt), height(height) {}
   int getHeight() {return height;}
   bool setHeight(int h) { if(h <1) return false; this->height =h; return true;}
};

template <class Comparable>
class FHvalBST : public FHBST<Comparable>
{
protected:
   void rotateWithLeft(FHvalNode<Comparable> * &k2);
   void rotateWithRight(FHvalNode<Comparable> * &k2);
   void doubleRotateWithLeft(FHvalNode<Comparable> * &k2);
   void doubleRotateWithRight(FHvalNode<Comparable> * &k2);
   static int heightOf(const FHvalNode<Comparable> *p) { return p == NULL ? -1 : p->getHeight(); }
   
   bool insert (const Comparable &x, FHvalNode<Comparable> * &node);
   bool remove (const Comparable &x, FHvalNode<Comparable> * &node);
public:
   bool insert(const Comparable &x) { return insert(x, this->mRoot); }
   bool remove(const Comparable &x) { return remove(x, this->mRoot); }
};

template <class Comparable>
void FHvalBST<Comparable> :: rotateWithLeft(FHvalNode<Comparable> * &k2)
{
   FHvalNode<Comparable> *k1 = k2->left;
   k2->left = k1->right;
   k1->right = k2;
   k2 = k1;
}

template <class Comparable>
void FHvalBST<Comparable> :: rotateWithRight(FHvalNode<Comparable> * &k2)
{
   FHvalNode<Comparable> *k1 = k2->right;
   k2->right = k1->left;
   k1->left = k2;
   k2 = k1;
}

template <class Comparable>
void FHvalBST<Comparable> :: doubleRotateWithLeft(FHvalNode<Comparable> * &k2)
{
   rotateWithRight(k2->left);
   rotateWithLeft(k2);
}
#endif


/*********** #TODO
 1. finish the implementation: insert/remove
 2. recursion (where?)
 3. insert mass int. and checkout how many recursions for 1 mil
 (21 recursions)
 4. post some result into forum on Saturday
 
 ******************/

int main()
{
   const int TREESIZE = 10; // change to after test 1000000
   FHvalBST<int> aValTree;
   
   // fill a tree
   for (int i=0; i<TREESIZE; i++)
      aValTree.insert( arc4random() % 200);
   
   aValTree.to_string();
   
}
