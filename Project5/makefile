proj5.exe: CarClass.o EventClass.o IntersectionSimulationClass.o random.o project5.o constants.h
	g++ CarClass.o EventClass.o IntersectionSimulationClass.o random.o project5.o constants.h -o proj5.exe

project5.o: project5.cpp LinkedNodeClass.h LinkedNodeClass.inl SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl
	g++ -std=c++98 -Wall -c project5.cpp -o project5.o

CarClass.o: CarClass.cpp CarClass.h
	g++ -std=c++98 -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h
	g++ -std=c++98 -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h LinkedNodeClass.h LinkedNodeClass.inl SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl
	g++ -std=c++98 -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

random.o: random.cpp random.h
	g++ -std=c++98 -Wall -c random.cpp -o random.o

clean:
	rm -rf project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o proj5.exe