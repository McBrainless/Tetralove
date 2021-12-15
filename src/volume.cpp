#include "./headers/volume.hpp"

int volume::count = 0;

volume::volume() {
	volume::count++;
	this->id = count;
}

volume::volume(int id, point3d* pt1, point3d* pt2) {
	this->id = id;
	this->points[0] = pt1;
	this->points[1] = pt2;
}
