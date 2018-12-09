#include "bullet.hpp"

Bullet::Bullet(Player *owner, Coordinate2D coordinate, Vector2D direction) {
	this->x = coordinate.x;
	this->y = coordinate.y;
	this->direction = direction;
}
