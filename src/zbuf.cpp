#include "zbuf.hpp"

Zbuf::Zbuf() {
}

Zbuf::~Zbuf() {
}

Zbuf::Zbuf(unsigned short width, unsigned short height) {
	this->width = width;
	this->height = height;
	this->reset();
}

void Zbuf::resize(unsigned short width, unsigned short height) {
	this->width = width;
	this->height = height;
	this->reset();
}

void Zbuf::reset() {
	// TODO: is there a faster way to do this?
	unsigned int i;
	for (i=0; i<z.size(); i++)
		z.at(i)=1000.0;
};
