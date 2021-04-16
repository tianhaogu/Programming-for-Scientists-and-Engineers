#ifndef _FIFOQUEUECLASS_H_
#define _FIFOQUEUECLASS_H_

#include <iostream>
#include "LinkedNodeClass.h"
using namespace std;

template <class T>
class FIFOQueueClass {
  private:
    LinkedNodeClass<T> *head;
    LinkedNodeClass<T> *tail;

  public:
    //constructor and destructor
    FIFOQueueClass();
    ~FIFOQueueClass();

    //Inserts the value provided into the queue
    void enqueue(const T &newItem);
    //Attempts to take the next item out of the queue
    bool dequeue(T &outItem);

    void print() const;
    int getNumElems() const;
    void clear();
};

#include "FIFOQueueClass.inl"
#endif
