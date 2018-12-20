//#include "misc.hpp"
#include "human.hpp"
#include "vehicle.hpp"
#include "color.hpp"
#include "bullet.hpp"
#include "projectile.hpp"
#include "player.hpp"
#include "geom.hpp"
#include "weapon.hpp"

Vehicle::Vehicle() {
}

Vehicle::~Vehicle() {
}

void Vehicle::inc_speed(int amount) {
	this->projectile->inc_speed(amount);
}

void Vehicle::dec_speed(int amount) {
	this->projectile->dec_speed(amount);
}

void Vehicle::respawn(Base *base) {
	// Set location to random base
}

void Vehicle::explode() {
	// burst some items inside to outside to the field, make some bursted items deteriorate, delete some items
	// Kill driver inside:
		if (this->driver != nullptr) this->driver->die();
}

Boat::Boat() {
	works_on_air = false;
	works_on_land = false;
	works_on_water = true;
	works_under_water = false;
	can_float = true;
}

Boat::~Boat() {
}

Helicopter::Helicopter() {
	works_on_air = true;
	works_on_land = false;
	works_on_water = false;
	works_under_water = false;
	can_float = true;
}

Helicopter::~Helicopter() {
}

Rocket::Rocket() {
	works_on_air = true;
	works_on_land = false;
	works_on_water = true;
	works_under_water = false;	// advanced models can go under water
	can_float = true;
	this->create_polygon();
}

Rocket::~Rocket() {
}

void Rocket::create_polygon() {
	// CREATE TRIANGLES:
		Point* v1 = new Point(0, 1);
		Point* v2 = new Point(-0.75, -1);
		Point* v3 = new Point(0, 0.1);

		Triangle* wing_left = new Triangle();
		wing_left->color = COLOR_GREEN;
		wing_left->shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
		wing_left->set_vertexes(v1, v2, v3);

		v1 = new Point(0, 1);
		v2 = new Point(0.75, -1);
		v3 = new Point(0, 0.1);
		Triangle* wing_right = new Triangle();
		wing_right->color = COLOR_GREEN;
		wing_right->shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
		wing_right->set_vertexes(v1, v2, v3);

		this->polygon = new Polygon();
		this->polygon->add_triangle(wing_left);
		this->polygon->add_triangle(wing_right);
}

Submarine::Submarine() {
	works_on_air = false;
	works_on_land = false;
	works_on_water = true;
	works_under_water = true;
	can_float = true;
}

Submarine::~Submarine() {
}

Tank::Tank() {
	works_on_air = false;
	works_on_land = true;
	works_on_water = false;
	works_under_water = false;
	can_float = false;
}

Tank::~Tank() {
}
