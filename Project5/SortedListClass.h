#ifndef _SORTEDLISTCLASS_H_
#define _SORTEDLISTCLASS_H_

#include <iostream>
#include "LinkedNodeClass.h"
using namespace std;

template <class T>
class SortedListClass {
  private:
    LinkedNodeClass<T> *head;
    LinkedNodeClass<T> *tail;

  public:
    //constructor, copy constructor, destructor
    SortedListClass();
    SortedListClass(const SortedListClass<T> &rhs);
    ~SortedListClass();
    void clear();

    //insert value to corresponding position
    void insertValue(const T &valToInsert);

    //print elements
    void printForward() const;
    void printBackward() const;

    //remove elements
    bool removeFront(T &theVal);
    bool removeLast(T &theVal);
    
    //get length of the list and element at specific position
    int getNumElems() const;
    bool getElemAtIndex(const int index, T &outVal) const;
};

#include "SortedListClass.inl"
#endif
