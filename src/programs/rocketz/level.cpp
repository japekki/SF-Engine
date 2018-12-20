#include "level.hpp"

Level::Level(Uint32 width, Uint32 height) {
	this->width = width;
	this->height = height;
	this->landpixels.resize(width * height);
}

Level::~Level() {
	//for (Uint32 i=0; i<(this->width * this->height); i++)
		//delete this->landpixels.at(i);	// ???
}

void Level::add_layer(Layer *layer) {
	this->layers.push_back(layer);
}

void RandomLevel::set_size(Uint32 width, Uint32 height) {
	this->width = width;
	this->height = height;
}

void RandomLevel::generate() {
	Level *level;
	level = new Level(this->width, this->height);

	// CREATE LAND:
	for (Uint32 y=0; y<this->height; y++) {
		for (Uint32 x=0; x<this->width; x++) {
			//level->landpixels.at(y * this->width + x) = nullptr;
		}
	}
	// CREATE WEATHER:
	// CREATE BLACK HOLES:
	// CREATE ITEMS:
	this->level = level;
}

RandomLevel::RandomLevel(Uint32 width, Uint32 height) {
}

RandomLevel::~RandomLevel() {
	delete this->level;	// ???
}
