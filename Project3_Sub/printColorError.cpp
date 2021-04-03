#include <iostream>
#include "printColorError.h"
using namespace std;

//print error message if color value in the message reads fail or end of file
void printColorError(const int countRow, const int countCol, const int type) {
  if (type == TYPE_IMAGE_ERROR) {
    cout << "Error: Reading color from file" << endl;
    cout << "Error: Reading image pixel at row: " << countRow 
         << " col: " << countCol << endl;
    cout << "Image read successful: No" << endl;
    cout << "Error: While reading the image, an error was encountered.  "
         << "Exiting the program!" << endl;
  }
  if (type == TYPE_MESSAGE_ERROR) {
    cout << "Error: Reading message value at row/col: " << countRow 
  	 << ' ' << countCol << endl;
    cout << "Message encode successful: No" << endl;
  }
}
