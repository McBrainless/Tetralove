#include "./headers/vector3d.hpp"

vector3d::vector3d() {
	vector3d(0.0, 0.0, 0.0);
}

vector3d::vector3d(bool x, bool y, bool z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
