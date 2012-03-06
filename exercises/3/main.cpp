#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include "Polygon.h"
#include "Vertex.h"

typedef std::pair<long long, long long> point; 
typedef std::pair<point, int> Chain;
 
/*point getPoint(std::string str) { 
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
}*/ 

void read(std::vector<Vertex>& upper, std::vector<Vertex>& lower) { 
	//std::fstream in("input.txt", std::fstream::in);  	
	size_t size = 0;
	std::string str; 
	int i = 0;  
	point m; 
	long long x = 0; 
	long long y = 0; 		

	std::cin >> size; 	
	
	if (size < 2) { 
		return; 
	} 

	std::getline(std::cin, str); 
	std::getline(std::cin, str); 
	const char *c = str.c_str();

	
	sscanf(c, "(%lld, %lld)", &x, &y);
	m = std::make_pair(x, y);
	Vertex *t = new Vertex(0, m);
	upper.push_back(*t); 		
		
	for(i = 1; i < size; ++i) { 
		std::getline(std::cin, str); 
		c = str.c_str(); 
		sscanf(c, "(%lld, %lld)", &x, &y);
		if (x < upper.back().v.first) {
			break; 
		}  
		m = std::make_pair(x, y);
		t = new Vertex(i, m);
		upper.push_back(*t); 
	} 
	
	if (i == size) { 
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
	
	for(; i < size; ++i) { 
		std::getline(std::cin, str); 
		c = str.c_str(); 
		sscanf(c, "(%lld, %lld)", &x, &y);		
		m = std::make_pair(x, y);
		t = new Vertex(i, m);
		lower.push_back(*t); 
	} 

	t = new Vertex((upper.begin())->num, (upper.begin())->v);
	lower.push_back(*t); 

	/*std::cout << "lower " << lower.size() <<std::endl; 
	for(std::vector<Vertex>::iterator it = lower.begin(); it < lower.end(); ++it) {
		std::cout << it->num << " " << it->v.first << " " << it->v.second << std::endl;		
	} 
	std::cout << std::endl;*/
} 

int main() { 
	//std::fstream output("output.txt", std::fstream::out); 
	std::vector<Vertex> upperChain;
	std::vector<Vertex> lowerChain;  	
	
	read(upperChain, lowerChain/*, output*/); 
	
	/*std::cout << "upper" << std::endl;
	for(std::vector<Vertex>::iterator it = upperChain.begin(); it < upperChain.end(); ++it) {
		std::cout << it->num << " " << it->v.first << " " << it->v.second << std::endl;		
	}

	std::cout << "lower" << std::endl;
	for(std::vector<Vertex>::iterator it = lowerChain.begin(); it < lowerChain.end(); ++it) {
		std::cout << it->num << " " << it->v.first << " " << it->v.second << std::endl;		
	} */
	
	Polygon poly(upperChain, lowerChain);
	poly.triangulation();
	poly.printTriangles();/*output);*/

	return 0; 
} 


