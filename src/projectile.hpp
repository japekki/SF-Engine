/*
TODO:
- Calculate damages when colliding
- Self rotate
*/

#ifndef PROJECTILE_HPP
	#define PROJECTILE_HPP

	#include "geom.hpp"

	/*
		TODO: Curve and current heading
		class Trajectory2D {
			Vector2D heading;
		};
		class Trajectory3D {
			Vector3D heading;
		};
	*/

	class Projectile2D : public Coordinate2D {
		public:
			float mass;
			Vector2D direction;	// Where is it going to and how fast
			float get_speed();
			float get_momentum();
			void move();
			bool collides(Projectile2D *projectile);
			std::vector<Projectile2D> list_colliding_projectiles(std::vector<Projectile2D> projectiles);
	};

	class Projectile3D : public Coordinate3D {
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
