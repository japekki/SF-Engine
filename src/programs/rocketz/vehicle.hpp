#ifndef VEHICLE_HPP
	#define VEHICLE_HPP

	#include "gamespace.hpp"

	// Forward declarations:
		class Base;
		class Bullet;
		class Human;
		class Player;
		class Weapon;
		class Shield;
		//class Shooter;

	class Vehicle : public Gameblob, public Trianglelist /*, public Shooter*/ {
		// TODO: get rid of obligatory Trianglelist
		protected:
			short fuel = 10000;
		public:
			float rotation_speed = 0.1;		// How much vehicle rotation angle changes per rotate()
			bool works_on_air = false;
			bool works_on_land = false;
			bool works_on_water = false;
			bool works_under_water = false;
			bool can_float = false;
			bool in_slowdown_mode = false;
			uint16_t weapon_power = 5;
			uint16_t max_speed = 1000;
			float acceleration = 0.023;
			Player *owner = nullptr;
			Human *driver = nullptr;		// nullptr if nobody inside, can also be a rogue
			unsigned char max_weapons = 0;
			unsigned char max_shields = 0;
			uint16_t max_items = 0;
			std::vector<Weapon*> weapons;
			std::vector<Shield*> shields;
			//std::vector<Item*> items_inside;
			virtual void toggle_slowdown();
			virtual void accelerate();
			bool sabotable = true;
			bool sabotaged = false;
			short temperature = 0;	// minus if cold, plus if hot
			//Vehicle();
			Vehicle(Gameplay* gameplay);
			~Vehicle();
			void explode();
			void move() override;
			void rotate_cw();
			void rotate_ccw();
			virtual void create_polygon();
			uint32_t get_fuel();
			void damage(float damage);
			virtual void shoot(uint8_t weapon_index);
	};

	#define DIRECTION_LEFT 0
	#define DIRECTION_UP 1
	#define DIRECTION_RIGHT 2
	#define DIRECTION_DOWN 3

	class Jetpack : public Vehicle {
		public:
			uint8_t direction;	// Left, middle or right
			Jetpack(Gameplay* gameplay);
			~Jetpack();
			void accelerate();
	};

	class Boat : public Vehicle {
		// Has integrated cannon and one weapon slot
		public:
			char cannon_angle;
			uint16_t cannon_power;
			Boat(Gameplay* gameplay);
			~Boat();
			//void move() override;
			void accelerate();
			void create_polygon() override;
	};

	class Helicopter : public Vehicle {
		public:
			// Sensitive to wind
			// Crashes if propellers are damaged
			Helicopter(Gameplay* gameplay);
			~Helicopter();
			//void move() override;
			void accelerate();
			void create_polygon() override;
	};

	class Rocket : public Vehicle {
		// TODO: Acceleration flames also act as fire weapon
		// Integrated peagun
		// one weapon slot
		// can not dive in water
		public:
			bool show_flames = false;
			Rocket(Gameplay* gameplay);
			~Rocket();
			//void move() override;
			void accelerate();
			Trianglelist *flames;
			void create_polygon() override;
			void draw();
	};

	class Rocket2 : public Vehicle {
		// Integrated peagun
		// two weapon slots
		// can dive in water
		public:
			Rocket2(Gameplay* gameplay);
			~Rocket2();
			//void move() override;
			void accelerate();
			void create_polygon() override;
	};

	class Submarine : public Vehicle {
		public:
			Submarine(Gameplay* gameplay);
			~Submarine();
			//void move() override;
			void accelerate();
			void create_polygon() override;
	};

	class Tank : public Vehicle {
		// integrated cannon only
		// TODO:
		// - Keep motor running and sound looping while fuel, different sound when driving
		// - Produce exhaust gas while motor running
			//this->gameplay->audio->play(this->gameplay->sound_motor, 0);
		public:
			char cannon_angle;
			uint16_t cannon_power;
			Tank(Gameplay* gameplay);
			~Tank();
			//void move() override;
			void accelerate();
			void create_polygon() override;
	};

	class Tank2 : public Vehicle {
		// integrated cannon
		// one weapon slot
		public:
			char cannon_angle;
			uint16_t cannon_power;
			Tank2(Gameplay* gameplay);
			~Tank2();
			//void move() override;
			void accelerate();
			void create_polygon() override;
	};

	class Drone : public Vehicle {
		// Remote controllable or with AI autopilot
	};

#endif // VEHICLE_HPP
