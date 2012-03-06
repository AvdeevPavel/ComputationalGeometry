#ifndef VERTEX_H_
#define VERTEX_H_
#include <utility>

typedef std::pair<long long, long long> point; 

struct Vertex { 	 
	int num;
	point v;
	
	Vertex(int n, point &m);  
};

#endif 
