/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a Minebombers style game.
*/

/*
Game modes / goals:
- Adventure (at least 1 player)
- Duel (at least 2 players)
*/

#ifndef CAVEBOMBERS_HPP
	#define CAVEBOMBERS_HPP

	#include "program.hpp"
	#include <vector>

	class Tile {
		// Can we wall, floor, water etc.
		bool can_break;
	};

	class Wall : public Tile {
		bool can_break = true;
		unsigned char treasure;
	};

	class Map {
		//unsigned char squares[][];	// 256 different tiles to construct from
	};

	class Level {
		Map map;
		void generate();	// generate random map for level
	};

	class Player {
		public:
			unsigned char lives;
			unsigned int score;
			Player();
			~Player();
	};

	class Gameplay {
		std::vector<Player*> players;	// 1-4 players
	};

	class Cavebombers : public Program {
		public:
			Cavebombers();
			~Cavebombers();
			bool init() override;
			bool mainloop() override;
	};

#endif // CAVEBOMBERS_HPP
