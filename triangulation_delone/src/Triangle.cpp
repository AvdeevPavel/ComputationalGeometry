#include "algo/Triangle.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>

/*Constructors*/
namespace algo { 

Triangle::Triangle(my_point* const a, my_point* const b, my_point* const c) {  

	if (a->isInfPoint() || b->isInfPoint() || c->isInfPoint() ) { 
		coordinates.push_back(a);
		coordinates.push_back(b);
		coordinates.push_back(c); 
		isWedge = true;
	} else if (orient(*a, *b, *c) > 0) { 
		coordinates.push_back(a);
		coordinates.push_back(b);
		coordinates.push_back(c); 
		isWedge = false;			
	} else if (orient(*a, *c, *b) > 0) { 
		coordinates.push_back(a);
		coordinates.push_back(c);
		coordinates.push_back(b); 
		isWedge = false;
	} 
}

	
my_point* Triangle::findOtherCoordinate(const Edge& e) const { 
	for(std::vector<my_point*>::const_iterator it = coordinates.begin(); it != coordinates.end(); ++it) { 
		if ((*(*it) != *e.x) && (*(*it) != *e.y))
			return *it;
	} 
	assert(false);
	return NULL;
}

Edge Triangle::getEdgeClockwiseOrient(const Edge& e) const { 
	my_point *point = findOtherCoordinate(e);
	
	if (orient(*point, *e.x, *e.y) > 0) { 
		return Edge(e.x, e.y);
	} else { 
		return Edge(e.y, e.x);
	} 
} 

bool Triangle::isIntoCircleForTriangle(const my_point& a) const { 
	long long sqrAx = a.xy.x * (long long)(a.xy.x);
	long long sqrAy = a.xy.y * (long long)(a.xy.y);
	long long coord0x = coordinates[0]->xy.x * (long long)(coordinates[0]->xy.x);
	long long coord0y = coordinates[0]->xy.y * (long long)(coordinates[0]->xy.y);
	long long coord1x = coordinates[1]->xy.x * (long long)(coordinates[1]->xy.x);
	long long coord1y = coordinates[1]->xy.y * (long long)(coordinates[1]->xy.y);
	long long coord2x = coordinates[2]->xy.x * (long long)(coordinates[2]->xy.x);
	long long coord2y = coordinates[2]->xy.y * (long long)(coordinates[2]->xy.y);
	
	long long det1 = (coordinates[1]->xy.y - a.xy.y) * ((coord2x - sqrAx) + (coord2y - sqrAy)) - \
			 (coordinates[2]->xy.y - a.xy.y) * ((coord1x - sqrAx) + (coord1y - sqrAy)); 
	long long det2 = (coordinates[0]->xy.y - a.xy.y) * ((coord2x - sqrAx) + (coord2y - sqrAy)) - \
			 (coordinates[2]->xy.y - a.xy.y) * ((coord0x - sqrAx) + (coord0y - sqrAy)); 
	long long det3 = (coordinates[0]->xy.y - a.xy.y) * ((coord1x - sqrAx) + (coord1y - sqrAy)) - \
			 (coordinates[1]->xy.y - a.xy.y) * ((coord0x - sqrAx) + (coord0y - sqrAy)); 

	long long res0 = (coordinates[0]->xy.x - a.xy.x) * det1 - (coordinates[1]->xy.x - a.xy.x) * det2 + (coordinates[2]->xy.x - a.xy.x) * det3;
	
	return (res0 > 0);
} 

bool Triangle::isIntoCircleForWedge(const Edge &first, const Edge &second) const { 
	my_point point = first.getNotEquelEnd(second);
	return (orient(point, *second.x, *second.y) < 0);
}

bool Triangle::isOnEdgeInTriangle(const my_point& point) const { 
	if (orient(*coordinates[0], *coordinates[1], point) == 0)
		return true; 

	if (orient(*coordinates[1], *coordinates[2], point) == 0)
		return true; 

	if (orient(*coordinates[2], *coordinates[0], point) == 0)
		return true; 

	return false; 
} 

Edge Triangle::getOnEdgeInTriangle(const my_point& point) const { 
	if (orient(*coordinates[0], *coordinates[1], point) == 0)
		return Edge(coordinates[0], coordinates[1]); 

	if (orient(*coordinates[1], *coordinates[2], point) == 0)
		return Edge(coordinates[1], coordinates[2]);

	if (orient(*coordinates[2], *coordinates[0], point) == 0)
		return Edge(coordinates[2], coordinates[0]); 

	assert(false);
	return Edge(NULL, NULL);
} 

/*Geters*/
bool Triangle::getIsWedge() const { 
	return isWedge; 
} 

std::vector<my_point*> Triangle::getCoordinates() const {
	/*if (coordinates.size() != 3) { 
		printf("aborted "%d\n", coordinates.size());
	} */ 
	assert(coordinates.size() == 3);
	return coordinates;  
} 

/*Operators*/
bool Triangle::operator==(const Triangle& a) const { 
	return ((*coordinates[0] == *(a.coordinates[0])) && (*coordinates[1] == *(a.coordinates[1])) && (*coordinates[2] == *(a.coordinates[2])));
}

bool Triangle::operator!=(const Triangle& a) const { 
	return !(*this == a);
} 

/*Debug*/ 
void Triangle::print() const { 
	assert(coordinates.size() == 3);

	if (isWedge == false)
		printf("Triangle: (%d, %d)--(%d, %d)--(%d, %d)\n", coordinates[0]->xy.x, coordinates[0]->xy.y, coordinates[1]->xy.x, coordinates[1]->xy.y, coordinates[2]->xy.x,  coordinates[2]->xy.y);
	else 
		printf("Wedge: (%d, %d, %d)--(%d, %d, %d)--(%d, %d, %d)\n", coordinates[0]->xy.x, coordinates[0]->xy.y, coordinates[0]->z, coordinates[1]->xy.x, coordinates[1]->xy.y, coordinates[1]->z, coordinates[2]->xy.x, coordinates[2]->xy.y, coordinates[2]->z);
} 

/*Private methods*/
bool Triangle::isHereTriangle(const my_point& point) const { 
	assert(coordinates.size() == 3 && isWedge == false); 
	return  ((orient(*coordinates[0], *coordinates[1], point) >= 0) && (orient(*coordinates[1], *coordinates[2], point) >= 0) && \
		(orient(*coordinates[2], *coordinates[0], point) >= 0)) || ((orient(*coordinates[0], *coordinates[1], point) <= 0) && \
		(orient(*coordinates[1], *coordinates[2], point) <= 0) && (orient(*coordinates[2], *coordinates[0], point) <= 0));	
} 


/*Other*/
long long orient(const my_point& a, const my_point& b, const my_point& c) { 
	return ((long long)(a.xy.x))*(b.xy.y - c.xy.y) + ((long long)(b.xy.x))*(c.xy.y - a.xy.y) + ((long long)(c.xy.x))*(a.xy.y - b.xy.y); 
}

}

