#ifndef SPACE_HPP
	#define SPACE_HPP

	#include <vector>
	#include "geometry.hpp"

	/*
		TODO: Curve and current heading
		class Trajectory {
			Vector heading;
		};
	*/

	// Forward declarations:
		class Point;

	class Projectile {
		private:
			float max_speed = 0;
		public:
			Point location;		// Center point
			Point previous_location;
			float collision_radius = 0;		// TODO: Bounding box (or something even better)
			uint32_t trail_max_length = 0;
			Path* trail = nullptr;			// old trajectory
			float angle = 0;
			float mass = 0;
			Vector heading;	// Where is it going to and how fast
			Projectile();
			~Projectile();
			Point get_location();
			float get_speed();
			float get_max_speed();
			float get_momentum();
			void push(Vector direction);
			virtual void move();
			void set_rotation(float angle);		// absolute
			virtual void rotate(float angle);			// relative
			//bool collides(Projectile *projectile);
			std::vector<Projectile*> list_colliding_projectiles(std::vector<Projectile*> projectiles);
	};

	void collide(Projectile *projectile1, Projectile *projectile2);	// Alter direction/speed in both projectiles

	class Blob : public Projectile {
		public:
			uint8_t type = 0;
			bool stationary = false;	// Fixed position, does not move
			float attract_force = 0;
			float repel_force = 0;
			bool can_collide = true;
			// TODO:
				//short temperature_combust;
				//short temperature;	// current temperature
			Blob();
			~Blob();
			//virtual void move();
			virtual void draw();
	};


	class Blob_polygon : public Blob, public Trianglelist {
		public:
			Blob_polygon();
			~Blob_polygon();
			virtual void create_polygon();
			virtual void draw();
	};

	class Blackhole : public Blob {
		// Destroys anything going in
		public:
			Blackhole();
			~Blackhole();
			int gravity = 0;	// negative numbers repel and make it white
	};

	class Wormhole : public Blob {
		// Transports anything going in
		// starting_point
		// ending_point
		Wormhole();
		~Wormhole();
		bool works_both_ways = true;	// TODO: gravity for one-way wormholes
	};

	#define SPACE_DELETE 0
	#define SPACE_BOUNCE 1
	#define SPACE_LOOP 2

	class Space {
		public:
			uint8_t wall_mode = SPACE_BOUNCE;
			uint8_t ceiling_mode = SPACE_BOUNCE;
			uint8_t floor_mode = SPACE_DELETE;
			uint32_t total_blobs = 0;
			uint32_t max_blobs = 0;
			uint32_t collisions = 0;
			uint32_t max_collisions = 0;
			uint32_t total_collisions = 0;
			float gravity = 0.0095;
			float airresistance = 0.995;	// 0 = stop immediately, 1 = no resistance
			float width = 0;
			float height = 0;
			Space();
			Space(float width, float height);
			//unsigned char edgetype = 2;	// 0 = delete object 1 = warp, 2 = bounce
			std::vector<Blob*> blobs;
			void add_blob(Blob* blob);
			virtual void move_blobs();
			void apply_gravity();
			void apply_airresistance();
			Blob* get_nearest_blob(Blob* object, uint8_t type);
	};

#endif // SPACE_HPP
