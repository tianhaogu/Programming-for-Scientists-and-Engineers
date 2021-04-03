#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "constants.h"
#include "ColorClass.h"
#include "ColorImageClass.h"
#include "MessageClass.h"
#include "RowColumnClass.h"
#include "printMenu.h"
#include "printHeadError.h"
#include "printColorError.h"
#include "printEnd.h"
#include "checkHeadEndFail.h"
#include "checkColorEndFail.h"
using namespace std;

/*Programmer: Tianhao Gu, Date: 03/18/2021
In this program I implement the image modification based on the initial image
I read in, and then perform encoding and decoding operations based on 
different user choices, and then output the modified image to a new file.*/

int main(int argc, char* argv[]) {
  //check number of arguments
  if (argc == 1) {
    cout << "Usage: ./project3.exe <startPPM.ppm>" << endl;
    exit(2);
  }
  if (argc > 2) {
    cout << "Error: Incorrect number of arguments" << endl;
    exit(2);
  }
  //open the file on command line argument
  ifstream inFile;
  inFile.open(argv[1]);
  cout << "Reading initial image from: " << argv[1] << endl;
  //check whether can open or not
  if (inFile.fail()) {
    cout << "Unable to open input file!" << endl;
    exit(3);
  }
  //construct ColorImageClass object, read head of file and do error checking
  ColorImageClass testImage;
  string magicNumber;
  int numCol;
  int numRow;
  int maxColor;
  testImage.readCheckHeader(magicNumber, numCol, numRow, maxColor, inFile);
  //set row and col and color arrayfor the constructed ColorImageClass object
  testImage.initializeTo(numRow, numCol);
  int redPixel;
  int greenPixel;
  int bluePixel;
  int countRow = 0;
  int countCol = 0;
  int countPixel = 0;
  //use nested while loops to read in all color values and do error checkings
  while (countRow < numRow) {
    while (countCol < numCol) {
      while (countPixel < PIXEL_NUMBER) {
        testImage.checkPixelValid(redPixel, greenPixel, bluePixel, countRow, 
                                  countCol, countPixel, inFile);
        //if no error, construct a ColorClass according to the colors readed
        //and put this class into the 2d array of the Image
        ColorClass testColor;
        testColor.setTo(redPixel, greenPixel, bluePixel);
        RowColumnClass testRowCol(countRow, countCol);
        testImage.setColorAtLocation(testRowCol, testColor);
        countPixel += 1;
      }
      countPixel = 0;
      countCol += 1;
    }
    countCol = 0;
    countRow += 1;
  }
  //check if more data values than expected
  int checkAddition;
  inFile >> checkAddition;
  if (!(inFile.eof() || inFile.fail())) {
    printEnd(testImage.getRowSize(), 0);
    exit(3);
  }
  cout << "Image read successful: Yes" << endl;
  inFile.close();
  bool checkExit = false;
  int userChoice;
  int msgRowPlc;
  int msgColPlc;
  while (checkExit == false) {
    printMenu();
    cin >> userChoice;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(IGNORE_NUMBER, '\n');
      cout << "Error: Not an int, please input a valid int" << endl;
    }
    else {
      if (userChoice == 1) {
        //enter message file, row and column to be placed and do error checking
        cout << "Enter name of file containing message: ";
        ifstream inMsg;
        string msgFile;
        cin >> msgFile;
        cout << "Enter row and column for message placement: ";
        cin >> msgRowPlc >> msgColPlc;
        inMsg.open(msgFile.c_str());
        bool checkOpenFail = false;
        if (inMsg.fail()) {
          cout << "Unable to open input file!" << endl;
          checkOpenFail = true;
        }
        //check numCol value in the message file
        if (checkOpenFail == false) {
          //if the input file is valid, then call the readColorPixel function of 
          //the ColorImageClass to read the file from the beginning, perform
          //error checking, build the MessageClass object inside this function,
          //encode the message vias the MessageClass and then perform the change
          //to the ColorImageClass for further output.
          testImage.readColorPixel(msgRowPlc, msgColPlc, inMsg, inFile);
        }
        inMsg.close();
      }
      else if (userChoice == 2) {
        //decode the current image
        testImage.decodeImg();
        cout << "Image modified to decoded image contents" << endl;
      }
      else if (userChoice == 3) {
        cout << "Enter name of file to write image to: ";
        string writeFile;
        //check whether can open the output file
        cin >> writeFile;
        ofstream outFile;
        outFile.open(writeFile.c_str());
        bool checkOpen = true;
        if (outFile.fail()) {
          cout << "Error: File written to cannot open" << endl;
          checkOpen = false;
        }
        if (checkOpen == true) {
          cout << "Image write successful: Yes" << endl;
          //print the image to the output file
          outFile << "P3" << endl;
          outFile << testImage.getColSize() << ' ' 
                  << testImage.getRowSize() << endl;
          outFile << MAX_COLOR << endl;
          testImage.printImage(outFile);
        }
        outFile.close();
      }
      //exit the program
      else if (userChoice == 4) {
        cout << "Thanks for using this program!" << endl;
        checkExit = true;
      }
      else {
        cout << "Error: Not a valid int choice, enter a new int" << endl;
      }
    }
  }
  return 0;
}
