#ifndef HUMAN_HPP
	#define HUMAN_HPP

	#include "item.hpp"
	#include "player.hpp"
	#include "geom.hpp"
	//#include "vehicle.hpp"

	#include <vector>

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_HUMANHEAL DATAPATH "humanheal.wav"
			#define FILENAME_SOUND_HUMANSCREAM DATAPATH "humanscream.wav"	// get hit
			#define FILENAME_SOUND_HUMANYELL DATAPATH "humansyell.wav"		// die

	//class Blood : public Water {
		//const SDL_Color color = {200, 0, 0};
	//};

	// Forward declarations:
		class Item;
		class Vehicle;

	#define WALK_LEFT 0
	#define WALK_RIGHT 1
	#define WALK_UP 2	// With ladders
	#define WALK_DOWN 3	// With ladders
	// TODO: diagonal ladders

	class Human {
		public:
			// max_speed
			Player *owner = nullptr;	// nullptr if rogue
			unsigned short max_health = 100;
			short health;
			unsigned short air_left;	// TODO: infinite
			unsigned char parachutes;	// Don't get hit if dropping down to ground
			bool falling;
			bool swimming;
			unsigned int fall_distance;
			bool parachute_burning = false;
			short temperature;	// minus for cold, plus for hot
			unsigned short ammo;	// TODO: infinite
			bool inside_vehicle;
			void steal(Vehicle *vehicle);
			void sabotage(Vehicle *vehicle);	// TODO: sabotage gadgets
			//void plant_virus(Vehicle *vehicle);	// TODO: same as sabotage?
			void walk(Uint8 direction);
			void swim(Vector2D direction);
			void collect(Item *item);
			void shoot(Vector2D direction);	// TODO: always same speed in bullet
			//void heal(unsigned short health);
			void fall();
			void get_damage(unsigned short damage);
			void die();
	};

	class Rogue : public Human {
		// Human not belonging to any player (or team)
	};

	class Hoarder : public Human {
		// Human that hoards items on the field and take them to base, or vice versa
		// Can also steal items from enemy base
		std::vector<Item*> items;
		void collect(Item *item);
	};

	class Soldier : public Human {
		Player *owner;	// nullptr if rogue
		short lifeforce;
	};

	class Guardian : public Human {
		// Doesn't move a lot, sticks to a single place or patrols a certain area
		// Can stand for example on the entrance of a tunnel or base
	};

#endif // HUMAN_HPP