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
}

void application::load_msh(string* filename) {
	fstream mshfile;
	mshfile.open(filename->c_str(), ios::in);
	if(!mshfile) {
		cout << "File not found!\n";
	} else {
		streamsize n = 255;
		char fLine[n];
		char* token;
		int lineNumber = 0, points = 0, curves = 0, surfaces = 0, volumes = 0;
		int points_ct = 0, curves_ct = 0, surfaces_ct = 0, volumes_ct = 0;
		int id = 0, tags = 0, boundingIDs = 0, p1 = 0, p2 = 0;
		double x = 0.0, y = 0.0, z = 0.0, xm = 0.0, ym=0.0, zm=0.0;
		point3d* lpoint = NULL;
		curve3d* lcurve = NULL;
		surface3d* lsurface = NULL;
		volume* lvolume = NULL;

		cout << "Loading file: " << filename->c_str() << "\n";
		
		while (!mshfile.eof()) {
			mshfile.getline(fLine, n);

			switch (this->state) {
				case initial:
					if (strstr(fLine, "$MeshFormat")) {
						this->state = MeshFormat;
						cout << "Loading: MeshFormat.\n";
					} else if (strstr(fLine, "$Entities")) {
						this->state = Entities;
						cout << "Loading: Entities.\n";
					}
 					break;
				case MeshFormat:
					if (strstr(fLine, "$EndMeshFormat")) {
						this->state = initial;
						cout << "Loaded: MeshFormat.\n";
					} else {
						cout << fLine << "\n";
					}
					break;
				case Entities:
					if (strstr(fLine, "$EndEntities")) {
						this->state = initial;
						cout << "Loaded: Entities.\n";
					} else {
						lineNumber++;
						if (lineNumber == 1) {
//							cout << fLine << "\n";
							points = atoi(strtok(fLine, " "));
							curves = atoi(strtok(NULL, " "));
							surfaces = atoi(strtok(NULL, " "));
							volumes = atoi(strtok(NULL, " "));
							points_ct = points;
							curves_ct = curves;
							surfaces_ct = surfaces;
							volumes_ct = volumes;
						} else {
//							cout << fLine << "\n";
							if (points_ct > 0) {
								id = atoi(strtok(fLine, " "));

								//get location
								x = std::stod(strtok(NULL, " "));
								y = std::stod(strtok(NULL, " "));
								z = std::stod(strtok(NULL, " "));

								//builds point
								lpoint = new point3d(id, x, y, z);
								this->points.push_back(lpoint);

								//ignores physical tags
								tags = std::stod(strtok(NULL, " "));
								for(; tags > 0; tags--) {
									lpoint->add_PTag( std::stod(strtok(NULL, " ")) );
								}

								points_ct--;

								//report data loaded
								if (points_ct == 0) {
									points = this->points.size();
									cout << "Points: " << points << "\n";
									for (int x = 1; x <= points; x++) {
										lpoint = this->get_point(x);
										cout << "ID: " << lpoint->get_id();
										cout << "\tX: " << lpoint->get_x();
										cout << "\tY: " << lpoint->get_y();
										cout << "\tZ: " << lpoint->get_z() << "\n";
									}
								}
							} else if (curves_ct > 0) {
								id = atoi(strtok(fLine, " "));

								//get mins
								x = std::stod(strtok(NULL, " "));
								y = std::stod(strtok(NULL, " "));
								z = std::stod(strtok(NULL, " "));

								//get maxs
								xm = std::stod(strtok(NULL, " "));
								ym = std::stod(strtok(NULL, " "));
								zm = std::stod(strtok(NULL, " "));

								//builds curve
								lcurve = new curve3d(id, this->points[p1], this->points[p2]);
								this->curves.push_back(lcurve);

								//ignores physical tags
								tags = std::stod(strtok(NULL, " "));
								for(; tags > 0; tags--) {
									lcurve->add_PTag( std::stod(strtok(NULL, " ")) );
								}

								//ignores bounding points
								boundingIDs = std::stod(strtok(NULL, " "));
								for(; boundingIDs > 0; boundingIDs--) {
									lcurve->add_Bounding( std::stod(strtok(NULL, " ")) );
								}

								//report data loaded
								curves_ct--;
								if (curves_ct == 0) {
									curves = this->curves.size();
									cout << "Curves: " << curves << "\n";
									for (int x = 1; x <= curves; x++) {
										lcurve = this->get_curve(x);
										cout << "ID: " << lcurve->get_id() << "\n";
									}
								}
							} else if (surfaces_ct > 0) {
								id = atoi(strtok(fLine, " "));

								//get mins
								x = std::stod(strtok(NULL, " "));
								y = std::stod(strtok(NULL, " "));
								z = std::stod(strtok(NULL, " "));

								//get maxs
								xm = std::stod(strtok(NULL, " "));
								ym = std::stod(strtok(NULL, " "));
								zm = std::stod(strtok(NULL, " "));

								//get physical tags
								for (int w = atoi(strtok(NULL, " ")); w>0; w--);

								//get point references
								p1 = atoi(strtok(NULL, " "));
								p2 = abs(atoi(strtok(NULL, " ")));

								//builds curve
								lsurface = new surface3d();
								this->surfaces.push_back(lsurface);

								surfaces_ct--;

								if (surfaces_ct == 0) {
									surfaces = this->surfaces.size();
									cout << "Surfaces: " << surfaces << "\n";
									for (int x = 1; x <= surfaces; x++) {
										lsurface = this->get_surface(x);
										cout << "ID: " << lsurface->get_id() << "\n";
									}
								}
							} else if (volumes_ct > 0) {
								id = atoi(strtok(fLine, " "));

								//get mins
								x = std::stod(strtok(NULL, " "));
								y = std::stod(strtok(NULL, " "));
								z = std::stod(strtok(NULL, " "));

								//get maxs
								xm = std::stod(strtok(NULL, " "));
								ym = std::stod(strtok(NULL, " "));
								zm = std::stod(strtok(NULL, " "));

								//get physical tags
								for (int w = atoi(strtok(NULL, " ")); w>0; w--);

								//get point references
								p1 = atoi(strtok(NULL, " "));
								p2 = abs(atoi(strtok(NULL, " ")));

								//builds curve
								lvolume = new volume(id, this->points[p1], this->points[p2]);
								this->volumes.push_back(lvolume);

								volumes_ct--;

								if (volumes_ct == 0) {
									volumes = this->volumes.size();
									cout << "Volumes: " << volumes << "\n";
									for (int x = 1; x <= volumes; x++) {
										lvolume = this->get_volume(x);
										cout << "ID: " << lvolume->get_id() << "\n";
									}
								}
							} else {
								cout << "Oh snap! There's more.\n";
							}
						}
					}
					break;
				default:
			
				cout << fLine << "\n";
/*
				token = strtok(fLine, "\n");
				while (token) {
					lineNum++;
					cout << lineNum << ") " << token << "\n";
					token = strtok(NULL, "\n");
				}
*/
			}
		}
		mshfile.close();
	}

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



