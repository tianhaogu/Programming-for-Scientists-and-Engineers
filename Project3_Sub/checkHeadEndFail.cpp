#include <iostream>
#include <cstdlib>
#include <string>
#include "checkHeadEndFail.h"
using namespace std;

//check whether the head (title, colNum, rowNum) reads fail or end of file
void checkHeadEndFail(istream &inFile) {
  if (inFile.eof()) {
    printHeadError();
    exit(3);
  }
  if (inFile.fail()) {
    inFile.clear();
    inFile.ignore(IGNORE_NUMBER, '\n');
    printHeadError();
    exit(3);
  }
}