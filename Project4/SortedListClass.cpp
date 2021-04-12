#include <iostream>
#include "SortedListClass.h"
using namespace std;

SortedListClass::SortedListClass() {
  head = 0;
  tail = 0;
}

SortedListClass::SortedListClass(const SortedListClass &rhs) {
  LinkedNodeClass *tmpNode = rhs.head;
  head = 0;
  tail = 0;
  for (int i = 0; i < rhs.getNumElems(); ++i) {
    this-> insertValue(tmpNode-> getValue());
    tmpNode = tmpNode-> getNext();
  }
}

SortedListClass::~SortedListClass() {
  this-> clear();
}

void SortedListClass::clear() {
  int theVal;
  int orinigalLength = this-> getNumElems();
  for (int i = 0; i < orinigalLength; ++i) {
    this-> removeFront(theVal);
  }
}

void SortedListClass::insertValue(const int &valToInsert) {
  LinkedNodeClass *tempNode;
  //check whether it's empty list
  if (head == 0) {
    tempNode = new LinkedNodeClass(0, valToInsert, 0);
    head = tempNode;
    tail = tempNode;
  }
  else {
    //check whether the inserted value is smaller than head value
    if (valToInsert < head-> getValue()) {
      tempNode = new LinkedNodeClass(0, valToInsert, head);
      tempNode-> setBeforeAndAfterPointers();
      head = tempNode;
    }
    else {
      tempNode = head;
      //get to the correct position
      while (tempNode != 0 && valToInsert >= tempNode-> getValue()) {
  	tempNode = tempNode-> getNext();
      }
      //check whether it's the largest value
      if (tempNode != 0) {
  	tempNode = new LinkedNodeClass(tempNode-> getPrev(), 
                                       valToInsert, tempNode);
      }
      else {
  	tempNode = new LinkedNodeClass(tail, valToInsert, 0);
        tail = tempNode;
      }
      tempNode-> setBeforeAndAfterPointers();
    }
  }
}

void SortedListClass::printForward() const {
  LinkedNodeClass *tempNode = head;
  cout << "Forward List Contents Follow:" << endl;
  while (tempNode != 0) {
    cout << "  " << tempNode-> getValue() << endl;
    tempNode = tempNode-> getNext();
  }
  cout << "End of List Contents" << endl;
}

void SortedListClass::printBackward() const {
  LinkedNodeClass *tempNode = tail;
  cout << "Backward List Contents Follow:" << endl;
  while (tempNode != 0) {
    cout << "  " << tempNode-> getValue() << endl;
    tempNode = tempNode-> getPrev();
  }
  cout << "End of List Contents" << endl;
}

bool SortedListClass::removeFront(int &theVal) {
  //check whether it's empty list
  if (head != 0) {
    //check whether there's only one element in the list
    if (head != tail) {
      theVal = head-> getValue();
      //int theVal1 = head-> getNext()-> getValue();
      //cout << theVal1 << endl;
      head = head-> getNext();
      head-> getPrev()-> setNextPointerToNull();
      delete head-> getPrev();
      head-> setPreviousPointerToNull();
    }
    else {
      head-> setNextPointerToNull();
      head-> setPreviousPointerToNull();
      delete head;
      head = 0;
      tail = 0;
    }
    return true;
  }
  else {
    return false;
  }
}

bool SortedListClass::removeLast(int &theVal) {
  //check whether it's empty list
  if (tail != 0) {
    //check whether there's only one element in the list
    if (tail != head) {
      theVal = tail-> getValue();
      tail = tail-> getPrev();
      tail-> getNext()-> setPreviousPointerToNull();
      delete tail-> getNext();
      tail-> setNextPointerToNull();
    }
    else {
      tail-> setPreviousPointerToNull();
      tail-> setNextPointerToNull();
      delete tail;
      head = 0;
      tail = 0;
    }
    return true;
  }
  else {
    return false;
  }
}

int SortedListClass::getNumElems() const {
  LinkedNodeClass *tempNode = head;
  int countNode = 0;
  while (tempNode != 0) {
    countNode += 1;
    tempNode = tempNode-> getNext();
  }
  return countNode;
}

bool SortedListClass::getElemAtIndex(const int index, int &outVal) const {
  if (index >= this-> getNumElems() || index < 0) {
    return false;
  }
  int countNode = 0;
  LinkedNodeClass *tempNode = head;
  //loop to te the correct position
  while (countNode < index) {
    countNode += 1;
    tempNode = tempNode-> getNext();
  }
  outVal = tempNode-> getValue();
  return true;
}
