#ifndef VEHICLE_HPP
	#define VEHICLE_HPP

	#include "base.hpp"
	#include "bullet.hpp"
	#include "player.hpp"
	#include "weapon.hpp"

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_CRASH DATAPATH "crash.wav"
			#define FILENAME_SOUND_DIESELMOTOR DATAPATH "dieselmotor.wav"
			#define FILENAME_SOUND_JETENGINE DATAPATH "jetengine.wav"
			#define FILENAME_SOUND_PROPELLER DATAPATH "propeller.wav"

	// Forward declarations:
	class Base;
	class Human;

	class Vehicle : public Polygon2D, public Projectile2D {
		public:
			bool works_on_air;
			bool works_on_land;
			bool works_on_water;
			bool works_under_water;
			bool can_float;
			unsigned short max_speed;
			unsigned char acceleration;
			Player *owner;
			short lifeforce;
			Human *driver;		// nullptr if nobody inside, can also be a rogue
			unsigned char weapon_slots;
			Weapon *primaryweapon;
			Weapon *secondaryweapon;
			std::vector<Bullet*> bullets;
			std::vector<Item*> items_inside;
			// TODO: brakes
			bool autopilot = false;
			bool sabotable = true;
			bool sabotaged = false;
			short temperature;	// minus if cold, plus if hot
			Vehicle();
			~Vehicle();
			void respawn(Base *base);
			void explode();
	};

	class Boat : public Vehicle {
		public:
			char cannon_angle;
			unsigned short cannon_power;
			Boat();
	};

	class Helicopter : public Vehicle {
		public:
			// Sensitive to wind
			// Crashes if propellers are damaged
			Helicopter();
	};

	class Rocket : public Vehicle {
		public:
			Rocket();
	};

	class Submarine : public Vehicle {
		public:
			Submarine();
	};

	class Tank : public Vehicle {
		public:
			char cannon_angle;
			unsigned short cannon_power;
			Tank();
	};

#endif // VEHICLE_HPP
