#Makefile for triangle monotony polygon

main: main.o Polygon.o
	g++ -o main main.o Polygon.o 
main.o:	main.cpp
	g++ -c main.cpp
Polygon.o: Polygon.cpp Polygon.h
	g++ -c Polygon.cpp 	
clean: 
	rm -f *.o main
