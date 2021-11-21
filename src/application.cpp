#include <iostream>
#include <string>
#include "./headers/application.hpp"
#include "./headers/models.hpp"
#include "./headers/point3d.hpp"
#include "./headers/curves.hpp"

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
		int id = 0, tags = 0, p1 = 0, p2 = 0;
		double x = 0.0, y = 0.0, z = 0.0, xm = 0.0, ym=0.0, zm=0.0;
		point3d* point = NULL;
		curve3d* curve = NULL;
		
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

								//ignores physical tags

								//builds point
								point = new point3d(id, x, y, z);
								this->points.push_back(point);
								points_ct--;
								if (points_ct == 0) cout << "Points: " << this->points.size() << "\n";
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

								//get physical tags
								for (int w = atoi(strtok(NULL, " ")); w>0; w--);

								//get point references
								p1 = atoi(strtok(NULL, " "));
								p2 = abs(atoi(strtok(NULL, " ")));

								//builds curve
								curve = new curve3d(id, this->points[p1], this->points[p2]);
								this->curves.push_back(curve);
								curves_ct--;
								if (curves_ct == 0) cout << "Curves: " << this->curves.size() << "\n";
							} else if (surfaces_ct > 0) {
								id = atoi(strtok(fLine, " "));
								x = std::stod(strtok(NULL, " "));
								y = std::stod(strtok(NULL, " "));
								z = std::stod(strtok(NULL, " "));
								cout << "ID: " << id << "\t";
								cout << "X: " << x << "\t";
								cout << "Y: " << y << "\t ";
								cout << "Z: " << z << "\n";
								surfaces_ct--;
							} else if (volumes_ct > 0) {
								id = atoi(strtok(fLine, " "));
								x = std::stod(strtok(NULL, " "));
								y = std::stod(strtok(NULL, " "));
								z = std::stod(strtok(NULL, " "));
								cout << "ID: " << id << "\t";
								cout << "X: " << x << "\t";
								cout << "Y: " << y << "\t ";
								cout << "Z: " << z << "\n";
								volumes_ct--;
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
