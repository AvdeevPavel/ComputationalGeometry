#include "algo/Node.h"
#include <cassert>
#include <cstdio>

namespace algo
{ 

typedef std::pair<Edge, Node*> mapPair;
typedef std::unordered_map<Edge, Node*> type_map;

/*Constructor*/
Node::Node(const Triangle& date_): date(date_) { 
} 

/*Methods work neignbors*/
void Node::setNeighbor(const Edge &e, Node* const neighbor) {
	neighbors[e] = neighbor;
	assert(neighbors.size() <= 3);
} 

void Node::setNeighbor(const mapPair& e) {
	neighbors[e.first] = e.second;
	assert(neighbors.size() <= 3);
} 

void Node::setCurrentNeighbor(const type_map& allOldNeighbors, Node *anotherNeighbor) {
	std::vector<my_point*> coordinates = date.getCoordinates();
	//printf("----SetCurrentNumber\n");
	for(size_t i = 0; i < 3; ++i) { 
		//printf("Find edge: ");
		//Edge(coordinates[i], coordinates[(i + 1) % 3]).print();
		type_map::const_iterator it = allOldNeighbors.find(Edge(coordinates[i], coordinates[(i + 1) % 3]));	
		if (it == allOldNeighbors.end()) { 
			//anotherNeighbor->print();
			neighbors.insert(mapPair(Edge(coordinates[i], coordinates[(i + 1) % 3]), anotherNeighbor));
			assert(neighbors.size() <= 3);
		} else {
			//printf("Set neighbor to: "); 
			//it->second->print();
			//print();
			neighbors.insert(mapPair(Edge(coordinates[i], coordinates[(i + 1) % 3]), it->second));
			it->second->setNeighbor(it->first, this);
			assert(neighbors.size() <= 3);
		}  
	} 
}

mapPair Node::findNeighborTriangleInWedge() const { 
	assert(date.getIsWedge() == true);
	for(type_map::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) { 
		if (it->second->getIsWedge() == false) { 
			return *it;
		} 
	} 
	//print();
	assert(false);
	return *(neighbors.end());
} 

mapPair Node::getNeighbor(const Edge &e) const { 
	type_map::const_iterator it = neighbors.find(e);
	if (it != neighbors.end()) { 
		return *it;
	} 
	//print();
	assert(false); 
	return *(neighbors.end()); 
} 

type_map Node::getNeighbors() const { 
	return neighbors;
} 

/*Methods MODULE TRIANGLE*/
bool Node::isHere(const my_point& point) const { 
	if (date.getIsWedge() == false) { 
		return date.isHereTriangle(point);
	} else { 
		mapPair triangle = findNeighborTriangleInWedge();
		Edge first = triangle.second->date.getEdgeClockwiseOrient(triangle.first);
		if (orient(*first.x, *first.y, point) < 0) { 
			return true; 
		} else { 
			return false; 
		} 
	} 
} 

bool Node::isFlip(const mapPair& mp) const {
	if (date.getIsWedge() != mp.second->date.getIsWedge()) { 
		return false; 
	} else if (date.getIsWedge() == true && mp.second->date.getIsWedge() == true) {
		Edge first = findNeighborTriangleInWedge().first; 
		mapPair triangle = mp.second->findNeighborTriangleInWedge();
		Edge second = triangle.second->date.getEdgeClockwiseOrient(triangle.first);
		return date.isIntoCircleForWedge(first, second);
	} else if (date.getIsWedge() == false && mp.second->date.getIsWedge() == false) { 
		return date.isIntoCircleForTriangle(*(mp.second->date.findOtherCoordinate(mp.first)));
	} 
	assert(false);
	return false;
} 

/*Methods*/
std::vector<Node*> Node::putPointInTriangle(my_point * const point, std::vector<Node*>& erase) { 
	std::vector<Node*> result;
	erase.push_back(this);
	
	if (date.getIsWedge() == false && date.isOnEdgeInTriangle(*point) == true) { 
		type_map allOldNeighbors(neighbors.begin(), neighbors.end());
		Edge onThis = date.getOnEdgeInTriangle(*point);
		mapPair neighbor = getNeighbor(onThis);

		my_point *firstPoint = date.findOtherCoordinate(onThis);
		Node *first =  new Node(Triangle(onThis.x, point, firstPoint));
		Node *second = new Node(Triangle(point, onThis.y, firstPoint));
		childs.push_back(first); 
		childs.push_back(second);

		my_point *fourPoint = neighbor.second->date.findOtherCoordinate(onThis);
		Node *firstNeighbor = new Node(Triangle(onThis.x, fourPoint, point));
		Node *secondNeighbor = new Node(Triangle(fourPoint, onThis.y, point));
		neighbor.second->childs.push_back(firstNeighbor); 
		neighbor.second->childs.push_back(secondNeighbor);

		allOldNeighbors.insert(mapPair(Edge(onThis.x, point), firstNeighbor));
		allOldNeighbors.insert(mapPair(Edge(point, onThis.y), secondNeighbor));
		first->setCurrentNeighbor(allOldNeighbors, second);
		second->setCurrentNeighbor(allOldNeighbors, first);
		
		allOldNeighbors.clear();
		allOldNeighbors.insert(neighbor.second->neighbors.begin(), neighbor.second->neighbors.end());
		allOldNeighbors.insert(mapPair(Edge(point, onThis.x), first));
		allOldNeighbors.insert(mapPair(Edge(onThis.y, point), second));
		firstNeighbor->setCurrentNeighbor(allOldNeighbors, secondNeighbor);
		secondNeighbor->setCurrentNeighbor(allOldNeighbors, firstNeighbor);

		erase.push_back(neighbor.second);
		result.push_back(first);
		result.push_back(second);
		if (neighbor.second->date.getIsWedge() == false) {
			result.push_back(firstNeighbor); 
			result.push_back(secondNeighbor);
		} 
	} else {
		std::vector<my_point*> coordiantes = getCoordinates();
		Node *first = new Node(Triangle(coordiantes[0], coordiantes[1], point));
		Node *second = new Node(Triangle(coordiantes[1], coordiantes[2], point));
		Node *third = new Node(Triangle(coordiantes[2], coordiantes[0], point));

		childs.push_back(first); 
		childs.push_back(second);	
		childs.push_back(third);

		first->setNeighbor(Edge(coordiantes[1], point), second);
		first->setNeighbor(Edge(point, coordiantes[0]), third);
		first->setNeighbor(getNeighbor(Edge(coordiantes[0], coordiantes[1])));

		second->setNeighbor(Edge(coordiantes[2], point), third);
		second->setNeighbor(Edge(point, coordiantes[1]), first);
		second->setNeighbor(getNeighbor(Edge(coordiantes[1], coordiantes[2])));
		
		third->setNeighbor(Edge(coordiantes[0], point), first);
		third->setNeighbor(Edge(point, coordiantes[2]), second);
		third->setNeighbor(getNeighbor(Edge(coordiantes[2], coordiantes[0])));

		getNeighbor(Edge(coordiantes[0], coordiantes[1])).second->setNeighbor(Edge(coordiantes[0], coordiantes[1]), first);
		getNeighbor(Edge(coordiantes[1], coordiantes[2])).second->setNeighbor(Edge(coordiantes[1], coordiantes[2]), second);
		getNeighbor(Edge(coordiantes[2], coordiantes[0])).second->setNeighbor(Edge(coordiantes[2], coordiantes[0]), third);
		
		result.push_back(first);
		result.push_back(second);
		result.push_back(third);
	}  

	return result;
} 


Node* Node::localizationInTriangle(const my_point& point) { 
	if (childs.empty()) { 
		return this; 
	} 

	for(std::vector<Node*>::iterator it = childs.begin(); it != childs.end(); ++it) { 
		if ((*it)->isHere(point)) { 
			//printf("We here sub triangle: ");
			//(*it)->print();
			return (*it)->localizationInTriangle(point);
		} 
	}
	//printChilds(); 
	assert(false);
	return this;
}

std::vector<Node*> Node::flip(std::pair<const Edge, Node*>& triangle) { 
	//printf("---------operation FLIP\n");
	std::vector<Node*> result; 
	my_point* pointFirst = date.findOtherCoordinate(triangle.first); 
	my_point* pointSecond = triangle.second->date.findOtherCoordinate(triangle.first); 
	
	Node *first = new Node(Triangle(triangle.first.x, pointFirst, pointSecond)); 
	Node *second = new Node(Triangle(triangle.first.y, pointFirst, pointSecond));
	
	type_map allOldNeighbors; 
	allOldNeighbors.insert(neighbors.begin(), neighbors.end());
	allOldNeighbors.insert(triangle.second->neighbors.begin(), triangle.second->neighbors.end());

	first->setCurrentNeighbor(allOldNeighbors, second);
	second->setCurrentNeighbor(allOldNeighbors, first);
	
	triangle.second->childs.push_back(first);
	triangle.second->childs.push_back(second);
	childs.push_back(first);
	childs.push_back(second);

	result.push_back(first);
	result.push_back(second);
 	
	//first->print();
	//first->printNeighbors();
	//second->print();
	//second->printNeighbors();
	return result;		
} 

/*Geters*/
std::vector<Node*> Node::getChild() const { 
	return childs;
} 

Triangle Node::getDate() const { 
	return date;
} 

std::vector<my_point*> Node::getCoordinates() const { 
	return date.getCoordinates();
}  

bool Node::getIsWedge() const { 
	return date.getIsWedge();
} 


/*Debug*/
void Node::print() const { 
	date.print();
} 

void Node::printChilds() const { 
	printf("childs\n");
	for(std::vector<Node*>::const_iterator it = childs.begin(); it != childs.end(); ++it) { 				
		(*it)->print();
	} 
} 

void Node::printNeighbors() const { 
	printf("::::::Neigbors:\n");
	for(type_map::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
		printf("(%d %d)--(%d %d):  ", it->first.x->xy.x, it->first.x->xy.y, it->first.y->xy.x, it->first.y->xy.y);
		it->second->print(); 
	}
} 

/*Operators*/
bool Node::operator==(const Node& a) const { 
	return (date == a.date);
}
 
bool Node::operator!=(const Node& a) const { 
	return (date != a.date);
}
 
} 
