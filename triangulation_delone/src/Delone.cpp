#include "algo/Delone.h"

#include "algo/Node.h"
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <cassert>

#include <cstdio> //del 

using algo::Node;

namespace algo 
{

typedef std::pair<Edge, Node*> mapPair;
typedef std::unordered_map<Edge, Node*> type_map;

void Delone::addPoint(const point_type &pt) {
	static bool flag = false; 
	//printf("-------------NEW_POINT---------------\n");

	points.push_back( new my_point(pt) );

	if (flag) { 
		//printf(":::::::::Find::::::::::\n");
		Node *current = triangleGraph.localizationInTriangle(*(points.back())); 
		//printf("-----We go in algorithm with: ");
		//current->print(); 
		flipTriangles(current, points.back());
	} else if (points.size() > 2) { 
		if (orient(*points[0], *points[1], *(points.back()) ) != 0) {
			points.push_back( new my_point(0, 0, 1) );

			Node* current = triangleGraph.createFirstTriangle(points[0], points[1], points[points.size() - 2], points.back());		
			answer.insert(current->getDate());
			
			for(auto it = points.begin() + 2; it != points.end() - 2; ++it) { 
				Node *local = triangleGraph.localizationInTriangle(*(*it)); 
				flipTriangles(local, *it);
			}

			flag = true;
		} 
	} 
	//printf("---------------END--------------------\n"); 
} 

void Delone::flipTriangles(Node* const current, my_point * const point) { 
	//printf("-------------FLIP TRIANGLES---------------\n");
	std::vector<Node*> erase;
	std::vector<Node*> result = current->putPointInTriangle(point, erase);
	std::queue<Node*> myQueue;

	for(std::vector<Node*>::iterator it = erase.begin(); it != erase.end(); ++it) {
		answer.erase((*it)->getDate());
	} 

	//printf("---We create triangles---\n");
	for(std::vector<Node*>::iterator it = result.begin(); it != result.end(); ++it) { 
		myQueue.push(*it);
		//(*it)->print();
		//(*it)->printNeighbors();
		if ((*it)->getIsWedge() == false) { 
			answer.insert((*it)->getDate());
		} 
	} 

	//printf("::::::We start new operation flip:::::\n");
	Node *now = NULL;
	while(!myQueue.empty()) { 
		now = myQueue.front(); 
		myQueue.pop();

		//printf("::::::We start new operation flip:::::");
		//now->print();
		//now->printNeighbors();
				
		type_map neighbors = now->getNeighbors();
		for(type_map::iterator it = neighbors.begin(); it != neighbors.end(); ++it) { 
			//printf("Start new neighbors ");
			//it->second->print();
			//it->second->printNeighbors();
			//now->printNeighbors();
			if (now->isFlip(*it)) { 
				std::vector<Node*> temp = now->flip(*it);
				answer.erase(it->second->getDate());
				answer.erase(now->getDate());
				//printf("-We get after flip triangles\n");
				for(std::vector<Node*>::iterator iter = temp.begin(); iter != temp.end(); ++iter) { 
					myQueue.push(*iter);
					//(*iter)->print();
					//(*iter)->printNeighbors();		
					if ((*iter)->getIsWedge() == false) { 
						answer.insert((*iter)->getDate());
					} 
				} 
			} 
			//printf("END NEW NEIGHBORS\n");
		} 
		//printf("::::::We END new operation flip:::::\n");
	} 

} 

std::unordered_set<Triangle> Delone::getAnswer() const { 
	return answer;
} 

}
