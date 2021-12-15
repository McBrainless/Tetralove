#include "./headers/surface3d.hpp"

int surface3d::count = 0;

surface3d::surface3d() {
	surface3d::count++;
	this->id = count;
}
