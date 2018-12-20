/*
TODO:
- Class template for 2D and 3D Projectile
- Convert from 2D to 3D and vice versa
- Calculate damages when colliding
*/

#ifndef PROJECTILE_HPP
	#define PROJECTILE_HPP

	#include <vector>

	/*
		TODO: Curve and current heading
		class Trajectory2D {
			Vector2D heading;
		};
		class Trajectory3D {
			Vector3D heading;
		};
	*/

	// Forward declarations:
		class Point;
		class Vector2D;

	class Projectile {
		public:
			Point* location;		// Center point
			float rotation = 0;		// angle
			float mass;
			float speed = 0;
			Vector2D* direction;		// Where is it going to and how fast
			Projectile();
			~Projectile();
			float get_speed();
			void set_speed(float speed);
			void inc_speed(float amount);
			void dec_speed(float amount);
			float get_momentum();
			void move();
			void rotate(float angle);
			bool collides(Projectile *projectile);
			std::vector<Projectile*> list_colliding_projectiles(std::vector<Projectile*> projectiles);
	};

	void collide(Projectile *projectile1, Projectile *projectile2);	// Alter direction/speed in both projectiles

#endif // PROJECTILE_HPP
