#include "zbuf.hpp"
#include <math.h>

Zbuf::Zbuf() {
}

Zbuf::~Zbuf() {
	//delete z;
	//z = nullptr;
}

Zbuf::Zbuf(uint16_t width, uint16_t height) {
	this->width = width;
	this->height = height;
	this->reset();
}

void Zbuf::resize(uint16_t width, uint16_t height) {
	this->width = width;
	this->height = height;
	this->reset();
}

void Zbuf::reset() {
	for (int i=0; i<width*height; i++)
		z[i] = INFINITY;
};
