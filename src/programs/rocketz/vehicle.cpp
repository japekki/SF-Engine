#include "misc.hpp"
#include "human.hpp"
#include "vehicle.hpp"
#include "color.hpp"
#include "space.hpp"
#include "player.hpp"
#include "geometry.hpp"
#include "weapon.hpp"
#include "gameplay.hpp"

Vehicle::Vehicle(Gameplay* gameplay) : Gameblob(gameplay) {
	type = GAMEBLOB_TYPE_VEHICLE;
	can_collect = true;
	mass = 300;
	collision_radius = 3;
	health = 30;
	max_health = 500;
}

Vehicle::~Vehicle() {
}

void Vehicle::explode() {
	// TODO: burst some items inside to outside to the field, make some bursted items deteriorate, delete some items
	if (driver != nullptr)
		driver->get_out_from_vehicle();	// TODO: Weapon_ejectionseat
	Gameblob::explode();
	heading.i = 0;
	heading.j = 0;
}

void Vehicle::damage(float damage) {
	Gameblob::damage(damage);
	if (driver != nullptr)
		driver->damage(damage/100);	// TODO: Parameter for how much a vehicle shields its driver
}

void Vehicle::move() {
	if (in_slowdown_mode) {
		heading.i *= 0.95;
		heading.j *= 0.95;
	}
	// Move Vehicle itself:
		Projectile::move();
	// Move driver inside Vehicle:
		if (driver != nullptr) {
			driver->location = this->location;
			driver->heading = this->heading;
			// NOTE:
			// Human might have been moved on screen already before we are executing this,
			// depending on the order of Blobs in array
		}
	// Move Items inside Vehicle:
		// TODO
}

void Vehicle::rotate_cw() {
	if (in_slowdown_mode)
		Projectile::rotate(this->rotation_speed/2);
	else
		Projectile::rotate(this->rotation_speed);
}

void Vehicle::rotate_ccw() {
	if (in_slowdown_mode)
		Projectile::rotate(-this->rotation_speed/2);
	else
		Projectile::rotate(-this->rotation_speed);
}

void Vehicle::toggle_slowdown() {
	in_slowdown_mode = !in_slowdown_mode;
}

void Vehicle::create_polygon() {
}

//void Vehicle::inc_speed(int amount) {
//	projectile->inc_speed(amount);
//}

//void Vehicle::dec_speed(int amount) {
//	projectile->dec_speed(amount);
//}

//void Vehicle::move() {
	//log("Vehicle::move");
	//projectile->move();
	//polygon->move(Vector(heading.i*speed, heading.j*speed));
	//Blob::move();
//}

//void Vehicle::rotate(float angle) {
	//projectile->rotate(angle);
	//polygon->rotate(angle);
//}

uint32_t Vehicle::get_fuel() {
	return fuel;
}

void Vehicle::accelerate() {
}

void Vehicle::shoot(uint8_t weapon_index) {
//if ((this->weapons[weapon_index) == nullptr) or (this->weapons[weapon_index) == 0)) log("null weapon\n");
	if (in_slowdown_mode)
		weapons[weapon_index]->shoot(location, heading, angle, weapon_power*0.75);
	else
		weapons[weapon_index]->shoot(location, heading, angle, weapon_power);
}

Jetpack::Jetpack(Gameplay* gameplay) : Vehicle(gameplay) {
}

Jetpack::~Jetpack() {
}

void Jetpack::accelerate() {
	if (direction == DIRECTION_RIGHT)
		heading.i += acceleration;
	else if (direction == DIRECTION_LEFT)
		heading.i -= acceleration;
	heading.j -= acceleration;
}

void Rocket::accelerate() {
	if (fuel > 0) {
		//Vehicle::accelerate();
		Vector accel;
		accel.i = 0;
		accel.j = acceleration;
		accel.rotate(angle);
		heading.i += accel.i;
		heading.j += accel.j;
		show_flames = true;
		if (in_slowdown_mode)
			fuel--;
		else
			fuel -= 2;
	}
}

void Boat::accelerate() {
}

void Helicopter::accelerate() {
}

void Rocket2::accelerate() {
}

void Submarine::accelerate() {
}

void Tank::accelerate() {
}

void Tank2::accelerate() {
}

Boat::Boat(Gameplay* gameplay) : Vehicle(gameplay) {
	works_on_air = false;
	works_on_land = false;
	works_on_water = true;
	works_under_water = false;
	can_float = true;
	max_weapons = 2;
}

