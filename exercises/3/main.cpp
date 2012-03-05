//#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <utility>
#include "Polygon.h"
#include "Vertex.h"

typedef std::pair<long, long> point; 
typedef std::pair<point, int> Chain;
 
point getPoint(std::string str) { 
	long x = 0; 
	long y = 0; 
	std::string::iterator it; 

	for(it = str.begin(); *it != ','; ++it) { 
		if (*it > '0' && *it < '9') { 
			x = x * 10 + (*it - '0');  
		} 
	}  

	for(; it < str.end(); ++it) { 
		if (*it > '0' && *it < '9') { 
			y = y * 10 + (*it - '0');  
		} 
	}

	return std::make_pair(x, y);  
} 

void read(std::vector<Vertex>& upper, std::vector<Vertex>& lower) { 
	//std::fstream in("input.txt", std::fstream::in);  	
	size_t size = 0;
	std::string str; 
	int i = 1;  
	point m; 
	 		
	std::cin >> size; 	

	if (size < 2) { 
		return; 
	} 

	std::getline(std::cin, str); 
	std::getline(std::cin, str); 
	m = getPoint(str);
	Vertex *t = new Vertex(1, m);
	upper.push_back(*t); 		
		
	for(i = 2; i <= size; ++i) { 
		std::getline(std::cin, str); 
		m = getPoint(str); 
		if (m.first < upper.back().v.first) {
			break; 
		}  
		t = new Vertex(i, m);
		upper.push_back(*t); 
	} 
	
	if (i == size + 1) { 
		t = new Vertex((upper.end() - 1)->num, (upper.end() - 1)->v);
		lower.push_back(*t);
		t = new Vertex((upper.begin())->num, (upper.begin())->v); 
		lower.push_back(*t);	
		return; 
	} 

	t = new Vertex((upper.end() - 1)->num, (upper.end() - 1)->v); 
	lower.push_back(*t); 
	t = new Vertex(i, m);
	lower.push_back(*t);
	++i; 
	
	for(; i <= size; ++i) { 
		std::getline(std::cin, str); 
		m = getPoint(str); 
		t = new Vertex(i, m);
		lower.push_back(*t); 
	} 

	t = new Vertex((upper.begin())->num, (upper.begin())->v);
	lower.push_back(*t); 

	/*for(std::vector<Vertex>::iterator it = lower.begin(); it < lower.end(); ++it) {
		std::cout << it->num << " " << /*<< it->v.first << " " << it->v.second << std::endl;		
	} */
} 

int main() { 
	//std::fstream output("output.txt", std::fstream::out); 
	std::vector<Vertex> upperChain;
	std::vector<Vertex> lowerChain;  	
	
	read(upperChain, lowerChain/*, output*/); 
	
	Polygon poly(upperChain, lowerChain);
	poly.triangulation();
	poly.printTriangles();/*output);*/

	return 0; 
} 


