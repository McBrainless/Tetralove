#ifndef VOLUME_HPP
#define VOLUME_HPP

#include "./point3d.hpp"
#include "./curve3d.hpp"

class volume {
		int id;
		point3d* points[2];
	public:
		static int count;
		int get_id() { return this->id; }
		volume();
		volume(int, point3d*, point3d*);
};

#endif // volume_HPP
