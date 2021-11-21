#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "./headers/point3d.hpp"

class tetrahedron {
		array <point3d*> points;
	public:
		tetrahedron();
		~tetrahedron();
}

#endif // TETRAHEDRON_HPP
