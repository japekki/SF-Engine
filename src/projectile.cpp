#include "projectile.hpp"

void Projectile2D::move() {
	x += i;
	y += j;
}

void Projectile3D::move() {
	x += i;
	y += j;
	z += k;
}
