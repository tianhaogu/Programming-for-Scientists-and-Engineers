#include <iostream>
#include "constants.h"
#include "printMenu.h"
using namespace std;

//print the user menu for choice
void printMenu() {
  cout << CHOICE_ONE << ". Encode a message from file" << endl;
  cout << CHOICE_TWO << ". Perform decode" << endl;
  cout << CHOICE_THREE << ". Write current image to file" << endl;
  cout << CHOICE_FOUR << ". Exit the program" << endl;
  cout << "Enter your choice: ";
}