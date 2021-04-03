#ifndef _CHECKHEADENDFAIL_H_
#define _CHECKHEADENDFAIL_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include "printHeadError.h"
#include "constants.h"
using namespace std;

//check whether the head (title, colNum, rowNum) reads fail or end of file
void checkHeadEndFail(istream &inFile);
#endif