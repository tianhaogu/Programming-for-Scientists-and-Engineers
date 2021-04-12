#ifndef _LIFOSTACKCLASS_H_
#define _LIFOSTACKCLASS_H_

#include <iostream>
#include "LinkedNodeClass.h"
using namespace std;

class LIFOStackClass {
  private:
    LinkedNodeClass *head;
    LinkedNodeClass *tail;

  public:
    //constructor and destructor
    LIFOStackClass();
    ~LIFOStackClass();

    //Inserts the value provided into the stack
    void push(const int &newItem);
    //Attempts to take the next item out of the stack
    bool pop(int &outItem);
    
    void print() const;
    int getNumElems() const;
    void clear();
};

#endif
