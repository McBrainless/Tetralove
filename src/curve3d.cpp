#include "./headers/curve3d.hpp"

int curve3d::count = 0;

curve3d::curve3d(int id, point3d* pt1, point3d* pt2) {
	curve3d::count++;
	this->id = count;
	this->points[0] = pt1;
	this->points[1] = pt2;
}

void curve3d::add_PTag(int tag) {
	this->tags.push_back(tag);
}

void curve3d::add_Bounding(int tag) {
	this->boundings.push_back(tag);
}