Boat::~Boat() {
}

void Boat::create_polygon() {
}

//void Boat::move() {
	// TODO
//}

Helicopter::Helicopter(Gameplay* gameplay) : Vehicle(gameplay) {
	works_on_air = true;
	works_on_land = false;
	works_on_water = false;
	works_under_water = false;
	can_float = true;
	max_weapons = 2;
}

Helicopter::~Helicopter() {
}

void Helicopter::create_polygon() {
}

//void Helicopter::move() {
	// TODO
//}

Rocket::Rocket(Gameplay* gameplay) : Vehicle(gameplay) {
	//log("Rocket::Rocket");
	works_on_air = true;
	works_on_land = false;
	works_on_water = true;
	works_under_water = false;
	can_float = true;
	max_weapons = 2;
	this->create_polygon();
	mass = 200;
}

Rocket::~Rocket() {
}

void Rocket::create_polygon() {
	// CREATE TRIANGLES
	Point v1 = Point(0, 2);
	Point v2 = Point(-1.5, -2);
	Point v3 = Point(0, 0.4);

	Triangle* wing_left = new Triangle();
	wing_left->color = COLOR_GREEN;
	wing_left->shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
	wing_left->set_vertexes(v1, v2, v3);

	v1 = Point(0, 2);
	v2 = Point(1.5, -2);
	v3 = Point(0, 0.4);
	Triangle* wing_right = new Triangle();
	wing_right->color = COLOR_GREEN;
	wing_right->shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
	wing_right->set_vertexes(v1, v2, v3);

	this->add_triangle(wing_left);
	this->add_triangle(wing_right);

	v1 = Point(-1.6, -2.1);
	v2 = Point(-1.4, -2.1);
	v3 = Point(-1.5, -3.5);
	Triangle* flame_left = new Triangle();
	flame_left->color = COLOR_ORANGE;
	flame_left->shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
	flame_left->set_vertexes(v1, v2, v3);
	v1 = Point(1.6, -2.1);
	v2 = Point(1.4, -2.1);
	v3 = Point(1.5, -3.5);
	Triangle* flame_right = new Triangle();
	flame_right->color = COLOR_ORANGE;
	flame_right->shadestyle = POLYGON_SHADESTYLE_WIREFRAME;
	flame_right->set_vertexes(v1, v2, v3);

	flames = new Trianglelist();
	flames->add_triangle(flame_left);
	flames->add_triangle(flame_right);
}

void Rocket::draw() {
	gameplay->display->grid_draw_polygon(this, location.x, location.y, angle);
	if (show_flames) {
		gameplay->display->grid_draw_polygon(flames, location.x, location.y, angle);
		show_flames = false;
	}
	// TEST:
		// Draw trace:
		grapher::draw_path(gameplay->display->renderer, trail, SDLCOLOR_GREY);
}

Rocket2::Rocket2(Gameplay* gameplay) : Vehicle(gameplay) {
	works_on_air = true;
	works_on_land = false;
	works_on_water = true;
	works_under_water = true;
	can_float = true;
	max_weapons = 3;
	this->create_polygon();
}

Rocket2::~Rocket2() {
}

void Rocket2::create_polygon() {
}

//void Rocket2::move() {
	// TODO
//}

Submarine::Submarine(Gameplay* gameplay) : Vehicle(gameplay) {
	works_on_air = false;
	works_on_land = false;
	works_on_water = true;
	works_under_water = true;
	can_float = true;
	max_weapons = 3;
}

Submarine::~Submarine() {
}

void Submarine::create_polygon() {
}

//void Submarine::move() {
	// TODO
//}

Tank::Tank(Gameplay* gameplay) : Vehicle(gameplay) {
	works_on_air = false;
	works_on_land = true;
	works_on_water = false;
	works_under_water = false;
	can_float = false;
	max_weapons = 1;
}

Tank::~Tank() {
}

//Tank::accelerate() {
	// TODO
//}

void Tank::create_polygon() {
}

//void Tank::move() {
	// TODO
//}

Tank2::Tank2(Gameplay* gameplay) : Vehicle(gameplay) {
	works_on_air = false;
	works_on_land = true;
	works_on_water = false;
	works_under_water = false;
	can_float = false;
	max_weapons = 2;
}

Tank2::~Tank2() {
}

void Tank2::create_polygon() {
}

//void Tank2::move() {
	// TODO
//}
