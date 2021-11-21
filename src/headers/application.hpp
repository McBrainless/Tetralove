
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>

#include "./classes/point3d.hpp"

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
		vector <point3d> points;
	public:
		application();
		void load_msh(string*);
};

#endif //APPLICATION_HPP
