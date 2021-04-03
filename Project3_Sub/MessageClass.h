#ifndef _MESSAGECLASS_H_
#define _MESSAGECLASS_H_

#include <iostream>
#include "RowColumnClass.h"
#include "constants.h"
using namespace std;

class MessageClass {
  public:
    //constructor, default constructor and destructor
    MessageClass();
    MessageClass(const int msgRow, const int msgCol);
    ~MessageClass();
    
    //get the int calue at the current place
    int getVal(const int currentMsgRow, const int currentMsgCol) const;
    int getRowSize() const;
    int getColSize() const;
    
    //set the value at current location according to given value
    void setVal(const RowColumnClass &inRowCol, const int msgVal);

  private:
    int **messageArray;
    int numRow;
    int numCol;
};
#endif