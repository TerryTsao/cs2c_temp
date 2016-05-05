/*
   1. insert of random elements into fhbst
   2. sequential insert = O(n^2)
   3. shuffled insert: T(n) = an + bn + c log(n) = O(n) linear
   4. Lookup time
 
   BSTLookupExpts
      * SeqInsertionExpt
      * ShuffledInsertonExpt.

      functor would just do a random numm generator and search

   5. 25 data points - and get the time to run.
 
 
*/


#include <iosteam>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "FHBST.h"
#include "Timeable.h"

using namespace std;

class SeqInsertExpt : public Timeable {
private:
   int treeSize;
   FHBST<int> aTree;
public:
   SeqInsertExpt(int nElements, int nTimes) :
      treeSize(nElements), Timeable(nTimes)
   {
      for (i=0; i<nElements; i++)
         aTree.insert(i);
   }
   ~ SeqInsertExpt() { aTree.clear(); }
   void operator() ()
   {
      srand(time(NULL));
      int aRand = rand() % treeSize;
      aTree.find(aRand);
   }
};

class ShuffledInsertonExpt : public Timeable{
private:
   int treeSize;
   FHBST<int> aTree;
public:
   ShuffledInsertonExpt(int nElements, int nTimes) :
      treeSize(nElements), Timeable(nTimes)
   {
      vector<int> aVec;
      for (int i=0; i<nElements; i++)
         aVec.push_back(i);
      
      random_shuffle(aVec.begin(), aVec.end());
      
      for (int i=0; i<nElements; i++)
         aTree.insert(aVec[i]);
   }
   ~ ShuffledInsertonExpt() { aTree.clear(); }
   void operator() ()
   {
      srand(time(NULL));
      int aRand = rand() % treeSize;
      aTree.find(aRand);
   }
      
};
int main(int argc, const char * argv[])
{

   int minTreeSize = 100, maxTreeSize = 5000, stepSize = 500;
   int numTime = 1000;
   
   for (int i = minTreeSize; i < maxTreeSize; i+= stepSize)
   {
      if (i >= 3500)
         int n = 0;
      
      SeqInsertionExpt seqExp(i, numTime);
      ShuffledInsertonExpt shuffledExp(i, numTime);
      
      cout << i << ", "
           << Timeable::timeit(&seqExp)
           << ", "
           << Timeable::timeit(&shuffledExp)
           << endl;
   }
   
}
