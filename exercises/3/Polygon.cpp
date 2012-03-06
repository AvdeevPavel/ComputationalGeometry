#include "Polygon.h"

Polygon::Polygon(std::vector<Vertex> &upper, std::vector<Vertex> &lower) {
	std::vector<Vertex>::iterator itUp = upper.begin() + 1; 
	std::vector<Vertex>::reverse_iterator itLo = lower.rbegin() + 1; 

	poly.push_back(std::make_pair(*(upper.begin()), END));

	while(itUp < (upper.end() - 1) && itLo < (lower.rend() - 1)) { 
		if (itUp->v.first < itLo->v.first) { 
			poly.push_back(std::make_pair(*itUp, UP)); 
			++itUp; 
		} else if (itUp->v.first == itLo->v.first && itUp->v.second < itLo->v.second){
			poly.push_back(std::make_pair(*itUp, UP)); 
			++itUp; 
		} else if (itUp->v.first == itLo->v.first && itUp->v.second > itLo->v.second) {
			poly.push_back(std::make_pair(*itLo, LOW));
			++itLo; 
		} else {
			poly.push_back(std::make_pair(*itLo, LOW));
			++itLo; 
		} 
	} 

	while (itUp < (upper.end() - 1)) { 
		poly.push_back(std::make_pair(*itUp, UP));
		++itUp;
	} 

	while (itLo < (lower.rend() - 1)) { 
		poly.push_back(std::make_pair(*itLo, LOW));
		++itLo;
	}
 
	poly.push_back(std::make_pair(*(upper.end() - 1), END));
	stack_.push(*poly.begin());
	stack_.push(*(poly.begin() + 1));

	/*std::cout << "Poly" << std::endl; 
	for(std::vector<std::pair<Vertex, WhereChain> >::iterator it = poly.begin(); it < poly.end(); ++it) {
		std::cout << it->first.num << " " << it->first.v.first << " " << it->first.v.second << " " << it->second <<std::endl;		
	}*/
} 

Polygon::Triangle::Triangle(const int& a1, const int& a2, const int& a3) { 
	v1 = a1; 
	v2 = a2; 
	v3 = a3; 
} 

long long Polygon::orient(const point& p1, const point& p2, const point& p3) const { 
	//std::cout << p1.first * p2.second << " " << p2.first * p3.second << " " << p3.first * p1.second << " " << p1.first * p3.second << " " << p2.first  * p1.second << " " << p3.first * p2.second << std::endl;
	return (p1.first * p2.second + p2.first * p3.second + p3.first * p1.second - p1.first * p3.second - p2.first  * p1.second - p3.first * p2.second);
}  

bool Polygon::isTrueAngle(const std::pair<Vertex, WhereChain>& base, const std::pair<Vertex, WhereChain>& p2, const std::pair<Vertex, WhereChain>& p3) {
	//std::cout << orient(base.first.v, p2.first.v, p3.first.v) << std::endl;
	return((orient(base.first.v, p2.first.v, p3.first.v) < 0 && base.second == LOW) || (orient(base.first.v, p2.first.v, p3.first.v) > 0 && base.second == UP));		
} 


void Polygon::triangulation() { 
	for(std::vector<std::pair<Vertex, WhereChain> >::iterator it = poly.begin() + 2; it < poly.end(); ++it) { 	
		if (stack_.top().second != it->second) { 
			//std::cout << "hello";
			std::pair<Vertex, WhereChain> p = stack_.top();
			std::pair<Vertex, WhereChain> begin = p;  
			stack_.pop();
			
			while (!stack_.empty()) {
				Triangle t(p.first.num, stack_.top().first.num, it->first.num);
				triangles.push_back(t);
				p = stack_.top();  
				stack_.pop();
			} 		
			
			stack_.push(begin);
			stack_.push(*it);
		} else { 
			std::pair<Vertex, WhereChain> p = stack_.top();
			stack_.pop();
			//std::cout << "new tirangle " << isTrueAngle(*it, p, stack_.top()) << " " << it->first.num << " " << p.first.num << " " <<  stack_.top().first.num << std::endl; 

			while (!stack_.empty() && isTrueAngle(*it, p, stack_.top())) {
				Triangle t(it->first.num, p.first.num, stack_.top().first.num);
				//std::cout << it->first.num << " " << p.first.num << " " <<  stack_.top().first.num << std::endl;
				triangles.push_back(t);  
				p = stack_.top();
				stack_.pop();
			} 		

			//std::cout << p.first.num << std::endl;
			stack_.push(p);
			stack_.push(*it);
		} 
	} 			
}  

void Polygon::printTriangles(/*std::fstream &out*/) {
	if (triangles.size() == 0) { 
		std::cout << "Fail input data" << std::endl;
		return;
	} 
	
	for(std::vector<Triangle>::iterator it = triangles.begin(); it < triangles.end(); ++it) {
		std::cout << (it->v1) << " " << (it->v2) << " " << (it->v3) << std::endl;
	}	 
}  

