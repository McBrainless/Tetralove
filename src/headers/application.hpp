
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

#define STREAM_SIZE 255

enum error_codes {
	None,
	File_Open_Already
};

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
		fstream mshfile;
		vector <point3d*> points;
		vector <curve3d*> curves;
		vector <surface3d*> surfaces;
		vector <volume*> volumes;
		string* readLine(void);
		void load_NodeBlock(int);
		int load_Entities(void);
		int load_Nodes(void);
	public:
		application();
		~application();
		int load_msh(string*);
		point3d* get_point(int);
		curve3d* get_curve(int);
		surface3d* get_surface(int);
		volume* get_volume(int);
};

string* strtoken(string*, const char*);

#endif //APPLICATION_HPP
