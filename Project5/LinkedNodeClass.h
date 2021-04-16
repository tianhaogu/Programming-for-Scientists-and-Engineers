#ifndef _LINKEDNODECLASS_H_
#define _LINKEDNODECLASS_H_

#include <iostream>
using namespace std;

template <class T>
class LinkedNodeClass {
  private:
    LinkedNodeClass<T> *prevNode;
    T nodeVal;
    LinkedNodeClass<T> *nextNode;

  public:
    //constructor
    LinkedNodeClass(LinkedNodeClass<T> *inPrev, const T &inVal, 
                    LinkedNodeClass<T> *inNext);

    //Returns the value stored within this node
    T getValue() const;
    //Returns the address of the node that follows/before this node
    LinkedNodeClass<T>* getNext() const;
    LinkedNodeClass<T>* getPrev() const;

    //Sets the object’s next/prev node pointer to NULL.
    void setNextPointerToNull();
    void setPreviousPointerToNull();
    //set newt/prev nodes' pointer to this object
    void setBeforeAndAfterPointers();
};

#include "LinkedNodeClass.inl"
#endif