#include <iostream>
#include <fstream>

using namespace std;

int main() {
	fstream my_file;
	my_file.open("./data/unit-tetra.geo", ios::in);
	if(!my_file) {
		cout << "File not found!\n";
	} else {
		char c;
		while (my_file.get(c)) {
			cout << c;
		}
		my_file.close();
	}
	return 0;
}
