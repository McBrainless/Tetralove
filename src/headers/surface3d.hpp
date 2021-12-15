#ifndef SURFACE3D_HPP
#define SURFACE3D_HPP

class surface3d {
		int id;
	public:
		static int count;
		surface3d();
		int get_id() { return this->id; }
};

#endif // SURFACE3D_HPP
