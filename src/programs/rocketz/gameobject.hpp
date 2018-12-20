#ifndef GAMEOBJECT_HPP
	#define GAMEOBJECT_HPP

	class Player;
	class Projectile;
	class Point;
	class Polygon;

	class Gameobject {
		public:
			float attract_force = 0;
			float repel_force = 0;
			Point* location;
			Player* owner;
			Polygon* polygon;
			Projectile* projectile;
			Gameobject();
			~Gameobject();
			virtual void create_polygon();
			Point* get_location();
			void move();
			void rotate(float angle);
			virtual void explode();
	};

#endif // GAMEOBJECT_HPP
