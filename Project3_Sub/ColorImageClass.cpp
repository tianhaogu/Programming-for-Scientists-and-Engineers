#include <iostream>
#include <fstream>
#include "ColorImageClass.h"
using namespace std;

ColorImageClass::ColorImageClass() {
  rowSize = 0;
  colSize = 0;
}

//delete the 2d array
ColorImageClass::~ColorImageClass() {
  for (int i = 0; i < rowSize; ++i) {
    delete [] colorArray[i];
    colorArray[i] = NULL;
  }
  delete [] colorArray;
  colorArray = NULL;
  rowSize = MIN_INDEX;
  colSize = MIN_INDEX;
}

int ColorImageClass::getRowSize() const {
  return rowSize;
}
int ColorImageClass::getColSize() const {
  return colSize;
}

void ColorImageClass::initializeTo(const int numRow, const int numCol) {
  colorArray = new ColorClass*[numRow];
  for (int i = 0; i < numRow; ++i) {
    colorArray[i] = new ColorClass[numCol];
  }
  rowSize = numRow;
  colSize = numCol;
}

void ColorImageClass::readCheckHeader(string &magicNumber, int &numCol, 
                                      int &numRow, int &maxColor, 
                                      ifstream &inFile) {
  //read title "P3" and do error checking
  inFile >> magicNumber;
  checkHeadEndFail(inFile);
  if (magicNumber != PROJECT_TITLE) {
    printHeadError();
    exit(3);
  }
  //read column number and do error checking
  inFile >> numCol;
  checkHeadEndFail(inFile);
  if (numCol > MAX_PIXEL || numCol < MIN_PIXEL) {
    printHeadError();
    exit(3);
  }
  //read row number and do error checking
  inFile >> numRow;
  checkHeadEndFail(inFile);
  if (numRow > MAX_PIXEL || numRow < MIN_PIXEL) {
    printHeadError();
    exit(3);
  }
  //read maximum color and do error checking
  inFile >> maxColor;
  checkHeadEndFail(inFile);
  if (maxColor != MAX_COLOR) {
    printHeadError();
    exit(3);
  }
}

void ColorImageClass::checkPixelValid(int &redPixel, int &greenPixel, 
                                      int &bluePixel, int &countRow, 
                                      int &countCol, int &countPixel, 
                                      ifstream &inFile) {
  //read in red pixel and do error checking
  if (countPixel == RED_PIXEL) {
    inFile >> redPixel;
    checkColorEndFail(countRow, countCol, inFile);
    if (redPixel > MAX_COLOR || redPixel < MIN_COLOR) {
      printColorError(countRow, countCol, 1);
      exit(3);
    }
  }
  //read in green pixel and do error checking
  if (countPixel == GREEN_PIXEL) {
    inFile >> greenPixel;
    checkColorEndFail(countRow, countCol, inFile);
    if (greenPixel > MAX_COLOR || greenPixel < MIN_COLOR) {
      printColorError(countRow, countCol, 1);
      exit(3);
    }
  }
  //read in blue pixel and do error checking
  if (countPixel == BLUE_PIXEL) {
    inFile >> bluePixel;
    checkColorEndFail(countRow, countCol, inFile);
    if (bluePixel > MAX_COLOR || bluePixel < MIN_COLOR) {
      printColorError(countRow, countCol, 1);
      exit(3);
    }
  }
}

void ColorImageClass::setColorAtLocation(const RowColumnClass &inRowCol, 
                                         const ColorClass &inColor) {
  int rowPos = inRowCol.getRow();
  int colPos = inRowCol.getCol();
  colorArray[rowPos][colPos].setTo(inColor);
}

