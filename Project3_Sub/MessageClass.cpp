#include <iostream>
#include "MessageClass.h"
using namespace std;

//construct the 2d array
MessageClass::MessageClass(const int msgRow, const int msgCol) {
  messageArray = new int*[msgRow];
  for (int i = 0; i < msgRow; ++i) {
    messageArray[i] = new int[msgCol];
  }
  numRow = msgRow;
  numCol = msgCol;
}

//delete the 2d array
MessageClass::~MessageClass() {
  for (int i = 0; i < numRow; ++i) {
    delete [] messageArray[i];
    messageArray[i] = NULL;
  }
  delete [] messageArray;
  messageArray = NULL;
  numRow = MIN_INDEX;
  numCol = MIN_INDEX;
}

int MessageClass::getVal(const int currentMsgRow, 
	                 const int currentMsgCol) const {
  return messageArray[currentMsgRow][currentMsgCol];
}

int MessageClass::getRowSize() const {
  return numRow;
}

int MessageClass::getColSize() const {
  return numCol;
}

void MessageClass::setVal(const RowColumnClass &inRowCol, const int msgVal) {
  messageArray[inRowCol.getRow()][inRowCol.getCol()] = msgVal;
}
