#include "vehicle.hpp"

Vehicle::Vehicle() {
}

Vehicle::~Vehicle() {
}

void Vehicle::respawn(Base *base) {
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

Helicopter::Helicopter() {
	works_on_air = true;
	works_on_land = false;
	works_on_water = false;
	works_under_water = false;
	can_float = true;
}

Rocket::Rocket() {
	works_on_air = true;
	works_on_land = false;
	works_on_water = true;
	works_under_water = false;	// advanced models can go under water
	can_float = true;
}

Submarine::Submarine() {
	works_on_air = false;
	works_on_land = false;
	works_on_water = true;
	works_under_water = true;
	can_float = true;
}

Tank::Tank() {
	works_on_air = false;
	works_on_land = true;
	works_on_water = false;
	works_under_water = false;
	can_float = false;
}
