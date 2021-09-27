#include "./headers/application.hpp"

application::application(void) {
	this->state = initial;
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
					} 					break;
				case MeshFormat:
					if (strstr(fLine, "$EndMeshFormat")) {
						this->state = initial;
						cout << "Loaded: MeshFormat.\n";
					}
					break;
				case Entities:
					if (strstr(fLine, "$EndEntities")) {
						this->state = initial;
						cout << "Loaded: Entities.\n";
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
