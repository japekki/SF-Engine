#ifndef PROJECTILE_HPP
	#define PROJECTILE_HPP

	#include "geom.hpp"

	class Projectile2D : public Vector2D {
		public:
			float x, y;	// Location
			void move();
		// Mass
	};

	class Projectile3D : public Vector3D {
		public:
			float x, y, z;	// Location
			void move();
		// Mass
	};

#endif // PROJECTILE_HPP
