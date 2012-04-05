#ifndef WINDOW_H
#define WINDOW_H

#include <unordered_set>
#include <fstream>
#include <iostream>
#include <QColor>

#include "visualization/viewer_adapter.h"
#include "geom/point.h"
#include "io/point.h"
#include "algo/Delone.h"
#include "algo/Triangle.h"
#include "algo/my_point.h"

using visualization::viewer_adapter;
using visualization::drawer_type;
using geom::structures::point_type;
using algo::Delone;
using algo::Triangle;
using algo::my_point;

namespace std { 
	template<>
	class hash<point_type> {
	public: 	
		size_t operator()(const point_type &a) const {
			return hash<int32>()(a.x) ^ hash<int32>()(a.y); 
		}	
	};
}


struct triangle_delone_window: viewer_adapter {
	triangle_delone_window();
	void draw(drawer_type & drawer) const;
	bool on_double_click(const point_type & pt);
	bool on_key(int key);
private:
	const int32 max_size_coordinate;
	const int32 min_size_coordinate;
	std::unordered_set<point_type> points;
	Delone builder;
};

triangle_delone_window::triangle_delone_window(): max_size_coordinate(30000), min_size_coordinate(-30000) { 
	auto args = QCoreApplication::arguments();
	if (args.size() != 1) { 
		if (args[1] == "-f") { 
			std::ifstream fileIn(args[2].toStdString(), std::ifstream::in);
			if (fileIn) { 
				point_type pt; 
				while(fileIn >> pt) {
					if (points.count(pt) == 0) { 
						points.insert(pt);
						builder.addPoint(pt);
					} 	 
				}
			} 
		} 
	} 
}

void triangle_delone_window::draw(drawer_type & drawer) const {
	drawer.set_color(Qt::blue);

	for (std::unordered_set<point_type>::const_iterator it = points.begin(); it != points.end(); ++it) {
		drawer.draw_point(*it, 3);
	}	

	std::unordered_set<Triangle> triangles = builder.getAnswer();
	if (!triangles.empty()) {
		drawer.set_color(Qt::blue);
		for (std::unordered_set<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
			std::vector<my_point*> temp = it->getCoordinates();
			drawer.draw_line(temp[0]->xy, temp[1]->xy);
			drawer.draw_line(temp[1]->xy, temp[2]->xy);
			drawer.draw_line(temp[2]->xy, temp[0]->xy);
		}
	}
}

bool triangle_delone_window::on_double_click(const point_type & pt) {
	if ((pt.x >= min_size_coordinate && pt.x<= max_size_coordinate) && (pt.y >= min_size_coordinate && pt.y <= max_size_coordinate)) { 
		if (points.count(pt) == 0) { 
			points.insert(pt);
			builder.addPoint(pt);
		}
	} else { 
		std::cout << "Sorry " << pt << " - have big coordiantes. -30000 <= x,y <= 30000" << std::endl;
	}  	
	return true;
}
  
bool triangle_delone_window::on_key(int key) {
	return true;
}

#endif //WINDOW_H
