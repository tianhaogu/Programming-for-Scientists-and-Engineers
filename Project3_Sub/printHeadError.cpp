#include <iostream>

#include "printHeadError.h"
using namespace std;

//print error message if head of the file reads fail ro end of file
void printHeadError() {
  cout << "Error: Reading image header from file" << endl;
  cout << "Image read successful: No" << endl;
  cout << "Error: While reading the image, an error was encountered.  " 
       << "Exiting the program!" << endl;
}
