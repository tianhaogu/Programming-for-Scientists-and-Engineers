#include <iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "LIFOStackClass.h"
using namespace std;

/*Programmer: Tianhao Gu, Date: 03/30/2021
In this program I develop and implement three common linked data structures:
a sorted doubly-linked list, a simple queue, and a simple stack.*/

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main() {
  //This is just a placeholder main function - it does exceptionally
  //little actual testing, so you'll want to add your own tests here.
  //Feel free to leave your tests in the version of this file you
  //submit, but we will not be running your main function, so the
  //output, etc., of your main doesn't need to match anything from
  //a sample output, etc.
  SortedListClass testList;
  
  testList.printForward();
  testList.insertValue(42);
  testList.insertValue(49);
  testList.insertValue(31);
  testList.insertValue(47);
  testList.insertValue(62);
  testList.insertValue(42);
  testList.printForward();
  testList.printBackward();
  
  testList.clear();
  testList.printForward();
  
  return 0;
}

#endif