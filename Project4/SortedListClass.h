#ifndef _SORTEDLISTCLASS_H_
#define _SORTEDLISTCLASS_H_

#include <iostream>
#include "LinkedNodeClass.h"
using namespace std;

class SortedListClass {
  private:
    LinkedNodeClass *head;
    LinkedNodeClass *tail;

  public:
    //constructor, copy constructor, destructor
    SortedListClass();
    SortedListClass(const SortedListClass &rhs);
    ~SortedListClass();
    void clear();

    //insert value to corresponding position
    void insertValue(const int &valToInsert);

    //print elements
    void printForward() const;
    void printBackward() const;

    //remove elements
    bool removeFront(int &theVal);
    bool removeLast(int &theVal);
    
    //get length of the list and element at specific position
    int getNumElems() const;
    bool getElemAtIndex(const int index, int &outVal) const;
};

#endif
