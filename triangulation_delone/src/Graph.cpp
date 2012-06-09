#include "algo/Graph.h"

#include "algo/Triangle.h"

#include <cassert>
#include <queue>
#include <cstdio> //del

namespace algo { 

Node* Graph::createFirstTriangle(my_point * const a, my_point * const b, my_point * const c, my_point * const infV) {
	assert(startVertexGraph.empty());

	startVertexGraph.push_back(new Node(Triangle(a, b, c)));
	std::vector<my_point*> coordinates = startVertexGraph.back()->getCoordinates();
	
	startVertexGraph.push_back(new Node(Triangle(coordinates[0], infV, coordinates[1])));
	startVertexGraph.push_back(new Node(Triangle(coordinates[1], infV, coordinates[2])));
	startVertexGraph.push_back(new Node(Triangle(coordinates[2], infV, coordinates[0])));
	
	startVertexGraph[0]->setNeighbor(Edge(coordinates[0], coordinates[1]), startVertexGraph[1]);
	startVertexGraph[0]->setNeighbor(Edge(coordinates[1], coordinates[2]), startVertexGraph[2]);
	startVertexGraph[0]->setNeighbor(Edge(coordinates[2], coordinates[0]), startVertexGraph[3]);

	startVertexGraph[1]->setNeighbor(Edge(coordinates[1], coordinates[0]), startVertexGraph[0]);
	startVertexGraph[1]->setNeighbor(Edge(infV, coordinates[1]), startVertexGraph[2]);
	startVertexGraph[1]->setNeighbor(Edge(coordinates[0], infV), startVertexGraph[3]);

	startVertexGraph[2]->setNeighbor(Edge(coordinates[2], coordinates[1]), startVertexGraph[0]);	
	startVertexGraph[2]->setNeighbor(Edge(coordinates[1], infV), startVertexGraph[1]);
	startVertexGraph[2]->setNeighbor(Edge(infV, coordinates[2]), startVertexGraph[3]);

	startVertexGraph[3]->setNeighbor(Edge(coordinates[0], coordinates[2]), startVertexGraph[0]);	
	startVertexGraph[3]->setNeighbor(Edge(coordinates[2], infV), startVertexGraph[2]);
	startVertexGraph[3]->setNeighbor(Edge(infV, coordinates[0]), startVertexGraph[1]);
	

	/*printf("Create triangle\n");
	for(std::vector<Node*>::iterator it = startVertexGraph.begin(); it != startVertexGraph.end(); ++it) { 
		(*it)->print();
	} */

	return startVertexGraph[0];
} 


Node* Graph::localizationInTriangle(const my_point& point) { 
	std::queue<Node*> myQueue; 

	for(std::vector<Node*>::iterator it = startVertexGraph.begin(); it != startVertexGraph.end(); ++it) { 	
		if ((*it)->isHere(point) == true) { 			
			//printf("We have this triangle\n"); 
			//(*it)->print();
			myQueue.push(*it);
		} 
	} 

	while(!myQueue.front()->isEmptyChilds()) {
		Node* now = myQueue.front();	
		myQueue.pop(); 
		auto childs = now->getChild();
		for(std::vector<Node*>::iterator it = childs.begin(); it != childs.end(); ++it) { 
			if ((*it)->isHere(point)) {  
				myQueue.push(*it);
			} 
		} 
	} 	

	assert(!myQueue.empty());
	return myQueue.front();
} 

} 
