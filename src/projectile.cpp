#include "projectile.hpp"
#include <iostream>
#include "geom.hpp"

Projectile::Projectile() {
}

Projectile::~Projectile() {
}

float Projectile::get_speed() {
	return this->speed;	// TODO
}

void Projectile::inc_speed(float amount) {
	this->speed += amount;
	printf("Speed: %f\n", this->speed);
}

void Projectile::dec_speed(float amount) {
	this->speed -= amount;
	printf("Speed: %f\n", this->speed);
}

float Projectile::get_momentum() {
	return this->mass * this->get_speed();
}

void Projectile::move() {
	this->location->x += direction->i;
	this->location->y += direction->j;
}

void Projectile::rotate(float angle) {
	this->rotation = angle;
}

bool Projectile::collides(Projectile *projectile) {
	// TODO
	return false;
}

std::vector<Projectile*> Projectile::list_colliding_projectiles(std::vector<Projectile*> projectiles) {
	// TODO
	std::vector<Projectile*> colliding;
	return colliding;
}

void collide(Projectile *projectile1, Projectile *projectile2) {
	// TODO
}

