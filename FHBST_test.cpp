#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstring>

#include "FHBST.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

int main ()
{
   FHBST<int> newTree;
   for(int i=1; i<15; i++)
      newTree.insert(i);
   
   newTree.preorder_traversal();
   newTree.postorder_traversal();
}
