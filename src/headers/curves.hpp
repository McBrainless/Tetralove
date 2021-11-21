#ifndef CURVE_HPP
#define CURVE_HPP

#include "./point3d.hpp"

class curve3d {
		int id;
		point3d* points[2];
	public:
		static int count;
		curve3d(int, point3d*, point3d*);
};

#endif // CURVE_HPP
