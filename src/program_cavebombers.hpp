/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a Minebombers style game.
*/

#ifndef PROGRAM_CAVEBOMBERS_HPP
	#define PROGRAM_CAVEBOMBERS_HPP

	#include "program.hpp"

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sounds:
			#define FILENAME_SOUND_GAMEOVER DATAPATH "gameover.wav"
			#define FILENAME_SOUND_PAUSE DATAPATH "pause.wav"

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

#endif // PROGRAM_CAVEBOMBERS_HPP
