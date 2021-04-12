#include <iostream>
#include "LIFOStackClass.h"
using namespace std;

LIFOStackClass::LIFOStackClass() {
  head = 0;
  tail = 0;
}

LIFOStackClass::~LIFOStackClass() {
  this-> clear();
}

void LIFOStackClass::push(const int &newItem) {
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

bool LIFOStackClass::pop(int &outItem) {
  //check whether it's empty list
  if (head != 0) {
    outItem = head-> getValue();
    //check whether there's only one element in the list
    if (head == tail) {
      delete head;
      head = 0;
      tail = 0;
    }
    else {
      head = head-> getNext();
      delete head-> getPrev();
      head-> setPreviousPointerToNull();
    }
    return true;
  }
  else {
    return false;
  }
}

void LIFOStackClass::print() const {
  LinkedNodeClass *tempNode = head;
  while (tempNode != 0) {
    cout << tempNode-> getValue();
    if (tempNode != tail) {
      cout << ' ';
    }
    tempNode = tempNode-> getNext();
  }
  cout << endl;
}

int LIFOStackClass::getNumElems() const {
  LinkedNodeClass *tempNode = head;
  int countNode = 0;
  while (tempNode != 0) {
    countNode += 1;
    tempNode = tempNode-> getNext();
  }
  return countNode;
}

void LIFOStackClass::clear() {
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
