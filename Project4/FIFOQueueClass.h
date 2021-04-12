#ifndef _FIFOQUEUECLASS_H_
#define _FIFOQUEUECLASS_H_

#include <iostream>
#include "LinkedNodeClass.h"
using namespace std;

class FIFOQueueClass {
  private:
    LinkedNodeClass *head;
    LinkedNodeClass *tail;

  public:
    //constructor and destructor
    FIFOQueueClass();
    ~FIFOQueueClass();

    //Inserts the value provided into the queue
    void enqueue(const int &newItem);
    //Attempts to take the next item out of the queue
    bool dequeue(int &outItem);

    void print() const;
    int getNumElems() const;
    void clear();
};

#endif
