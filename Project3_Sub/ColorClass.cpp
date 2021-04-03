#include <iostream>
#include "ColorClass.h"
using namespace std;

ColorClass::ColorClass(): 
  amountOfRed(MAX_COLOR), 
  amountOfGreen(MAX_COLOR), 
  amountOfBlue(MAX_COLOR) {
}

ColorClass::ColorClass(const int inRed, const int inGreen, const int inBlue): 
  amountOfRed(inRed), 
  amountOfGreen(inGreen),
  amountOfBlue(inBlue) {
}

ColorClass::~ColorClass() {
  amountOfRed = MIN_COLOR;
  amountOfGreen = MIN_COLOR;
  amountOfBlue = MIN_COLOR;
}

void ColorClass::setTo(const int inRed, const int inGreen, const int inBlue) {
  amountOfRed = inRed;
  amountOfGreen = inGreen;
  amountOfBlue = inBlue;
}

void ColorClass::setTo(const ColorClass &inColor) {
  amountOfRed = inColor.amountOfRed;
  amountOfGreen = inColor.amountOfGreen;
  amountOfBlue = inColor.amountOfBlue;
}

int ColorClass::getRed() const {
  return amountOfRed;
}

int ColorClass::getGreen() const {
  return amountOfGreen;
}

int ColorClass::getBlue() const {
  return amountOfBlue;
}

//Each encodeVal corresponds to a color
//odd to even minus 1, even to odd add 1
void ColorClass::setEncode(const int encodeVal) {
  //Black (even, even, even)
  if (encodeVal == BLACK_COLOR) {
    if (amountOfRed % 2 == 1) {
      amountOfRed -= 1;
    }
    if (amountOfGreen % 2 == 1) {
      amountOfGreen -= 1;
    }
    if (amountOfBlue % 2 == 1) {
      amountOfBlue -= 1;
    }
  }
  //Red (odd, even, even)
  if (encodeVal == RED_COLOR) {
    if (amountOfRed % 2 == 0) {
      amountOfRed += 1;
    }
    if (amountOfGreen % 2 == 1) {
      amountOfGreen -= 1;
    }
    if (amountOfBlue % 2 == 1) {
      amountOfBlue -= 1;
    }
  }
  //Green (even, odd, even)
  if (encodeVal == GREEN_COLOR) {
    if (amountOfRed % 2 == 1) {
      amountOfRed -= 1;
    }
    if (amountOfGreen % 2 == 0) {
      amountOfGreen += 1;
    }
    if (amountOfBlue % 2 == 1) {
      amountOfBlue -= 1;
    }
  }
  //Blue (even, even, odd)
  if (encodeVal == BLUE_COLOR) {
    if (amountOfRed % 2 == 1) {
      amountOfRed -= 1;
    }
    if (amountOfGreen % 2 == 1) {
      amountOfGreen -= 1;
    }
    if (amountOfBlue % 2 == 0) {
      amountOfBlue += 1;
    }
  }
  //White (odd, odd, odd)
  if (encodeVal == WHITE_COLOR) {
    if (amountOfRed % 2 == 0) {
      amountOfRed += 1;
    }
    if (amountOfGreen % 2 == 0) {
      amountOfGreen += 1;
    }
    if (amountOfBlue % 2 == 0) {
      amountOfBlue += 1;
    }
  }
  //Yellow (odd, odd, even)
  if (encodeVal == YELLOW_COLOR) {
    if (amountOfRed % 2 == 0) {
      amountOfRed += 1;
    }
    if (amountOfGreen % 2 == 0) {
      amountOfGreen += 1;
    }
    if (amountOfBlue % 2 == 1) {
      amountOfBlue -= 1;
    }
  }
  //Magenta (odd, even, odd)
  if (encodeVal == MAGENTA_COLOR) {
    if (amountOfRed % 2 == 0) {
      amountOfRed += 1;
    }
    if (amountOfGreen % 2 == 1) {
      amountOfGreen -= 1;
    }
    if (amountOfBlue % 2 == 0) {
      amountOfBlue += 1;
    }
  }
  //Cyan (even, odd, odd)
  if (encodeVal == CYAN_COLOR) {
    if (amountOfRed % 2 == 1) {
      amountOfRed -= 1;
    }
    if (amountOfGreen % 2 == 0) {
      amountOfGreen += 1;
    }
    if (amountOfBlue % 2 == 0) {
      amountOfBlue += 1;
    }
  }
}

//if current color is even, set to min, otherwise set to max
void ColorClass::decodeColor(int &thisColor) {
  if (thisColor % 2 == 0) {
    thisColor = MIN_COLOR;
  }
  else {
    thisColor = MAX_COLOR;
  }
}

//decode each color
void ColorClass::decodeClass() {
  decodeColor(amountOfRed);
  decodeColor(amountOfGreen);
  decodeColor(amountOfBlue);
}
