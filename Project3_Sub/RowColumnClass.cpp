#include <iostream>
#include "RowColumnClass.h"
using namespace std;

RowColumnClass::RowColumnClass(): 
  rowIndex(MIN_INDEX), 
  colIndex(MIN_INDEX) {
}

RowColumnClass::RowColumnClass(const int inRow, const int inCol) {
  rowIndex = inRow;
  colIndex = inCol;
}

RowColumnClass::~RowColumnClass() {
  rowIndex = MIN_INDEX;
  colIndex = MIN_INDEX;
}

int RowColumnClass::getRow() const {
  return rowIndex;
}

int RowColumnClass::getCol() const {
  return colIndex;
}
