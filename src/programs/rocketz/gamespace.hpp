/*
A "blob" is an object in space.
Usually drawn and has physical properties.

TODO:
- Bitmap blobs
- Vector blobs
- Blob animation
*/

#ifndef GAMESPACE_HPP
	#define GAMESPACE_HPP

	#include "space.hpp"

	// TYPES
	// Each gameblob is one of these:
		#define GAMEBLOB_TYPE_UNDEFINED		0
		#define GAMEBLOB_TYPE_VEHICLE		1
		#define GAMEBLOB_TYPE_BULLET		2
		#define GAMEBLOB_TYPE_BLOCKBULLET	3
		#define GAMEBLOB_TYPE_HUMAN			4
		#define GAMEBLOB_TYPE_BEAM			5
		#define GAMEBLOB_TYPE_ITEM			6
		#define GAMEBLOB_TYPE_BASE			7
		#define GAMEBLOB_TYPE_GAUGE			8		// Like bomb timer, guide arrow etc.
		#define GAMEBLOB_TYPE_BUILDING		9

		#define COLLISION_TYPE_NONE 0
		#define COLLISION_TYPE_NORMAL 1

		#define EDGE_TYPE_NONE 0
		#define EDGE_TYPE_STOP 1
		#define EDGE_TYPE_BOUNCE 2
		#define EDGE_TYPE_LOOP 3
		#define EDGE_TYPE_DELETE 4

	// FEATURES
	// Each gameblob can feature one or more of these:
		#define GAMEBLOB_FEAT_PARTICLE		1
		#define GAMEBLOB_FEAT_KNOCKER		1 << 1		// Knocks blobs away (ignores mass when collides)

	class Player;
	class Gameplay;
	class Item;

	class Gameblob : public Blob {
		public:
			// TODO:
				//short temperature_combust;
				//short temperature;	// current temperature
			uint8_t features = 0;
			bool can_expire = false;
			bool can_collect = false;
			int expirecounter = 0;	// Decrease during time, delete blob when time left == 0
			bool is_expired();
			float max_health = 0;
			float health = 0;
			Gameplay* gameplay;
			Player* owner = nullptr;
			Gameblob(Gameplay* gameplay);
			virtual ~Gameblob();
			void draw();
			void age();
			virtual void explode();
			void heal(float health);
			virtual void damage(float damage);
			void use_item(Item* item);
	};

	//class Collector {
	//	public:
	//		void collect(Item *item);
	//};

	class Gamespace : public Space {
		public:
			Gameplay* gameplay;
			std::vector<Gameblob*> blobs;
			//std::vector<Gameblob*> new_blobs;
			uint8_t wall_type = EDGE_TYPE_BOUNCE;
			uint8_t ceiling_type = EDGE_TYPE_BOUNCE;
			uint8_t floor_type = EDGE_TYPE_DELETE;
			uint8_t collision_type = COLLISION_TYPE_NORMAL;
			Gamespace(Gameplay* gameplay);
			~Gamespace();
			void add_blob(Gameblob* blob);	// DO NOT USE WHILE ITERATING blobs
			//void add_new_blobs();
			void move_blobs();
			// FIXME: These should reside in Space class but access Gamespace->blobs instead of Space->blobs
				void apply_gravity();
				void apply_airresistance();
				uint32_t apply_collisions();	// Changes headings, deals damage, returns the amount of collisions
				void apply_blackholes();
				// TODO: Optimize by combining the routines above into a single iteration/function

			void age();
			//void apply_gravity() override;
			void use_items();
			uint32_t dispose_expired_gameblobs();
	};

#endif // GAMESPACE_HPP
