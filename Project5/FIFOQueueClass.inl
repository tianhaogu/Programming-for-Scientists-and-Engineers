#include <iostream>
#include "FIFOQueueClass.h"
using namespace std;

template <class T>
FIFOQueueClass<T>::FIFOQueueClass() {
  head = 0;
  tail = 0;
}

template <class T>
FIFOQueueClass<T>::~FIFOQueueClass() {
  this-> clear();
}

template <class T>
void FIFOQueueClass<T>::enqueue(const T &newItem) {
  //check whether it's empty list
  if (head != 0) {
    LinkedNodeClass<T> *tempNode;
    tempNode = new LinkedNodeClass<T>(0, newItem, head);
    tempNode-> setBeforeAndAfterPointers();
    head = tempNode;
  }
  else {
    head = new LinkedNodeClass<T>(0, newItem, 0);
    tail = head;
  }
}

template <class T>
bool FIFOQueueClass<T>::dequeue(T &outItem) {
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

template <class T>
void FIFOQueueClass<T>::print() const {
  LinkedNodeClass<T> *tempNode = tail;
  while (tempNode != 0) {
    cout << tempNode-> getValue();
    if (tempNode != head) {
      cout << ' ';
    }
    tempNode = tempNode-> getPrev();
  }
  cout << endl;
}

template <class T>
int FIFOQueueClass<T>::getNumElems() const {
  LinkedNodeClass<T> *tempNode = head;
  int countNode = 0;
  while (tempNode != 0) {
    countNode += 1;
    tempNode = tempNode-> getNext();
  }
  return countNode;
}

template <class T>
void FIFOQueueClass<T>::clear() {
  LinkedNodeClass<T> *tempNode = head;
  LinkedNodeClass<T> *recordNode = head;
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
