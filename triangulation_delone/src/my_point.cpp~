#include "algo/my_point.h"

namespace  algo { 

my_point::my_point(int32 x, int32 y): xy(x, y), z(0) { 
} 

my_point::my_point(const point_type& a): xy(a), z(0) { 
} 

my_point::my_point(int32 x, int32 y, int32 z_): xy(x, y), z(z_) { 
} 
	
bool my_point::operator == (const my_point &b) const { 
	return ((xy == b.xy) && (z == b.z));
} 

bool my_point::operator != (const my_point &b) const { 
	return !(*this == b);
} 
		
bool my_point::isInfPoint() const { 
	return (z != 0);
} 

} 
