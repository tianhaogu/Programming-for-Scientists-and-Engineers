#include <iostream>
#include "FIFOQueueClass.h"
#include "LIFOStackClass.h"
#include "LinkedNodeClass.h"
#include "SortedListClass.h"

using namespace std;
//Programmer: Wentao Xiong
//Date: March 30th  2021
//Purpose: To demonstrate a program that 
//develop three data structures: 
//a sorted doubly-linked list, 
//a simple queue,
//and a simple stack.


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
  // Test SortedListClass
  SortedListClass testList;
  int num = 10;
  testList.printForward();
  testList.insertValue(42);
  testList.insertValue(45);
  testList.getElemAtIndex(1, num);
  cout << "Num1: " << num << endl;
  testList.insertValue(20);
  testList.printForward();
  cout << "1. Number of Elements: " << testList.getNumElems()
       << endl;
  testList.insertValue(3);
  testList.printForward();
  cout << "2. Number of Elements: " << testList.getNumElems()
       << endl;
  testList.removeFront(num);
  cout << "After removing from the front, Num2: " << num 
       << endl;
  testList.printForward();
  testList.removeLast(num);
  cout << "After removing from the last, Num3: " << num 
       << endl;
  testList.printForward();
  cout << "3. Number of Elements: " << testList.getNumElems()
       << endl;
  testList.removeLast(num);
  cout << "Remove status: " << testList.removeLast(num) << endl;
  cout << "Remove status: " << testList.removeLast(num) << endl;

  testList.printBackward();
  
  LIFOStackClass testStackList;
  testStackList.print();
  cout << testStackList.getNumElems() << endl;
  testStackList.push(42);
  testStackList.push(20);
  testStackList.push(35);
  testStackList.push(1);
  testStackList.push(-4);
  testStackList.print();
  cout << "The length of Stack 1 is " << testStackList.getNumElems()
       << endl;
  int tempNum;
  testStackList.pop(tempNum);
  testStackList.print();
  cout << "Stack Num is: " << tempNum << endl;
  cout << "The length of Stack 2 is " << testStackList.getNumElems()
       << endl;
  testStackList.clear();
  cout << "After clearing: " << endl;
  cout << "The length of Stack 3 is " << testStackList.getNumElems()
       << endl;
  cout << "Pop is "
       << testStackList.pop(tempNum)
       << endl;


  FIFOQueueClass testQueueList;
  testQueueList.print();
  cout << testQueueList.getNumElems() << endl;

  testQueueList.enqueue(42);
  testQueueList.enqueue(20);
  testQueueList.enqueue(35);
  cout << "The length of Queue 0: " << testQueueList.getNumElems()
       << endl;
  testQueueList.enqueue(1);
  testQueueList.enqueue(-4);
  testQueueList.print();
  cout << "The length of Queue 1: " << testQueueList.getNumElems()
       << endl;
  int tempNumQueue;
  testQueueList.dequeue(tempNumQueue);
  testQueueList.print();
  cout << "Queue Num is: " << tempNumQueue << endl;
  cout << "The length of Queue 2: " << testQueueList.getNumElems() 
       << endl;

  testQueueList.clear();
  cout << "After clearing: " << endl;
  cout << "The length of Queue 3: " << testQueueList.getNumElems()
       << endl;
  cout << "Dequeue is " 
       << testQueueList.dequeue(tempNumQueue) 
       << endl;

  return 0;
}
#endif

