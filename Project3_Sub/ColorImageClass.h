#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include <iostream>
#include <fstream>
#include "ColorClass.h"
#include "MessageClass.h"
#include "RowColumnClass.h"
#include "constants.h"
#include "checkColorEndFail.h"
#include "checkHeadEndFail.h"
#include "printColorError.h"
#include "printHeadError.h"
#include "printEnd.h"
using namespace std;

class ColorImageClass {
  public:
    //constructor, default constructor and destructor
    ColorImageClass();
    //ColorImageClass(const int numRow, const int numCol);
    ~ColorImageClass();

    int getRowSize() const;
    int getColSize() const;
    
    //constructor the 2d array  and set rowNum and colNum
    void initializeTo(const int numRow, const int numCol);
    
    //read the head file and check error
    void readCheckHeader(string &magicNumber, int &numCol, int &numRow,
                         int &maxColor, ifstream &inFile);
    //read pixels and check error
    void checkPixelValid(int &redPixel, int &greenPixel, int &bluePixel, 
                         int &countRow, int &countCol, int &countPixel, 
                         ifstream &inFile);

    //set pixel at current location specified by inRowCol parameter to 
    //the color specified via inColor parameter
    void setColorAtLocation(const RowColumnClass &inRowCol, 
                            const ColorClass &inColor);
    
    void readColorPixel(const int msgRowPlc, const int msgColPlc, 
                        ifstream &inMsg, ifstream &inFile);

    //encode the current location pixel by the passed in message
    void encodeAtLocation(const RowColumnClass &beginPlc, 
                          const RowColumnClass &endPlc, 
                          const MessageClass &testMessage);
    //decode current image
    void decodeImg();
    
    //print all pixels of the whole image
    ostream &printImage(ostream &outFile) const;

  private:
    ColorClass **colorArray;
    int rowSize;
    int colSize;
};
#endif