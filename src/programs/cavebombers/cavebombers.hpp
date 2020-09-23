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
		// Can be wall, floor, water etc.
		bool can_break = true;
	};

	class Wall : public Tile {
		unsigned char treasure;
	};

	class Map {
		//unsigned char squares[][];	// 256 different tiles to construct from
	};

	class Level {
		public:
			uint16_t width = 0;
			uint16_t height = 0;
			Map map;
			void generate();	// generate random map for level
	};

	class Weapon {
	};

	class Item {
	};

	class Treasure : public Item {
	};

	class Trap {
	};

	class Player {
		public:
			unsigned char lives;
			uint32_t score;
			Player();
			~Player();
	};

	class Computerplayer : public Player {
		public:
			void execute();
	};

	class Gameplay {
		Level* level;
		std::vector<Player> players;	// 1-4 players
		void init();
	};

	class Cavebombers : public Program {
		public:
			Cavebombers(int argc, char** argv);
			~Cavebombers();
			Level level;
			bool init() override;
			bool mainloop() override;
	};

#endif // CAVEBOMBERS_HPP
