#ifndef PROJECTILE_HPP
	#define PROJECTILE_HPP

	#include "geom.hpp"

	class Projectile2D : public Vector2D {
		public:
		// Location:
			float x = 0;
			float y = 0;
		// Heading
		// Speed
		// Mass
	};

	class Projectile3D : public Vector3D {
		public:
		// Location:
			float x = 0;
			float y = 0;
			float z = 0;
		// Heading
		// Speed
		// Mass
	};

#endif // PROJECTILE_HPP
