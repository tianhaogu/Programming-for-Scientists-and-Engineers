#include <iostream>
using namespace std;

void printMenu();
double toThePower(const double val, const int power);
bool evaluateCubicFormula(const double aCoeff, const double bCoeff, 
	                      const double cCoeff, const double dCoeff, 
	                      const double xValue, double &resultVal);
double apporximateAreaWithRectangles(const double aCoeff, const double bCoeff, 
	                                 const double cCoeff, const double dCoeff, 
	                                 const double startX, const double endX, 
	                                 const int numRects);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main() {
  int userChoice;
  double aCoeff; double bCoeff; double cCoeff; double dCoeff;
  double startVal; double endVal;
  int numOfRecs; 
  while (true) {
  	printMenu();
  	cout << "YOUR CHOICE: ";
  	cin >> userChoice;
    if (userChoice == 3) {
      cout << "Thanks for using this program" << endl;
      break;
    }
    else {
      cout << "Enter (a b c d) for function y = a*x^3 + b*x^2 + c*x + d: ";
      cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;
      cout << "Now enter x start and end values: ";
      cin >> startVal >> endVal;
      if (userChoice == 1) {
        cout << "Enter the number of rectangles to use: ";
        cin >> numOfRecs;
        double recResult = apporximateAreaWithRectangles(aCoeff, bCoeff, cCoeff, 
        	                                             dCoeff, startVal, endVal, 
        	                                             numOfRecs);
        cout << "Rectangle result is: " << recResult << endl;
      }
      else if (userChoice == 2) {
      	double corrAns; double requiredPrecision;
        cout << "Enter correct answer: ";
        cin >> corrAns;
        cout << "Enter precision to reach: ";
        cin >> requiredPrecision;
        int count = 1;
        while (count <= 100) {
          double recArea = apporximateAreaWithRectangles(aCoeff, bCoeff, cCoeff, 
          	                                             dCoeff, startVal, endVal, 
	                                                     count);
          if (((recArea - corrAns) >= 0 && 
          	   (recArea - corrAns) <= requiredPrecision) || 
          	  ((corrAns - recArea) >= 0 && 
          	   (corrAns - recArea) <= requiredPrecision)) {
          	break;
          }
          count += 1;
        }
        if (count <= 100) {
          cout << "Rectangles needed to reach precision: " << count << endl; 
        }
        else {
          cout << "Tried 100 rectangles without reaching precision" << endl;
        }
      }
      else {
      }
    }
  }
  return 0;
}
#endif

void printMenu() {
  cout << "1 Approximate Integral Using Rectangles" << endl;
  cout << "2 Experiment With Rectangle Precision" << endl;
  cout << "3 Quit The Program" << endl;
}

double toThePower(const double val, const int power) {
  double powerResult = val;
  for (int i = 0; i < power-1; ++i) {
  	powerResult *= val;
  }
  return powerResult;
}

bool evaluateCubicFormula(const double aCoeff, const double bCoeff, 
	                      const double cCoeff, const double dCoeff, 
	                      const double xValue, double &resultVal) {
  resultVal = aCoeff * toThePower(xValue,3) + bCoeff * toThePower(xValue,2) + 
              cCoeff * xValue + dCoeff;
  if (resultVal >= 0) {
  	return true;
  }
  else {
  	resultVal *= (-1);
  	return false;
  }
}

double apporximateAreaWithRectangles(const double aCoeff, const double bCoeff, 
	                                 const double cCoeff, const double dCoeff, 
	                                 const double startX, const double endX, 
	                                 const int numRects) {
  double totalArea = 0.0;
  double midX = 0.0; 
  double tempStart = startX; 
  double intervalLength = (endX-startX) / numRects;
  double tempEnd = startX + intervalLength; 
  double funcheight = 0.0;
  for (int i = 1; i <= numRects; ++i) {
    midX = tempStart + intervalLength / 2;
    bool checkPos = evaluateCubicFormula(aCoeff, bCoeff, cCoeff, 
    	                                 dCoeff, midX, funcheight);
    totalArea += (intervalLength * funcheight);
    tempStart = tempEnd;
    tempEnd = tempStart + intervalLength;
  }
  return totalArea;
}