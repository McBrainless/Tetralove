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
	string filename = "./data/unit-tetra.msh";
	app.load_msh(&filename);
	return 0;
}
