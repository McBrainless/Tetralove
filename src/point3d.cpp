#include "./headers/point3d.hpp"

int point3d::count = 0;

point3d::point3d(int id, double x, double y, double z) {
	this->id = id;
	this->x = x;
	this->y = y;
	this->z = z;
}

point3d::point3d(int id) {
	this->id = id;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

point3d::point3d() {
	point3d::count++;
	this->id = count;
	this->x = 0;
	this->y = 0;
	this->z = 0;

}

point3d point3d::operator= (const point3d& point) {
	point3d tmp;
	tmp.x = point.x;
	tmp.y = point.y;
	tmp.z = point.z;
	return tmp;
}

void point3d::add_PTag(int tag) {
	this->tags.push_back(tag);
}

void point3d::set_position(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

