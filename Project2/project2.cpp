#include <iostream>
using namespace std;

/*Programmer: Tianhao Gu, Date: 02/21/2021
In this program I implement the beginnings of three class to represent
colors, images, and locations within an image.*/

//maximum and minimum color amount of pixels
const int MAX_COLOR = 1000;
const int MIN_COLOR = 0;

//default initialized row and column for RowColClass
const int NEW_CREATED_ROW = -99999;
const int NEW_CREATED_COL = -99999;

//default max bound for array that represents the image
const int ROW_BOUND = 10;
const int COL_BOUND = 18;

//global function for ColorClass constructor
const int setToOneColor(const int oneColor);

class ColorClass {
  public:
    //constructor and default constructor for the class
  	ColorClass();
  	ColorClass(const int inRed, const int inGreen, const int inBlue);
    
    //modifiers, set to a certain color
  	void setToBlack();
  	void setToRed();
  	void setToGreen();
  	void setToBlue();
  	void setToWhite();
    
    //set to multiple colors and check clipped or not
  	bool setTo(const int inRed, const int inGreen, const int inBlue);
    //set to the color of the class passed in
  	bool setTo(const ColorClass &inColor);
    //add/subtract color to/from the current class by the class passed in
  	bool addColor(const ColorClass &rhs);
  	bool subtractColor(const ColorClass &rhs);
    //multiply color by a factor
  	bool adjustBrightness(const double adjFactor);
    //print color values
  	void printComponentValues() const;

  private:
  	int amountOfRed;
  	int amountOfGreen;
  	int amountOfBlue;
    //set to one color and check whether there's clip
  	int setToColor(const int oneColor, bool &checkClip);
};

class RowColumnClass {
  public:
    //constructor and default constructor
    RowColumnClass();
    RowColumnClass(const int inRow, const int inCol);
    
    //modifiers, set row and column positions
    void setRowCol(const int inRow, const int inCol);
    void setRow(const int inRow);
    void setCol(const int inCol);
    
    //accessors, access the current row and column position
    int getRow() const;
    int getCol() const;
    
    //add row and colum index by the passed in class
    void addRowColTo(const RowColumnClass &inRowCol);
    //print the current row and column
    void printRowCol() const;

  private:
    int rowIndex;
    int colIndex;
};

class ColorImageClass {
  public:
    //constructor
    ColorImageClass();
    
    //initialize the current pixel to the color passed in
    void initializeTo(const ColorClass &inColor);
    //add the color of the passed in class to the current pixel
    bool addImageTo(const ColorImageClass &rhsImg);
    //initialize the current pixel and add passed in class to it
    bool addImages(const int numImgsToAdd, 
                   const ColorImageClass imagesToAdd []);
    //set pixel at current location specified by inRowCol parameter to 
    //the color specified via inColor parameter
    bool setColorAtLocation(const RowColumnClass &inRowCol, 
                            const ColorClass &inColor);
    
    //assign color of the passed in location to the passed in class
    bool getColorAtLocation(const RowColumnClass &inRowCol, 
                            ColorClass &outColor) const;
    
    //print all pixels of the whole image
    void printImage() const;

  private:
    ColorClass colorArray[ROW_BOUND][COL_BOUND];
    //check whether to return true or false
    bool checkCount(const int countTrue) const;
    //check whether the passed in location is out of bound or not
    bool checkValidPos(const int rowPos, const int colPos) const;
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main() {
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor)) {
    testColor.printComponentValues();
  }
  else {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor)) {
    testColor.printComponentValues();
  }
  else {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);
  
  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2) {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)) {
      testColor.printComponentValues();
    }
    else {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2) {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)) {
      testColor.printComponentValues();
    }
    else {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;
}
#endif

const int setToOneColor(const int oneColor) {
  if (oneColor > MAX_COLOR) {
    return MAX_COLOR;
  }
  else if (oneColor < MIN_COLOR) {
    return MIN_COLOR;
  }
  else {
    return oneColor;
  }
}

ColorClass::ColorClass(): amountOfRed(MAX_COLOR), 
                          amountOfGreen(MAX_COLOR), 
                          amountOfBlue(MAX_COLOR) {
}

