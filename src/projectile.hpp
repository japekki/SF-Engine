// TODO:
// - Calculate damages when colliding

#ifndef PROJECTILE_HPP
	#define PROJECTILE_HPP

	#include "geom.hpp"

	//class Trajectory2D {
	//};

	//class Trajectory3D {
	//};

	class Projectile2D {
		public:
			float mass;
			float x, y;			// Location
			Vector2D direction;	// Where is it going to and how fast
			float get_speed();
			float get_momentum();
			void move();
			bool collides(Projectile2D *projectile);
	};

	class Projectile3D {
		public:
			float mass;
			float x, y, z;		// Location
			Vector3D direction;	// Where is it going to and how fast
			float get_speed();
			float get_momentum();
			void move();
			bool collides(Projectile3D *projectile);
	};

	void collide(Projectile2D *projectile1, Projectile2D *projectile2);	// Alter direction/speed in both projectiles
	void collide(Projectile3D *projectile1, Projectile3D *projectile2);	// Alter direction/speed in both projectiles

#endif // PROJECTILE_HPP
