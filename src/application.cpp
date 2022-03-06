#include <iostream>
#include <string>
#include "./headers/application.hpp"


application::application(void) {
	this->state = initial;
}

application::~application(void) {
	//clear points
	while (this->points.size() > 0) {
		points.pop_back();
	}

	//clear curves
	while (this->curves.size() > 0) {
		curves.pop_back();
	}

	//clear surfaces
	while (this->surfaces.size() > 0) {
		surfaces.pop_back();
	}

	//clear volumess
	while (this->volumes.size() > 0) {
		volumes.pop_back();
	}

	if (this->mshfile.is_open()) {
		this->mshfile.close();
	}
}

int application::load_Entities(void) {
	bool readLine = true;
	int error_code = None;
	int lineNumber = 0, points = 0, curves = 0, surfaces = 0, volumes = 0;
	string* lString = NULL;
	string* token = NULL;

	if (this->mshfile.is_open()) {
		while (readLine) {

			lString = this->readLine();
			readLine = !this->mshfile.eof();

			lineNumber++;
			if (strstr(lString->c_str(), "$EndEntities")) {
				cout << "Loaded: Entities.\n";
				readLine = false;
			} else if (lineNumber == 1) {
				cout << *lString << "\n";
				points = stoi( *strtoken(lString, " ") );
				curves = stoi( *strtoken(NULL, " ") );
				surfaces = stoi( *strtoken(NULL, " ") );
				volumes = stoi( *strtoken(NULL, " ") );
				
				cout << "\tPoints: " << points << "\n";
				cout << "\tCurves: " << curves << "\n";
				cout << "\tSurfaces: " << surfaces << "\n";
				cout << "\tVolumes: " << volumes << "\n";
			}
			delete lString;

		}
	} else {
		error_code = File_Open_Already;
		cout << "Error: File already open. (code " << error_code << ")\n";
	}
	return error_code;
}


void application::load_NodeBlock(int size) {
	point3d* lPoint = NULL;
	int id = 0;
	double x = 0.0, y = 0.0, z = 0.0;

	char fLine[STREAM_SIZE];

	for (int lLine = 0; lLine < size; lLine++) {
		mshfile.getline(fLine, STREAM_SIZE);
		id = std::stod(fLine);

		lPoint = new point3d(id);
		this->points.push_back(lPoint);
	}

	for (int lLine = 0; lLine < size; ++lLine) {
		mshfile.getline(fLine, STREAM_SIZE);
	}
}


string* application::readLine(void) {
	char fLine[STREAM_SIZE];
	this->mshfile.getline(fLine, STREAM_SIZE);
	string* lString = new string(fLine);
	return lString;
}

int application::load_Nodes(void) {
	bool readLine = true;
	int error_code = None;
	string* lString = NULL;
	curve3d* lcurve = NULL;
	surface3d* lsurface = NULL;
	volume* lvolume = NULL;

	if (this->mshfile.is_open()) {
		while (readLine) {
			lString = this->readLine();
			readLine = !this->mshfile.eof();
			
			if (strstr(lString->c_str(), "$EndNodes")) {
				cout << "Loaded: Nodes.\n";
				readLine = false;
			} else {

			}
			delete lString;
		}
	}
	return error_code;
}

int application::load_msh(string* filename) {
	int error = 0;
	this->mshfile.open(filename->c_str(), ios::in);
	if(!this->mshfile.is_open()) {
		cout << "File not found!\n";
		error = 1;
	} else {
		string* lString = NULL;
		bool readLine = true;
		char fLine[STREAM_SIZE];
		char* token = NULL;
		
		cout << "Loading file: " << filename->c_str() << "\n";
		
		while (readLine) {
			switch (this->state) {
				case initial:
					this->mshfile.getline(fLine, STREAM_SIZE);
					readLine = !this->mshfile.eof();

					if (strstr(fLine, "$MeshFormat")) {
						this->state = MeshFormat;
						cout << "Loading: MeshFormat.\n";
					} else if (strstr(fLine, "$Entities")) {
						this->state = Entities;
						cout << "Loading: Entities.\n";
					} else if (strstr(fLine, "$Nodes")) {
						this->state = Nodes;
						cout << "Loading: Nodes.\n";
					} else {
						cout << "Error: Unknown root state: \n" << fLine << "\n";
						readLine = false;
					}
 					break;
				case MeshFormat:
					cout << *this->readLine() << "\n";
					lString = this->readLine();
					delete lString;
					cout << "Loaded: MeshFormat.\n";
					this->state = initial;
					break;
				case Entities:
					this->load_Entities();
					this->state = initial;
					break;
				case Nodes:
					this->load_Nodes();
					this->state = initial;
					break;
				default:			
					cout << "Unknown branch state: " << fLine << "\n";
			}
		}
		mshfile.close();
	}
	return error;
}

point3d* application::get_point(int id) {
	for (vector<point3d*>::iterator it = this->points.begin(); it != points.end(); ++it) {
		if ((*it)->get_id() == id) return *it;
	}
	return NULL;
}

curve3d* application::get_curve(int id) {
	for (vector<curve3d*>::iterator it = this->curves.begin(); it != curves.end(); ++it) {
		if ((*it)->get_id() == id) return *it;
	}
	return NULL;
}

surface3d* application::get_surface(int id) {
	for (vector<surface3d*>::iterator it = this->surfaces.begin(); it != surfaces.end(); ++it) {
		if ((*it)->get_id() == id) return *it;
	}
	return NULL;
}

volume* application::get_volume(int id) {
	for (vector<volume*>::iterator it = this->volumes.begin(); it != volumes.end(); ++it) {
		if ((*it)->get_id() == id) return *it;
	}
	return NULL;
}

string* strtoken(string* str, const char* delim) {
	static string s = *str;
	static int x = 0, size = 0;
	string* outstr = new string("");

	if (str != NULL) {
		size = s.size();
	}

	if (x < size) {
		for(; ((s[x] != *delim) && (x < size)); x++) {
			*outstr += s[x];
		}
		x++;
	} else *outstr = s[size - 1];	

	return outstr;
}