ColorClass::ColorClass(const int inRed, const int inGreen, const int inBlue): 
  amountOfRed(setToOneColor(inRed)), 
  amountOfGreen(setToOneColor(inGreen)),
  amountOfBlue(setToOneColor(inBlue)) {
}

//set black to all minimum color
void ColorClass::setToBlack() {
  amountOfRed = MIN_COLOR;
  amountOfGreen = MIN_COLOR;
  amountOfBlue = MIN_COLOR;
}

void ColorClass::setToRed() {
  amountOfRed = MAX_COLOR;
  amountOfGreen = MIN_COLOR;
  amountOfBlue = MIN_COLOR;
}

void ColorClass::setToGreen() {
  amountOfRed = MIN_COLOR;
  amountOfGreen = MAX_COLOR;
  amountOfBlue = MIN_COLOR;
}

void ColorClass::setToBlue() {
  amountOfRed = MIN_COLOR;
  amountOfGreen = MIN_COLOR;
  amountOfBlue = MAX_COLOR;
}

//set white to all maximum color
void ColorClass::setToWhite() {
  amountOfRed = MAX_COLOR;
  amountOfGreen = MAX_COLOR;
  amountOfBlue = MAX_COLOR;
}

int ColorClass::setToColor(const int oneColor, bool &checkClip) {
  int finalColor;
  //Compare the given color with Max and Min value to decide clipping
  if (oneColor > MAX_COLOR) {
  	finalColor = MAX_COLOR;
  	checkClip = true;
  }
  else if (oneColor < MIN_COLOR) {
  	finalColor = MIN_COLOR;
  	checkClip = true;
  }
  else {
  	finalColor = oneColor;
  }
  return finalColor;
}

bool ColorClass::setTo(const int inRed, const int inGreen, const int inBlue) {
  bool checkClip = false;
  //set each color one by one and check clipping
  amountOfRed = setToColor(inRed, checkClip);
  amountOfGreen = setToColor(inGreen, checkClip);
  amountOfBlue = setToColor(inBlue, checkClip);
  return checkClip;
}

bool ColorClass::setTo(const ColorClass &inColor) {
  amountOfRed = inColor.amountOfRed;
  amountOfGreen = inColor.amountOfGreen;
  amountOfBlue = inColor.amountOfBlue;
  return false;
}

bool ColorClass::addColor(const ColorClass &rhs) {
  //Add each color and check clipping after calling the setTo function
  int finalRed = amountOfRed + rhs.amountOfRed;
  int finalGreen = amountOfGreen + rhs.amountOfGreen;
  int finalBlue = amountOfBlue + rhs.amountOfBlue;
  bool checkAdd = setTo(finalRed, finalGreen, finalBlue);
  return checkAdd;
}

bool ColorClass::subtractColor(const ColorClass &rhs) { //not tested
  //Subtract each color and check clipping after calling the setTo function
  int finalRed = amountOfRed - rhs.amountOfRed;
  int finalGreen = amountOfGreen - rhs.amountOfGreen;
  int finalBlue = amountOfBlue - rhs.amountOfBlue;
  bool checkSubtract = setTo(finalRed, finalGreen, finalBlue);
  return checkSubtract;
}

bool ColorClass::adjustBrightness(const double adjFactor) {
  //Multiply each color by a factor and check clipping after calling 
  //the setTo function
  int finalRed = int(amountOfRed * adjFactor);
  int finalGreen = int(amountOfGreen * adjFactor);
  int finalBlue = int(amountOfBlue * adjFactor);
  bool checkAdjust = setTo(finalRed, finalGreen, finalBlue);
  return checkAdjust;
}

void ColorClass::printComponentValues() const {
  cout << "R: " << amountOfRed << " G: " << amountOfGreen 
       << " B: " << amountOfBlue;
}

RowColumnClass::RowColumnClass(): rowIndex(NEW_CREATED_ROW), 
                                  colIndex(NEW_CREATED_COL) {
}

RowColumnClass::RowColumnClass(const int inRow, const int inCol) {
  rowIndex = inRow;
  colIndex = inCol;
}

