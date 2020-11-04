#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "two_three_tree.h"

int main()
{
   auto tree = ttt::Two_thee_tree();
   // Insert something to this tree
   for(auto &i : {3,2,1,4,5,6,7,8,9})
       tree.insert(i);


}
