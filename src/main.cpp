#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "./headers/application.hpp"

using namespace std;

/***
 *
 *	strrem - clear string of character
 *
 ***/
void strrem(char* cstring, const char delim) {
	uint16_t size = strlen(cstring), loc = 0;
	for (uint16_t x = 0; x<size; x++) {
		if (cstring[x] != delim) {
			cstring[loc] = (loc != x) ? cstring[x] : cstring[loc];
			loc++;
		}
	}
	cstring[loc] = '\0';
}

int main() {
	application app;
#ifdef LINUX
	string filename = "./data/unit-tetra.msh";
#elif _WINDOWS
	string filename = "data/unit-tetra.msh";
#else
	string filename = "\n";
#endif // OS

	cout << "Opening file: " << filename << "\n";
	app.load_msh(&filename);
	return 0;
}
