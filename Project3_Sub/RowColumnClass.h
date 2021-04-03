#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

#include <iostream>
#include "constants.h"
#include "checkHeadEndFail.h"
#include "printHeadError.h"
using namespace std;

class RowColumnClass {
  public:
    //constructor, default constructor, and destructor
    RowColumnClass();
    RowColumnClass(const int inRow, const int inCol);
    ~RowColumnClass();
    
    //accessors, access the current row and column position
    int getRow() const;
    int getCol() const;

  private:
    int rowIndex;
    int colIndex;
};
#endif