void RowColumnClass::setRowCol(const int inRow, const int inCol) {
  rowIndex = inRow;
  colIndex = inCol;
}

void RowColumnClass::setRow(const int inRow) {
  rowIndex = inRow;
}

void RowColumnClass::setCol(const int inCol) {
  colIndex = inCol;
}

int RowColumnClass::getRow() const {
  return rowIndex;
}

int RowColumnClass::getCol() const {
  return colIndex;
}

void RowColumnClass::addRowColTo(const RowColumnClass &inRowCol) {
  rowIndex += inRowCol.getRow();
  colIndex += inRowCol.getCol();
}

void RowColumnClass::printRowCol() const {
  cout << '[' << rowIndex << ',' << colIndex << ']';
}

ColorImageClass::ColorImageClass() {
  //initialize each color pixel to black(all min color)
  for (int i = 0; i < ROW_BOUND; ++i) {
    for (int j = 0; j < COL_BOUND; ++j) {
      colorArray[i][j].setToBlack();
    }
  }
}

void ColorImageClass::initializeTo(const ColorClass &inColor) {
  for (int i = 0; i < ROW_BOUND; ++i) {
    for (int j = 0; j < COL_BOUND; ++j) {
      colorArray[i][j].setTo(inColor);
    }
  }
}

bool ColorImageClass::checkCount(const int countTrue) const {
  //check whether to return true or false by the cumulative count
  if (countTrue == 0) {
    return false;
  }
  else {
    return true;
  }
}

bool ColorImageClass::addImageTo(const ColorImageClass &rhsImg) {
  int countTrue = 0;
  //for each pixel, add the provided color to the original color and use count
  //to check whether's there's any one that clips
  for (int i = 0; i < ROW_BOUND; ++i) {
    for (int j = 0; j < COL_BOUND; ++j) {
      if (colorArray[i][j].addColor(rhsImg.colorArray[i][j]) == true) {
        countTrue += 1;
      }
    }
  }
  return checkCount(countTrue);
}

bool ColorImageClass::addImages(const int numImgsToAdd, 
                                const ColorImageClass imagesToAdd []) {
  //first set each pixel to initialize color (all black, min color)
  for (int i = 0; i < ROW_BOUND; ++i) {
    for (int j = 0; j < COL_BOUND; ++j) {
      colorArray[i][j].setToBlack();
    }
  }
  //then add <num> colors in the passed in array, and check clipping
  int countTrue = 0;
  for (int i = 0; i < numImgsToAdd; ++i) {
    if (addImageTo(imagesToAdd[i]) == true) {
      countTrue += 1;
    }
  }
  return checkCount(countTrue);
}

bool ColorImageClass::checkValidPos(const int rowPos, const int colPos) const {
  if ((rowPos <= ROW_BOUND && rowPos >= 0) && 
      (colPos <= COL_BOUND && colPos >= 0)) {
    return true;
  }
  else {
    return false;
  }
}

bool ColorImageClass::setColorAtLocation(const RowColumnClass &inRowCol, 
                                         const ColorClass &inColor) {
  int rowPos = inRowCol.getRow();
  int colPos = inRowCol.getCol();
  //if the passed in position is valid, set the specific location to the 
  //passed in color
  if (checkValidPos(rowPos, colPos) == true) {
    return !(colorArray[rowPos][colPos].setTo(inColor)); 
  } 
  else {
    return false;
  }
}

bool ColorImageClass::getColorAtLocation(const RowColumnClass &inRowCol, 
                                         ColorClass &outColor) const {
  int rowPos = inRowCol.getRow();
  int colPos = inRowCol.getCol();
  //if the passed in position is valid, set the passed in color to the 
  //color in this location
  if (checkValidPos(rowPos, colPos) == true) {
    return !(outColor.setTo(colorArray[rowPos][colPos]));
  }
  else {
    return false;
  }
}

void ColorImageClass::printImage() const {
  for (int i = 0; i < ROW_BOUND; ++i) {
    for (int j = 0; j < COL_BOUND; ++j) {
      colorArray[i][j].printComponentValues();
      if (!(j == COL_BOUND - 1)) {
        cout << "--";
      }
    }
    cout << endl;
  }
}