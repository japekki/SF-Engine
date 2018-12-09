#include "projectile.hpp"

float Projectile2D::get_speed() {
	// TODO
}

float Projectile2D::get_momentum() {
	return this->mass * this->get_speed();
}

void Projectile2D::move() {
	x += direction.i;
	y += direction.j;
}

void Projectile3D::move() {
	x += direction.i;
	y += direction.j;
	z += direction.k;
}

bool Projectile2D::collides(Projectile2D *projectile) {
}

bool Projectile3D::collides(Projectile3D *projectile) {
}

std::vector<Projectile2D> Projectile2D::list_colliding_projectiles(std::vector<Projectile2D> projectiles) {
}

void collide(Projectile2D *projectile1, Projectile2D *projectile2) {
	// TODO
}

void collide(Projectile3D *projectile1, Projectile3D *projectile2) {
	// TODO
}
