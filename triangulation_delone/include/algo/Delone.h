#ifndef DELONE_H_
#define DELONE_H_

#include <vector>
#include <unordered_set>
#include <cstdlib>

#include "geom/point.h"
#include "algo/my_point.h"
#include "algo/Triangle.h"
#include "algo/Graph.h"

using geom::structures::point_type;
using algo::my_point;
using algo::Triangle;
using algo::Graph;


namespace std { 
	template<>
	class hash<Triangle> {
	public: 
		size_t operator()(const Triangle &a) const {
			std::vector<my_point*> coordinates = a.getCoordinates();
			return hash<my_point>()(*coordinates[0])^hash<my_point>()(*coordinates[1])^hash<my_point>()(*coordinates[2]); 
		}	
	};

} 

namespace algo { 

	struct Delone { 
		/*Methods*/
		void addPoint(const point_type &pt);
		
		/*Geters*/
		std::unordered_set<Triangle> getAnswer() const;
	private:
		void flipTriangles(Node* const current, my_point * const point); 
	private: 
		Graph triangleGraph;
		std::vector<my_point*> points; 
		std::unordered_set<Triangle> answer; 
	}; 
} 

#endif
