#include "level.hpp"

Level::Level(Uint32 width, Uint32 height) {
	this->landpixels.resize(this->width * this->height);
}

Level::~Level() {
	//for (Uint32 i=0; i<(this->width * this->height); i++)
		//delete this->landpixels.at(i);	// ???
}

void Randomlevelgenerator::set_size(Uint32 width, Uint32 height) {
	this->width = width;
	this->height = height;
}

void Randomlevelgenerator::generate() {
	Level *level;
	level = new Level(this->width, this->height);
	for (Uint32 y=0; y<this->height; y++) {
		for (Uint32 x=0; x<this->width; x++) {
			//level->landpixels.at(y * this->width + x) = nullptr;
		}
	}
	this->level = level;
}

Randomlevelgenerator::Randomlevelgenerator(Uint32 width, Uint32 height) {
}

Randomlevelgenerator::~Randomlevelgenerator() {
	delete this->level;	// ???
}
