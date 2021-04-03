#include <iostream>
#include <cstdlib>
#include <string>
#include "checkColorEndFail.h"
using namespace std;

//check whether the color reads fail or end of file
void checkColorEndFail(const int countRow, const int countCol, 
	               istream &inFile) {
  if (inFile.eof()) {
    if (inFile.fail()) {
      printEnd(countRow, countCol);
      exit(3);
    }
  }
  if (inFile.fail()) {
    inFile.clear();
    inFile.ignore(IGNORE_NUMBER, '\n');
    printColorError(countRow, countCol, 1);
    exit(3);
  }
}
