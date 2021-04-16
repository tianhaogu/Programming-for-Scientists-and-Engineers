#include "CarClass.h"

#include <iostream>
using namespace std;

//Assign the static attribute used for auto-assigning unique ids
int CarClass::nextIdVal = 0;

CarClass &CarClass::operator=(const CarClass &rhs) {
  this-> uniqueId = rhs.getId();
  this-> travelDir = rhs.travelDir;
  this-> arrivalTime = rhs.arrivalTime;
  this-> nextIdVal = rhs.nextIdVal;
  return *this;
}

ostream &operator<<(ostream &outStream, const CarClass &carToPrint) {
  outStream << "Car id: " << carToPrint.uniqueId <<
               " traveling: " << carToPrint.travelDir <<
               " arrived: " << carToPrint.arrivalTime;
  return outStream;
}

