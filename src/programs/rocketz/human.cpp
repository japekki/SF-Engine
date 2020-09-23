#include "human.hpp"
#include "vehicle.hpp"
#include "geometry.hpp"
#include "player.hpp"
#include "display.hpp"
#include "gameplay.hpp"
//#include "item.hpp"

Human::Human(Gameplay* gameplay) : Gameblob(gameplay) {
	type = GAMEBLOB_TYPE_HUMAN;
	can_collect = true;
	mass = 100;
	collision_radius = 0.5;
	health = 50;
	max_health = 100;
}

Human::~Human() {
}

void Human::repair(Gameblob* gameblob) {
	if (gameblob->type == GAMEBLOB_TYPE_VEHICLE
	or gameblob->type == GAMEBLOB_TYPE_BUILDING) {
		// gameblob->heal();
		// gameblob->emped = false;
	}
}

void Human::get_into_vehicle(Vehicle* vehicle) {
	if (vehicle->health > 0) {
		this->vehicle = vehicle;
		this->vehicle->driver = this;
		this->inside_vehicle = true;
		this->location = vehicle->location;
		this->heading.i = vehicle->heading.i;
		this->heading.j = vehicle->heading.j;
		this->can_collide = false;
	}
}

void Human::get_out_from_vehicle() {
		this->vehicle->driver = nullptr;
		this->inside_vehicle = false;
		this->location = this->vehicle->location;
		this->heading = this->vehicle->heading;
		this->vehicle = nullptr;
		this->can_collide = true;
}

void Human::steal(Vehicle *vehicle) {
	// TODO: some kind of fighting if driver already aboard
	vehicle->driver->get_out_from_vehicle();	// Kick current driver out
	get_into_vehicle(vehicle);
	vehicle->owner = this->owner;
}

void Human::sabotage(Vehicle *vehicle) {
	if (vehicle->sabotable)
		vehicle->sabotaged = true;
}

void Human::walk(unsigned char direction) {
	if (!falling and !swimming) {
		if (direction == WALK_LEFT)
			heading.i -= acceleration;
		else if (direction == WALK_RIGHT)
			heading.i += acceleration;
	}
}

void Human::swim(Vector direction) {
	//TODO:
	//if (below water surface)
		// alter position
			// draw animation
		//	if (air_left > 0) air_left--;
		if (air_left <= 0)
			damage(1);
}

void Human::jump() {
	// TODO: Jump only if standing on ground, not falling or swimming
	heading.j -= acceleration*100;
}

void Human::shoot() {
	if (ammo > 0) {
		//weapons[0)->shoot(location, heading, angle, 1);
		ammo--;
	}
}

void Human::activate_parachute() {
	if (!parachute_in_use)
		if (parachutes > 0) {
			parachute_in_use = true;
			parachutes--;
		}
}

void Human::fall() {
	//TODO: gravity affects fall_distance
	//fall_distance++;
	//play sound
	//if (fall_distance > 100) {

			//fall_distance = 0;
			//TODO: restart falling if parachute has burned out

			//TODO:
			// check if hits to ground, give damage by fall_distance
			// check if falls into water, check if land is hard or soft
			// regular collisions apply (can collect items, get hit by bullets etc.)
	//}
}

void Human::explode() {
	//TODO: burst blood
	if (health > 0)
		health = 0;
	gameplay->play_scream = true;
	owner->spawn();
}

void Human::draw() {
	if (!inside_vehicle) {
		// Draw head:
			//grapher->draw_circle();
		// Draw torso:
			gameplay->display->grid_draw_line(Point(location.x, location.y), Point(location.x, location.y + 0.4), 0xc0, 0xa0, 0x00, 0xff);
		// Draw hands:
			gameplay->display->grid_draw_line(Point(location.x, location.y + 0.2), Point(location.x + 0.2, location.y + 0.12), 0xc0, 0xa0, 0x00, 0xff);
			gameplay->display->grid_draw_line(Point(location.x, location.y + 0.2), Point(location.x - 0.2, location.y + 0.12), 0xc0, 0xa0, 0x00, 0xff);
		// Draw legs:
			gameplay->display->grid_draw_line(Point(location.x, location.y + 0.4), Point(location.x + 0.2, location.y + 0.48), 0xc0, 0xa0, 0x00, 0xff);
			gameplay->display->grid_draw_line(Point(location.x, location.y + 0.4), Point(location.x - 0.2, location.y + 0.48), 0xc0, 0xa0, 0x00, 0xff);
		// Draw parachute:
			//if (falling)
			if (parachute_in_use)
				gameplay->display->grid_draw_line(Point(location.x - 1, location.y - 0.5), Point(location.x + 1, location.y - 0.5), 0xee, 0xee, 0xee, 0xff);
	}
}

void Hoarder::collect(Item *item) {
	items.push_back(item);
}
