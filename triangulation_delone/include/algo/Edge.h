#ifndef EDGE_H_
#define EDGE_H_ 

#include "algo/my_point.h"

using algo::my_point;

namespace algo { 	
	struct Edge {
		my_point* x; 
		my_point* y; 		

		Edge(my_point* const x_, my_point *const y_); 
		Edge(const Edge& b); 

		my_point getNotEquelEnd(const Edge &second) const;

		bool operator==(const Edge &a) const; 
		bool operator!=(const Edge &a) const; 	

		bool isWedge() const;		

		void print() const;
	}; 
} 

#endif

