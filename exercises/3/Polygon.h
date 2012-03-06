#ifndef POLYGON_H_
#define POLYGON_H_
#include <vector>
#include <stack>
#include "Vertex.h"
#include <iostream>
#include <utility>

	typedef std::pair<long long, long long> point; 
 	
	class Polygon { 
		private: 		
			struct Triangle { 
				int v1; 
				int v2; 
				int v3;
				Triangle(const int& a1, const int& a2, const int& a3); 
				friend class Polygon; 
			}; 
			enum WhereChain {UP, LOW, END}; 		
			
			std::vector<std::pair<Vertex, WhereChain> > poly; 
			std::stack<std::pair<Vertex, WhereChain> > stack_; 
			std::vector<Triangle> triangles; 
		public: 
			Polygon(std::vector<Vertex> &upper, std::vector<Vertex> &lower);
			long long orient(const point& p1, const point& p2, const point& p3) const; 
			bool isTrueAngle(const std::pair<Vertex, WhereChain>& p1, const std::pair<Vertex, WhereChain>& p2, const std::pair<Vertex, WhereChain>& base); 
			void triangulation(); 
			void printTriangles(/*std::fstream &out*/); 
	}; 
#endif
