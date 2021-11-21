#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "./point3d.hpp"

class vector3d {
		bool x, y, z;
	public:
		vector3d();
		vector3d(bool, bool, bool);
		vector3d& operator= (const vector3d&);
		vector3d& operator+ (const vector3d&);
		bool get_x() { return x;}
		bool get_y() { return y;}
		bool get_z() { return z;}
};

#endif // VECTOR3D_HPP
