#ifndef POINT3D_HPP
#define POINT3D_HPP

class point3d {
		double x, y, z;
		int id;
	public:
		static int count;
		point3d();
		point3d(int, double, double, double);
		point3d operator = (const point3d&);
		int get_id() { return this->id; }
		double get_x() { return this->x; }
		double get_y() { return this->y; }
		double get_z() { return this->z; }
};

#endif // POINT3D_HPP
