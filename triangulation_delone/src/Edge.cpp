#include "algo/Edge.h"
#include <cassert>
#include <cstdio>

namespace algo 
{ 

Edge::Edge(my_point* const x_, my_point *const y_): x(x_), y(y_) {
}  

Edge::Edge(const Edge& b): x(b.x), y(b.y) { 
} 

my_point Edge::getNotEquelEnd(const Edge &second) const { 
	if (*x == *second.y) { 
		return *y;
	} else if (*y == *second.x) {
		return *x; 
	} else if (*x == *second.x) {
		return *y; 
	} else if (*y == *second.y) {
		return *x; 
	} 

	assert(false);
	return my_point(0, 0);	
}


bool Edge::operator==(const Edge &a) const { 
	return ( ((*x == *a.x) && (*y == *a.y)) || ((*y == *a.x) && (*x == *a.y)) ) ;
}  

bool Edge::operator!=(const Edge &a) const { 
	return !(*this == a);
} 

bool Edge::isWedge() const { 
	return x->isInfPoint() || y->isInfPoint();
} 

void Edge::print() const { 
	if (isWedge() == false) { 
		printf("Triangle Edge:  (%d, %d)--(%d, %d)\n", x->xy.x, x->xy.y, y->xy.x, y->xy.y);
	} else { 
		printf("Wedge Edge:  (%d, %d, %d)--(%d, %d, %d)\n", x->xy.x, x->xy.y, x->z, y->xy.x, y->xy.y, y->z);
	} 
} 
 
} 
