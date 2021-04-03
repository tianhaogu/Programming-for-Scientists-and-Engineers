#ifndef _CHECKCOLORENDFAIL_H_
#define _CHECKCOLORENDFAIL_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include "printEnd.h"
#include "printColorError.h"
#include "constants.h"
using namespace std;

//check whether the color reads fail or end of file
void checkColorEndFail(const int countRow, const int countCol, 
	               istream &inFile);
#endif
