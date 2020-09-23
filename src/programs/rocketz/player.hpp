#ifndef PLAYER_HPP
	#define PLAYER_HPP

	#include <string>
	#include <vector>

	#define PLAYER_TYPE_CPU 0
	#define PLAYER_TYPE_HUMAN 1
	#define PLAYER_TYPE_REMOTE 2	// Netplayer

	// Forward declarations:
		class Team;
		class Gameplay;
		class Human;
		class Vehicle;
		class Bullet;
		class Base;
		class Point;
		class Joystick;

	class Player {
		public:
			// TODO: display window for each player:
				//SDL_Rect viewarea;
				//Grapher* display_window;
			uint32_t color;
			std::string name;
			// SDL_Texture *avatar		// TODO
			unsigned char lives = 3;	// re-spawn at base if lives left
			unsigned char type = 0;		// computer or human
			bool remote;				// remote if controlled over network
			uint32_t money = 0;
			Gameplay* gameplay;
			Team* team;
			Player(Gameplay* gameplay);
			virtual ~Player();
			void set_color(uint32_t color);
			float get_health();
			float get_speed();
			void shoot(uint8_t weaponindex);
			void spawn();
			void spawn(Base* base);
			void move();
			Point get_location();
			Base* nearest_homebase();	// nearest base of own team
			void set_location(float x, float y);
			void set_location(Point location);
			void surrender();
			virtual void execute();
			Human* human = nullptr;				// one per player
			Vehicle* vehicle = nullptr;			// one per player
			Joystick* joystick = nullptr;
			// Joystick button bindings:
				int8_t joybut_shoot = -1;
				int8_t joybut_shoot_active = -1;
				int8_t joybut_cycle_active = -1;
				int8_t joybut_zoomin = -1;
				int8_t joybut_zoomout = -1;
				int8_t joybut_slowdown = -1;
				int8_t joybut_jump = -1;
				int8_t joybut_eject = -1;
				int8_t joybut_thrust = -1;
				std::vector<uint8_t> joybut_weapons;
			void set_joystick(Joystick* joystick);
	};

	class Team {
		public:
			std::string name;
			uint32_t color;
			std::vector<Player*> players;
			void add_player(Player* player);
			std::vector<Base*> bases;
			void add_base(Base* base);
			void surrender();			// surrender if all players have done so
			bool has_human_alive();
			Team();
			Team(std::string name);
			~Team();
	};

#endif // PLAYER_HPP
