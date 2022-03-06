#include "./headers/tetrahedron.hpp"

int tetrahedron::count = 0;

tetrahedron::tetrahedron(void) {
	tetrahedron::count++;
	this->id = tetrahedron::count;

	this->points[0] = NULL;
	this->points[1] = NULL;
	this->points[2] = NULL;
	this->points[3] = NULL;
}

tetrahedron::tetrahedron(int id, point3d* p0, point3d* p1, point3d* p2, point3d* p3) {
	this->id = id;
	if (id > tetrahedron::count) tetrahedron::count = id;

	this->points[0] = p0;
	this->points[1] = p1;
	this->points[2] = p2;
	this->points[3] = p3;
}

tetrahedron::~tetrahedron(void) {
	
}