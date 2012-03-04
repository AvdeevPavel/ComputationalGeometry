#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Polygon.h"

typedef std::pair<long, long> point; 

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

void read(std::vector<point>& upper, std::vector<point>& lower, std::fstream &out) { 
	std::fstream input("input.txt", std::fstream::in);  	
	size_t size = 0;
	std::string str; 
	int i = 0;  
	point m; 
	 		
	input >> size; 	

	if (size < 2) { 
		return; 
	} 

	std::getline(input, str); 
	std::getline(input, str); 
	m = getPoint(str);
	upper.push_back(m); 		
		
	for(i = 1; i < size; ++i) { 
		std::getline(input, str); 
		m = getPoint(str); 
		if (m.first < upper.back().first) {
			break; 
		}  
		upper.push_back(m); 
	} 
	
	if (i == size) { 
		lower.push_back(*(upper.end() - 1)); 
		lower.push_back(*(upper.begin()));	
		return; 
	} 

	lower.push_back(*(upper.end() - 1)); 
	lower.push_back(m);
	++i; 
	
	for(; i < size; ++i) { 
		std::getline(input, str); 
		m = getPoint(str); 
		lower.push_back(m); 
	} 

	lower.push_back(*(upper.begin())); 

	/*for(std::vector<point>::iterator it = lower.begin(); it < lower.end(); ++it) {
		std::cout << it->first << " " << it->second << std::endl;		
	} */	
} 

int main() { 
	std::fstream output("output.txt", std::fstream::out); 
	std::vector<point> upperChain;
	std::vector<point> lowerChain;  	
	
	read(upperChain, lowerChain, output); 
	
	Polygon poly(upperChain, lowerChain);
	poly.triangulation();
	poly.printTriangles(output);

	return 0; 
} 


