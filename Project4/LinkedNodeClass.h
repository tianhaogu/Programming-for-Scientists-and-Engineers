#ifndef _LINKEDNODECLASS_H_
#define _LINKEDNODECLASS_H_

#include <iostream>
using namespace std;

class LinkedNodeClass {
  private:
    LinkedNodeClass *prevNode;
    int nodeVal;
    LinkedNodeClass *nextNode;

  public:
    //constructor
    LinkedNodeClass(LinkedNodeClass *inPrev, const int &inVal, 
                    LinkedNodeClass *inNext);

    //Returns the value stored within this node
    int getValue() const;
    //Returns the address of the node that follows/before this node
    LinkedNodeClass* getNext() const;
    LinkedNodeClass* getPrev() const;

    //Sets the object’s next/prev node pointer to NULL.
    void setNextPointerToNull();
    void setPreviousPointerToNull();
    //set newt/prev nodes' pointer to this object
    void setBeforeAndAfterPointers();
};

#endif