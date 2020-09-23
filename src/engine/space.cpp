#include <iostream>
#include <math.h>
#include "space.hpp"
#include "geometry.hpp"
#include "misc.hpp"

Projectile::Projectile() {
	//log("Projectile::Projectile");
	trail = new Path;
}

Projectile::~Projectile() {
	delete trail;
}

void Projectile::push(Vector direction) {
	this->heading.i += direction.i;
	this->heading.j += direction.j;
}

Point Projectile::get_location() {
	return this->location;
}

float Projectile::get_speed() {
	return sqrt(heading.i * heading.i + heading.j * heading.j);
}

float Projectile::get_max_speed() {
	return this->max_speed;
}

float Projectile::get_momentum() {
	return mass * this->get_speed();
}

void Projectile::move() {
	//log("Projectile::move");
	if (trail_max_length > 0) {
		trail->append(location);
		if (trail->get_length() == trail_max_length)
			trail->points.erase(trail->points.begin());
	}
	if (this->get_speed() > max_speed)
		max_speed = this->get_speed();
	previous_location = location;
	location.x += heading.i;
	location.y += heading.j;
}

#define angle_right	-PIPER2
#define angle_left	PIPER2
#define angle_up	PI
#define angle_down	0

void Projectile::rotate(float angle) {
	this->angle += angle;
	// Keep angle between -PI/2 and +PI/2:
		for (; this->angle >= PI; this->angle -= PIX2);
		for (; this->angle <= -PI; this->angle += PIX2);
}

/*
bool Projectile::collides(Projectile *projectile) {
	if (this->location.x == projectile->location.x and this->location.y == projectile->location.y)
		return true;
	return false;
}
*/
std::vector<Projectile*> Projectile::list_colliding_projectiles(std::vector<Projectile*> projectiles) {
	// TODO
	std::vector<Projectile*> colliding;
	return colliding;
}

void collide(Projectile *projectile1, Projectile *projectile2) {
	Vector tmp = projectile1->heading;
	projectile1->heading.add(projectile2->heading);
	projectile2->heading.sub(tmp);
}

Blob::Blob() {
	location.x = 0;
	location.y = 0;
}

Blob::~Blob() {
}

//void Blob::move() {
//	log("Blob::move()");
//}

void Blob::draw() {
	log("Blob::draw()\n");
}

//Blob_polygon::Blob_polygon() {
//}

Blob_polygon::Blob_polygon() : Blob() {
}

Blob_polygon::~Blob_polygon() {
}

void Blob_polygon::create_polygon() {
}

void Blob_polygon::draw() {
	//log("Blob_polygon::draw()\n");
	//gameplay->display->grid_draw_polygon(this, location.x, location.y, angle);
}

Blackhole::Blackhole() {
	stationary = true;
}

Blackhole::~Blackhole() {
	stationary = true;
}

Wormhole::Wormhole() {
}

Wormhole::~Wormhole() {
}

Blob* Space::get_nearest_blob(Blob* object, uint8_t type) {
	std::vector<Blob*> objects;
	for (uint32_t i=0; i<blobs.size(); i++) {
		if (blobs[i]->type == type)
			objects.push_back(blobs[i]);
	}

	float lowest_distance = 1000000;
	int nearest_object = -1;
	for (uint32_t i=0; i<objects.size(); i++) {
		float distance = get_distance(blobs[i]->location, object->location);
		if (distance < lowest_distance) {
			lowest_distance = distance;
			nearest_object = i;
		}
	}

	return objects[nearest_object];
}

Space::Space() {
}

Space::Space(float width, float height) {
	this->width = width;
	this->height = height;
}

void Space::add_blob(Blob* blob) {
	blobs.push_back(blob);
	total_blobs++;
}

/*
void Gamespace::process_objects() {
	for (int i = 0; i<projectiles.size(); i++) {
		projectile[i).move();
		projectile[i).rotate();
	}
}
*/

void Space::apply_gravity() {
	//log("Space::apply_gravity()");
	for (uint32_t i=0; i<blobs.size(); i++) {
		// Fall down:
			blobs[i]->heading.j += gravity;
		// TODO: Each blob attracts each blob
	}
}

void Space::apply_airresistance() {
	//log("Space::apply_airresistance()");
	for (uint32_t i=0; i<blobs.size(); i++) {
		blobs[i]->heading.i *= airresistance;
		blobs[i]->heading.j *= airresistance;
	}
}

void Space::move_blobs() {
	for (uint32_t i=0; i<blobs.size(); i++)
		blobs[i]->move();
}
