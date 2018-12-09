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

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_GAMEOVER DATAPATH "gameover.wav"
			#define FILENAME_SOUND_PAUSE DATAPATH "pause.wav"

		// Music:
			#define FILENAME_MUSIC_GAMEPLAY DATAPATH "game.xm"

	class Tile {
		// Can we wall, floor, water etc.
		bool can_break;
	};

	class Wall : public Tile {
		bool can_break = true;
		unsigned char treasure;
	};

	class Level {
		//unsigned char squares[][];	// 256 different tiles to construct from
	};

	class Player {
	};

	class Gameplay {
		// 1-4 players
	};

	class Cavebombers : public Program {
		public:
			Cavebombers();
			~Cavebombers();
			bool init() override;
			bool mainloop() override;
	};

#endif // CAVEBOMBERS_HPP
