#ifndef VEHICLE_HPP
	#define VEHICLE_HPP

	#include "gameobject.hpp"

	// Forward declarations:
		class Base;
		class Bullet;
		class Human;
		class Player;
		class Weapon;
		class Shield;

	class Vehicle : public Gameobject {
		public:
			bool works_on_air;
			bool works_on_land;
			bool works_on_water;
			bool works_under_water;
			bool can_float;
			unsigned short max_speed = 1000;
			unsigned char acceleration = 1;
			Player *owner;
			short health;
			Human *driver;		// nullptr if nobody inside, can also be a rogue
			unsigned char max_weapons = 2;
			unsigned char max_shields = 2;
			std::vector<Weapon*> weapons;
			std::vector<Shield*> shields;
			//std::vector<Item*> items_inside;
			// TODO: brakes
			bool autopilot = false;
			bool sabotable = true;
			bool sabotaged = false;
			short temperature;	// minus if cold, plus if hot
			Vehicle();
			virtual ~Vehicle();
			void respawn(Base *base);
			void explode();
			void inc_speed(int amount);
			void dec_speed(int amount);
	};

	class Boat : public Vehicle {
		public:
			char cannon_angle;
			unsigned short cannon_power;
			Boat();
			~Boat();
	};

	class Helicopter : public Vehicle {
		public:
			// Sensitive to wind
			// Crashes if propellers are damaged
			Helicopter();
			~Helicopter();
	};

	class Rocket : public Vehicle {
		public:
			Rocket();
			~Rocket();
			void create_polygon() override;
	};

	class Submarine : public Vehicle {
		public:
			Submarine();
			~Submarine();
	};

	class Tank : public Vehicle {
		public:
			char cannon_angle;
			unsigned short cannon_power;
			Tank();
			~Tank();
	};

#endif // VEHICLE_HPP
