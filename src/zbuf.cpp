#include "zbuf.hpp"

Zbuf::Zbuf() {
}

Zbuf::Zbuf(unsigned short width, unsigned short height) {
	this->width = width;
	this->height = height;
}

void Zbuf::set_size(unsigned short width, unsigned short height) {
	this->width = width;
	this->height = height;
}

void Zbuf::reset() {
	unsigned int i;
	for (i=0; i<z.size(); i++)
		z.at(i)=1000000.0;
};
