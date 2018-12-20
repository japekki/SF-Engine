#ifndef PLAYER_HPP
	#define PLAYER_HPP

	#define PLAYER_TYPE_CPU 0
	#define PLAYER_TYPE_HUMAN 1
	#define PLAYER_TYPE_REMOTE 2

	#include <string>
	#include <vector>
	#include "types.hpp"

	// Forward declarations:
	class Gameplay;
	class Human;
	class Vehicle;
	class Bullet;
	class Base;
	class Point;

	class Player {
		public:
			Point* location;
			std::string name;
			// SDL_Texture *avatar		// TODO
			unsigned char lives = 3;	// re-spawn at base if lives left
			unsigned char type = 0;		// computer or human
			bool remote;				// remote if controlled over network
			unsigned int money = 0;
			//Client client;			// for network game
			std::vector<Bullet*> bullets;
			Gameplay* gameplay;
			Player(Gameplay* gameplay);
			~Player();
			void add_bullet(Bullet* bullet);
			void shoot();
			void spawn();
			void move();
			Point* get_location();
			void set_location(float x, float y);
			void surrender();
			virtual void execute();
			Human* human;				// one per player
			Vehicle* vehicle;			// one per player
	};

	class Team {
		public:
			std::string name;
			unsigned int color;
			std::vector<Player*> players;
			void add_player(Player* player);
			std::vector<Base*> bases;
			void add_base(Base* base);
			void surrender();			// surrender if all players have done so
	};

#endif // PLAYER_HPP
