#include "./headers/curves.hpp"

int curve3d::count = 0;


curve3d::curve3d(int id, point3d* pt1, point3d* pt2) {
	curve3d::count++;
	this->points[0] = pt1;
	this->points[1] = pt2;
}
