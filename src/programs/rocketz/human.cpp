#include "human.hpp"
#include "vehicle.hpp"
#include "geom.hpp"

void Human::get_into_vehicle(Vehicle* vehicle) {
	this->vehicle = vehicle;
	this->vehicle->driver = this;
	this->inside_vehicle = true;
}

void Human::get_out_from_vehicle() {
	this->vehicle->driver = nullptr;
	this->inside_vehicle = false;
	this->vehicle = nullptr;
}

void Human::steal(Vehicle *vehicle) {
	// TODO: some kind of fighting if driver already aboard
	vehicle->driver->inside_vehicle = false;	// Kick current driver out
	this->get_into_vehicle(vehicle);
	// TODO: Change vehicle's owner
}

void Human::sabotage(Vehicle *vehicle) {
	if (vehicle->sabotable) vehicle->sabotaged = true;
}

void Human::walk(unsigned char direction) {
	if (!this->falling and !this->swimming) {
		// alter position
		// draw animation
	}
}

void Human::swim(Vector2D direction) {
	//TODO:
	//if (below water surface)
		// alter position
			// draw animation
		//	if (this->air_left > 0) this->air_left--;
		if (this->air_left <= 0) this->get_damage(1);
}

void Human::collect(Item *item) {
	// Use item immediately
}

void Human::shoot() {
	if (this->ammo > 0) {
		this->ammo--;
		//play sound
	}
}

/*
void Human::heal(unsigned short health) {
	this->health += health;
	if (this->health > this->max_health) health = max_health;	// TODO: leave some health left into medkit
	//play sound
}
*/

void Human::fall() {
	//TODO: gravity affects fall_distance
	this->fall_distance++;
	//play sound
	if (this->fall_distance > 100) {
		if (this->parachutes > 0) {
			//activate parachute
			//this->fall_distance = 0;
			//TODO: restart falling if parachute has burned out
		} else {
			//TODO:
			// check if hits to ground, give damage by fall_distance
			// check if falls into water, check if land is hard or soft
			// regular collisions apply (can collect items, get hit by bullets etc.)
		}
	}
}

void Human::get_damage(unsigned short damage) {
	if (this->health > damage) {
		this->health =- damage;
		//play sound
	} else this->die();
}

void Human::die() {
	//play sound
	//burst blood
}

void Hoarder::collect(Item *item) {
	this->items.push_back(item);
}
