#ifndef CURVE_HPP
#define CURVE_HPP

#include <vector>
#include "./point3d.hpp"

class curve3d {
		int id;
		vector <int> tags;
		vector <int> boundings;
		point3d* points[2];
	public:
		static int count;
		int get_id() { return this->id; }
		curve3d(int, point3d*, point3d*);
		void add_PTag(int);
		void add_Bounding(int);
};

#endif // CURVE_HPP
