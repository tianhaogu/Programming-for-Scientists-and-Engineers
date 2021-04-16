#include <iostream>
#include "SortedListClass.h"
using namespace std;

template <class T>
SortedListClass<T>::SortedListClass() {
  head = 0;
  tail = 0;
}

template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs) {
  LinkedNodeClass<T> *tmpNode = rhs.head;
  head = 0;
  tail = 0;
  for (int i = 0; i < rhs.getNumElems(); ++i) {
    this-> insertValue(tmpNode-> getValue());
    tmpNode = tmpNode-> getNext();
  }
}

template <class T>
SortedListClass<T>::~SortedListClass() {
  this-> clear();
}

template <class T>
void SortedListClass<T>::clear() {
  T theVal;
  int orinigalLength = this-> getNumElems();
  for (int i = 0; i < orinigalLength; ++i) {
    this-> removeFront(theVal);
  }
}

template <class T>
void SortedListClass<T>::insertValue(const T &valToInsert) {
  LinkedNodeClass<T> *tempNode;
  //check whether it's empty list
  if (head == 0) {
    tempNode = new LinkedNodeClass<T>(0, valToInsert, 0);
    head = tempNode;
    tail = tempNode;
  }
  else {
    //check whether the inserted value is smaller than head value
    if (head-> getValue() > valToInsert) {
      tempNode = new LinkedNodeClass<T>(0, valToInsert, head);
      tempNode-> setBeforeAndAfterPointers();
      head = tempNode;
    }
    else {
      tempNode = head;
      //get to the correct position
      while (tempNode != 0 && tempNode-> getValue() <= valToInsert) {
        tempNode = tempNode-> getNext();
      }
      //check whether it's the largest value
      if (tempNode != 0) {
        tempNode = new LinkedNodeClass<T>(tempNode-> getPrev(), 
                                          valToInsert, tempNode);
      }
      else {
  	tempNode = new LinkedNodeClass<T>(tail, valToInsert, 0);
        tail = tempNode;
      }
      tempNode-> setBeforeAndAfterPointers();
    }
  }
}

template <class T>
void SortedListClass<T>::printForward() const {
  LinkedNodeClass<T> *tempNode = head;
  cout << "Forward List Contents Follow:" << endl;
  while (tempNode != 0) {
    cout << "  " << tempNode-> getValue() << endl;
    tempNode = tempNode-> getNext();
  }
  cout << "End of List Contents" << endl;
}

template <class T>
void SortedListClass<T>::printBackward() const {
  LinkedNodeClass<T> *tempNode = tail;
  cout << "Backward List Contents Follow:" << endl;
  while (tempNode != 0) {
    cout << "  " << tempNode-> getValue() << endl;
    tempNode = tempNode-> getPrev();
  }
  cout << "End of List Contents" << endl;
}

template <class T>
bool SortedListClass<T>::removeFront(T &theVal) {
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

template <class T>
bool SortedListClass<T>::removeLast(T &theVal) {
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

template <class T>
int SortedListClass<T>::getNumElems() const {
  LinkedNodeClass<T> *tempNode = head;
  int countNode = 0;
  while (tempNode != 0) {
    countNode += 1;
    tempNode = tempNode-> getNext();
  }
  return countNode;
}

template <class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const {
  if (index >= this-> getNumElems() || index < 0) {
    return false;
  }
  int countNode = 0;
  LinkedNodeClass<T> *tempNode = head;
  //loop to te the correct position
  while (countNode < index) {
    countNode += 1;
    tempNode = tempNode-> getNext();
  }
  outVal = tempNode-> getValue();
  return true;
}
