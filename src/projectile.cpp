#include "projectile.hpp"

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

void collide(Projectile2D *projectile1, Projectile2D *projectile2) {
	// TODO
}

void collide(Projectile3D *projectile1, Projectile3D *projectile2) {
	// TODO
}
