#include <iostream>
#include "printEnd.h"
using namespace std;

//print error message if the read ends before expected or after expected
void printEnd(const int countRow, const int countCol) {
  cout << "Error: Reading color from file" << endl;
  cout << "Error: Reading image pixel at row: " << countRow
       << " col: " << countCol << endl;
  cout << "Image read successful: No" << endl;
  cout << "Error: While reading the image, an error was encountered. "
       << " Exiting the program!" << endl;
}