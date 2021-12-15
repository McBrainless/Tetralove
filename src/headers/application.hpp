
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>

#include "./point3d.hpp"
#include "./curve3d.hpp"
#include "./surface3d.hpp"
#include "./volume.hpp"

using namespace std;

enum loading_t {
	initial,
	MeshFormat,
	PhysicalNames,
	Entities,
	PartitionedEntities,
	Nodes,
	Elements,
	Periodic,
	GhostElements,
	Parametrizations,
	NodeData,
	ElementData,
	InterpolationScheme
};


class application {
		loading_t state;
		vector <point3d*> points;
		vector <curve3d*> curves;
		vector <surface3d*> surfaces;
		vector <volume*> volumes;
	public:
		application();
		~application();
		void load_msh(string*);
		point3d* get_point(int);
		curve3d* get_curve(int);
		surface3d* get_surface(int);
		volume* get_volume(int);
};

#endif //APPLICATION_HPP
