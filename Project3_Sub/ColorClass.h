#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include <iostream>
#include "constants.h"
using namespace std;

class ColorClass {
  public:
    //constructor, default constructor and destructor for the class
    ColorClass();
    ColorClass(const int inRed, const int inGreen, const int inBlue);
    ~ColorClass();

    //get color values
    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    //set to multiple colors and check clipped or not
    void setTo(const int inRed, const int inGreen, const int inBlue);
    //set to the color of the class passed in
    void setTo(const ColorClass &inColor);
    
    //encode the current pixel according to input value
    void setEncode(const int encodeVal);
    //decode the current pixel according to the given color
    void decodeColor(int &thisColor);
    void decodeClass();

  private:
    int amountOfRed;
    int amountOfGreen;
    int amountOfBlue;
};
#endif