void ColorImageClass::readColorPixel(const int msgRowPlc, const int msgColPlc, 
                                     ifstream &inMsg, ifstream &inFile) {
  int msgCol;
  inMsg >> msgCol;
  bool checkMsgColFail = false;
  if (inMsg.eof()) {
    printHeadError();
    exit(3);
    checkMsgColFail = true;
  }
  if (inMsg.fail() || 
      ((!inMsg.fail()) && msgCol > MAX_PIXEL) || 
      ((!inMsg.fail()) && msgCol < MIN_PIXEL)) {
    printHeadError();
    checkMsgColFail = true;
  }
  //check numRow value in the message file
  if (checkMsgColFail == false) {
    int msgRow;
    inMsg >> msgRow;
    bool checkMsgRowFail = false;
    if (inMsg.eof()) {
      printHeadError();
      exit(3);
      checkMsgRowFail = true;
    }
    if (inMsg.fail() || 
        ((!inMsg.fail()) && msgRow > MAX_PIXEL) || 
        ((!inMsg.fail()) && msgRow < MIN_PIXEL)) {
      printHeadError();
      checkMsgRowFail = true;
    }
    //check color value in the message file one by one
    if (checkMsgRowFail == false) {
      bool checkMsgCorFail = false;
      //construct a MessageClass with the 2d array to store color values
      MessageClass testMessage(msgRow, msgCol);
      int msgVal;
      for (int i = 0; i < msgRow; ++i) {
        for (int j = 0; j < msgCol; ++j) {
          inMsg >> msgVal;
          if (inMsg.eof()) {
            if (inMsg.fail()) {
              printEnd(i, j);
              checkMsgCorFail = true;
            }
          }
          if (inMsg.fail() || 
              ((!inMsg.fail()) && msgVal > MAX_ENCODE) || 
              ((!inMsg.fail()) && msgVal < MIN_ENCODE)) {
            printColorError(i, j, 2);
            checkMsgCorFail = true;
            j = msgCol - 1;
            i = msgRow - 1;
          }
          //if no error occurs, set the encoded color value to the array
          if (checkMsgCorFail == false) {
            RowColumnClass testRowCol(i, j);
            testMessage.setVal(testRowCol, msgVal);
          }
        }
      }
      //check if more data values than expected
      int checkRemaining;
      inMsg >> checkRemaining;
      if (!(inMsg.eof() || inFile.fail())) {
        printEnd(testMessage.getRowSize(), 0);
        checkMsgCorFail = true;
      }
      if (checkMsgCorFail == false) {
        //get ended row and col of the encoded range, if part of message
        //out of bound, ignore these parts
        int rowEnd = msgRowPlc + msgRow - 1;
        int colEnd = msgColPlc + msgCol - 1;
        if (rowEnd >= getRowSize()) {
          rowEnd = getRowSize() - 1;
        }
        if (colEnd >= getColSize()) {
          colEnd = getColSize() - 1;
        }
        //encode the message to the current image
        RowColumnClass beginPlc(msgRowPlc, msgColPlc);
        RowColumnClass endPlc(rowEnd, colEnd);
        encodeAtLocation(beginPlc, endPlc, testMessage);
        cout << "Message encode successful: Yes" << endl;
      }
    }
  }
}

//first get the value of the message in each pixel,
//then call the setEncode function of ColorClass to encode the color
void ColorImageClass::encodeAtLocation(const RowColumnClass &beginPlc, 
                                       const RowColumnClass &endPlc, 
                                       const MessageClass &testMessage) {
  for (int i = beginPlc.getRow(); i <= endPlc.getRow(); ++i) {
    for (int j = beginPlc.getCol(); j <= endPlc.getCol(); ++j) {
      int currentMsgRow = i - beginPlc.getRow();
      int currentMsgCol = j - beginPlc.getCol();
      int encodeVal = testMessage.getVal(currentMsgRow, currentMsgCol);
      colorArray[i][j].setEncode(encodeVal);
    }
  }
}

//call the decodeClass function of ColorClass one by one
void ColorImageClass::decodeImg() {
  for (int i = 0; i < rowSize; ++i) {
    for (int j = 0; j < colSize; ++j) {
      colorArray[i][j].decodeClass();
    }
  }
}

//print each color in each pixel one by one
ostream &ColorImageClass::printImage(ostream &outFile) const {
  for (int i = 0; i < rowSize; ++i) {
    for (int j = 0; j < colSize; ++j) {
      outFile << colorArray[i][j].getRed() << ' '
              << colorArray[i][j].getGreen() << ' '
              << colorArray[i][j].getBlue();
      if (j != colSize - 1) {
        outFile << ' ';
      }
    }
    outFile << endl;
  }
  return outFile;
}
