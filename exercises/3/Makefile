#Makefile for triangle monotony polygon

main: main.o Vertex.o Polygon.o
	g++ -o main main.o Vertex.o Polygon.o
main.o:	main.cpp
	g++ -c main.cpp
Polygon.o: Polygon.cpp Polygon.h Vertex.h
	g++ -c Polygon.cpp 	
Vertex.o: Vertex.cpp Vertex.h
	g++ -c Vertex.cpp
clean: 
	rm -f *.o main
