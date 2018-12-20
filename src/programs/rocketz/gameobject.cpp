#include "gameobject.hpp"
#include "geom.hpp"
#include "projectile.hpp"

Gameobject::Gameobject() {
	this->polygon = new Polygon();
	this->projectile = new Projectile();
	this->location = new Point();
}

Gameobject::~Gameobject() {
}

void Gameobject::create_polygon() {
}

Point* Gameobject::get_location() {
	return this->location;
}

void Gameobject::move() {
	// TODO
	// TEST:
		//this->location->x += ẗhis->direction.i;
		//this->location->y += ẗhis->direction.j;
}

void Gameobject::rotate(float angle) {
	this->projectile->rotate(angle);
	this->polygon->rotate(angle);
}

void Gameobject::explode() {
}
