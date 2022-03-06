#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "./headers/point3d.hpp"

 class tetrahedron {
	point3d* points[4];
	int id;
public:
	static int count;
	tetrahedron(void);
	tetrahedron(int, point3d*, point3d*, point3d*, point3d*);
	~tetrahedron(void);
};

#endif // TETRAHEDRON_HPP
