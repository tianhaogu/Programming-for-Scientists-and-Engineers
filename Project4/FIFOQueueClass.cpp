#include <iostream>
#include "FIFOQueueClass.h"
using namespace std;

FIFOQueueClass::FIFOQueueClass() {
  head = 0;
  tail = 0;
}

FIFOQueueClass::~FIFOQueueClass() {
  this-> clear();
}

void FIFOQueueClass::enqueue(const int &newItem) {
  //check whether it's empty list
  if (head != 0) {
    LinkedNodeClass *tempNode;
    tempNode = new LinkedNodeClass(0, newItem, head);
    tempNode-> setBeforeAndAfterPointers();
    head = tempNode;
  }
  else {
    head = new LinkedNodeClass(0, newItem, 0);
    tail = head;
  }
}

bool FIFOQueueClass::dequeue(int &outItem) {
  //check whether it's empty list
  if (tail != 0) {
    outItem = tail-> getValue();
    //check whether there's only one element in the list
    if (head == tail) {
      delete tail;
      tail = 0;
      head = 0;
    }
    else {
      tail = tail-> getPrev();
      delete tail-> getNext();
      tail-> setNextPointerToNull();
    }
    return true;
  }
  else {
    return false;
  }
}

void FIFOQueueClass::print() const {
  LinkedNodeClass *tempNode = tail;
  while (tempNode != 0) {
    cout << tempNode-> getValue();
    if (tempNode != head) {
      cout << ' ';
    }
    tempNode = tempNode-> getPrev();
  }
  cout << endl;
}

int FIFOQueueClass::getNumElems() const {
  LinkedNodeClass *tempNode = head;
  int countNode = 0;
  while (tempNode != 0) {
    countNode += 1;
    tempNode = tempNode-> getNext();
  }
  return countNode;
}

void FIFOQueueClass::clear() {
  LinkedNodeClass *tempNode = head;
  LinkedNodeClass *recordNode = head;
  //delete nodes and set prev and next points to NULL
  while (tempNode != 0) {
    tempNode = tempNode-> getNext();
    recordNode-> setPreviousPointerToNull();
    recordNode-> setNextPointerToNull();
    delete recordNode;
    recordNode = tempNode;
  }
  head = 0;
  tail = 0;
}
