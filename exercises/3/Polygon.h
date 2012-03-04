#ifndef POLYGON_H_
#define POLYGON_H_
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <utility>

	typedef std::pair<long, long> point; 
 	
	class Polygon { 
		private: 		
			struct Triangle { 
				point v1; 
				point v2; 
				point v3;
				Triangle(const point& a1, const point& a2, const point& a3); 
				friend class Polygon; 
			}; 
			enum WhereChain {UP, LOW}; 		
			
			std::vector<std::pair<point, WhereChain> > poly; 
			std::deque<std::pair<point, WhereChain> > dec; 
			std::vector<Triangle> triangles; 
		public: 
			Polygon(std::vector<point> &upper, std::vector<point> &lower);
			long orient(const point& p1, const point& p2, const point& p3) const; 
			bool isTrueAngle(const std::pair<point, WhereChain>& p1, const std::pair<point, WhereChain>& p2, const std::pair<point, WhereChain>& base); 
			void triangulation(); 
			void printTriangles(std::fstream &out); 
	}; 
#endif
