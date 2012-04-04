#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

#include "algo/Node.h"
#include "algo/my_point.h"
	
using algo::my_point;
using algo::Node;

namespace algo { 
	struct Graph { 
		Node* createFirstTriangle(my_point * const a, my_point * const b, my_point * const c, my_point * const infV);
		Node* localizationInTriangle(const my_point&  point); 
	private: 
		std::vector<Node*> startVertexGraph;
	};
} 

#endif
