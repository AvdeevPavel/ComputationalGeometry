#ifndef NODE_H_ 
#define NODE_H_

#include <cstdlib>
#include <vector>	
#include <unordered_map>
#include <utility>

#include "algo/Triangle.h"
#include "algo/Edge.h"
#include "algo/my_point.h"
	
using algo::Triangle; 
using algo::Edge;
using algo::my_point;

namespace std { 
	template<>
	class hash<Edge> {
	public: 
		size_t operator()(const Edge &a) const {
			return hash<my_point>()(*a.x) ^ hash<my_point>()(*a.y); 
		}	
	};
} 

namespace algo { 
	struct Node {
		/*Constructor*/
		Node(const Triangle& date_);

		/*Methods work neignbors*/
		void setNeighbor(const Edge &e, Node * const neighbor);
		void setNeighbor(const std::pair<Edge, Node*>& e);
		void setCurrentNeighbor(const std::unordered_map<Edge, Node*>& allOldNeighbors, Node *anotherNeighbor);
		std::pair<Edge, Node*> findNeighborTriangleInWedge() const;
		std::pair<Edge, Node*> findNeighbor(const Triangle& triangle) const;
		std::pair<Edge, Node*> getNeighbor(const Edge &e) const;
		std::unordered_map<Edge, Node*> getNeighbors() const;

		/*Methods MODULE TRIANGLE*/
		std::vector<my_point*> getCoordinates() const; 
		bool getIsWedge() const;
		bool isFlip(const std::pair<Edge, Node*>& mp) const;
		bool isHere(const my_point& point) const;

		/*Methods*/
		bool isEmptyChilds() const;
		std::vector<Node*> putPointInTriangle(my_point * const point, std::vector<Node*>& erase);
		std::vector<Node*> flip(std::pair<const Edge, Node*>& triangle);

		/*Operators*/
		bool operator==(const Node& a) const;
		bool operator!=(const Node& a) const;

		/*Geters*/
		Triangle getDate() const; 
		std::vector<Node*> getChild() const;

		/*Debug*/
		void print() const;
		void printNeighbors() const; 
		void printChilds() const;
	private: 
		Triangle date;		
		std::unordered_map<Edge, Node*> neighbors;
		std::vector<Node*> childs; 
	};
} 

#endif
