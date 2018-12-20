#include "bullet.hpp"
#include "misc.hpp"

/*
Bullet::Bullet(Player *owner, Point coordinate, Vector2D direction) {
	this->x = coordinate.x;
	this->y = coordinate.y;
	this->direction = direction;
}
*/

Bullet::Bullet() {
	log("Bullet created.");
}

Bullet::~Bullet() {
	log("Bullet destroyed.");
}
