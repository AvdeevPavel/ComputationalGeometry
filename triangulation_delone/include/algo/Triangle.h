#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <cstdlib>
#include <vector>

#include "algo/my_point.h"
#include "algo/Edge.h"

using algo::my_point;
using algo::Edge;

namespace algo { 
	struct Triangle { 
		/*Constructor*/
		Triangle(my_point* const a, my_point* const b, my_point* const c);
	
		/*Method*/
		my_point* findOtherCoordinate(const Edge& e) const;
		Edge getEdgeClockwiseOrient(const Edge& e) const;
		bool isIntoCircleForTriangle(const my_point& point) const;
		bool isIntoCircleForWedge(const Edge &first, const Edge &second) const;
		bool isHereTriangle(const my_point& point) const;
		bool isOnEdgeInTriangle(const my_point& point) const; 
		Edge getOnEdgeInTriangle(const my_point& point) const;

		/*Geters*/
		bool getIsWedge() const;
		std::vector<my_point*> getCoordinates() const; 
		
		/*Operators*/
		bool operator==(const Triangle& a) const;
		bool operator!=(const Triangle& a) const;

		/*Debug*/
		void print() const;		 
	private: 
		std::vector<my_point*> coordinates;
		bool isWedge;
 	}; 

	long long orient(const my_point& a, const my_point& b, const my_point& c);
} 
#endif
