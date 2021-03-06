#ifndef MYPOINT_H_ 
#define MYPOINT_H_

#include <algorithm>
#include "geom/point.h"

using geom::structures::point_type;

namespace algo { 
	struct my_point { 
		point_type xy; 
		int32 z; 
		
		my_point(int32 x, int32 y);
		my_point(const point_type& a);
		my_point(int32 x, int32 y, int32 z);
	
		bool operator == (const my_point &b) const; 
		bool operator != (const my_point &b) const; 
		
		bool isInfPoint() const;
 	}; 
} 

namespace std { 
	template<>
	class hash<algo::my_point> {
	public: 
		size_t operator()(const algo::my_point &a) const {
			return hash<int32>()(a.xy.x) ^ hash<int32>()(a.xy.y) ^ hash<int32>()(a.z); 
		}	
	};
} 

#endif
