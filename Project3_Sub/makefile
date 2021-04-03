proj3.exe: ColorClass.o ColorImageClass.o MessageClass.o RowColumnClass.o printMenu.o printEnd.o printHeadError.o printColorError.o checkHeadEndFail.o checkColorEndFail.o project3.o constants.h
	g++ ColorClass.o ColorImageClass.o MessageClass.o RowColumnClass.o printMenu.o printEnd.o printHeadError.o printColorError.o checkHeadEndFail.o checkColorEndFail.o project3.o constants.h -o proj3.exe

project3.o: project3.cpp
	g++ -std=c++98 -Wall -c project3.cpp -o project3.o

ColorClass.o: ColorClass.cpp ColorClass.h
	g++ -std=c++98 -Wall -c ColorClass.cpp -o ColorClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h
	g++ -std=c++98 -Wall -c ColorImageClass.cpp -o ColorImageClass.o

MessageClass.o: MessageClass.cpp MessageClass.h
	g++ -std=c++98 -Wall -c MessageClass.cpp -o MessageClass.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h
	g++ -std=c++98 -Wall -c RowColumnClass.cpp -o RowColumnClass.o

printMenu.o: printMenu.cpp printMenu.h
	g++ -std=c++98 -Wall -c printMenu.cpp -o printMenu.o

printEnd.o: printEnd.cpp printEnd.h
	g++ -std=c++98 -Wall -c printEnd.cpp -o printEnd.o

printHeadError.o: printHeadError.cpp printHeadError.h
	g++ -std=c++98 -Wall -c printHeadError.cpp -o printHeadError.o

printColorError.o: printColorError.cpp printColorError.h
	g++ -std=c++98 -Wall -c printColorError.cpp -o printColorError.o

checkHeadEndFail.o: checkHeadEndFail.cpp checkHeadEndFail.h
	g++ -std=c++98 -Wall -c checkHeadEndFail.cpp -o checkHeadEndFail.o

checkColorEndFail.o: checkColorEndFail.cpp checkColorEndFail.h
	g++ -std=c++98 -Wall -c checkColorEndFail.cpp -o checkColorEndFail.o

clean: 
	rm -rf project3.o ColorClass.o ColorImageClass.o MessageClass.o RowColumnClass.o printMenu.o printEnd.o printHeadError.o printColorError.o checkHeadEndFail.o checkColorEndFail.o proj3.exe