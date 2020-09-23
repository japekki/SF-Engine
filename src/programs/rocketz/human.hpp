#ifndef HUMAN_HPP
	#define HUMAN_HPP

	#include <vector>
	#include "gamespace.hpp"

	//class Blood : public Water {
		//const SDL_Color color = {200, 0, 0};
	//};

	// Forward declarations:
		class Vehicle;
		class Player;
		class Vector;
		class Item;
		class Weapon;
		class Shield;

	#define WALK_LEFT 0
	#define WALK_RIGHT 1
	#define WALK_UP 2		// With ladders
	#define WALK_DOWN 3		// With ladders
	// TODO: diagonal ladders

	class Human : public Gameblob {
		public:
			std::vector<Weapon*> weapons;
			std::vector<Shield*> shields;
			Player *owner = nullptr;		// nullptr if rogue or expired
			uint16_t air_left = 100;
			unsigned char parachutes = 1;	// Don't get damage if hitting down to ground
			bool parachute_in_use = false;
			bool parachute_burning = false;
			bool falling = false;
			bool swimming = false;
			float acceleration = 0.005;
			//uint32_t fall_distance;
			short temperature = 0;			// minus for cold, plus for hot
			uint16_t ammo = 0;				// TODO: infinite
			bool inside_vehicle = false;
			Vehicle *vehicle = nullptr;		// inside this vehicle
			void repair(Gameblob* gameblob);
			void get_into_vehicle(Vehicle* vehicle);
			void get_out_from_vehicle();
			void steal(Vehicle *vehicle);
			void sabotage(Vehicle *vehicle);		// TODO: sabotage gadgets
			//void plant_virus(Vehicle *vehicle);	// TODO: same as sabotage?
			void walk(unsigned char direction);
			void swim(Vector direction);
			void jump();
			void shoot();	// TODO: always same speed in bullet
			void activate_parachute();
			void fall();
			//void damage(float damage);
			void explode();
			void draw();
			Human(Gameplay* gameplay);
			~Human();
	};

	class Rogue : public Human {
		// Human not belonging to any team
		// Do random stuff
	};

	class Hoarder : public Human {
		// Human that hoards items on the field and take them to base, or vice versa
		// Can also steal items from enemy base
		std::vector<Item*> items;
		void collect(Item *item);
	};

	class Soldier : public Human {
		Player *owner;	// nullptr if rogue
	};

	class Guardian : public Human {
		// Doesn't move a lot, sticks to a single place or patrols a certain area
		// Can stand for example on the entrance of a tunnel or base
	};

#endif // HUMAN_HPP
