#include "Polygon.h"

Polygon::Polygon(std::vector<point> &upper, std::vector<point> &lower) {
	std::vector<point>::iterator itUp = upper.begin() + 1; 
	std::vector<point>::reverse_iterator itLo = lower.rbegin() + 1; 
	
	poly.push_back(std::make_pair(*(upper.begin()), UP));

	while(itUp != (upper.end() - 1) && itLo < (lower.rend() - 1)) { 
		if (itUp->first < itLo->first) { 
			poly.push_back(std::make_pair(*itUp, UP)); 
			++itUp; 
		} else {
			poly.push_back(std::make_pair(*itLo, LOW));
			++itLo; 
		} 
	} 

	while (itUp < upper.end()) { 
		poly.push_back(std::make_pair(*itUp, UP));
		++itUp;
	} 

	while (itLo < lower.rend()) { 
		poly.push_back(std::make_pair(*itLo, LOW));
		++itLo;
	} 

	dec.push_back(*poly.begin());
	dec.push_back(*(poly.begin() + 1));
	
	for(std::vector<std::pair<point, WhereChain> >::iterator it = poly.begin(); it < poly.end(); ++it) { 	
		std::cout << it->first.first << " " << it->first.second << " " << it->second << std::endl;
	}
} 

Polygon::Triangle::Triangle(const point& a1, const point& a2, const point& a3) { 
	v1 = a1; 
	v2 = a2; 
	v3 = a3; 
} 

long Polygon::orient(const point& p1, const point& p2, const point& p3) const { 
	return p1.first * (p2.second - p3.second) + p2.first * (p3.second - p1.second) + p3.first * (p1.second - p2.second);
}  

bool Polygon::isTrueAngle(const std::pair<point, WhereChain>& p1, const std::pair<point, WhereChain>& p2, const std::pair<point, WhereChain>& base) {
	return ((orient(p1.first, p2.first, base.first) > 0 && base.second == UP) || (orient(p1.first, p2.first, base.first) < 0 && base.second == LOW));				
} 


void Polygon::triangulation() { 
	
	for(std::vector<std::pair<point, WhereChain> >::iterator it = poly.begin() + 2; it < poly.end(); ++it) { 	
		if (dec.back().second != it->second) { 
			std::cout << "hello";
			std::pair<point, WhereChain> p = dec.front();
			dec.pop_front(); 
			while (!dec.empty() && isTrueAngle(p, dec.front(), *it)) {
				Triangle t(p.first, dec.front().first, it->first);
				triangles.push_back(t);
				p = dec.front();  
				dec.pop_front();
			} 		
			
			dec.push_back(p);
			dec.push_back(*it);
		} else { 
			std::cout << "hellio";
			std::pair<point, WhereChain> p = dec.back();
			dec.pop_back(); 
			while (!dec.empty() && isTrueAngle(dec.back(), p, *it)) {
				Triangle t(dec.back().first, p.first, it->first);
				triangles.push_back(t);  
				p = dec.back();
				dec.pop_back();
			} 		
			
			dec.push_back(p);
			dec.push_back(*it);		
		} 
	} 			
}  

void Polygon::printTriangles(std::fstream &out) {
	if (triangles.size() == 0) { 
		out << "Fail input data" << std::endl;
		return;
	} 
	out << triangles.size() << std::endl;
	for(std::vector<Triangle>::iterator it = triangles.begin(); it < triangles.end(); ++it) {
		out << "<(" << (it->v1).first << ", " << (it->v1).second << "), (" << (it->v2).first << ", " << (it->v2).second << "), (" << (it->v3).first << ", " << (it->v3).second << ")>" << std::endl; 
	}  	 
}  

