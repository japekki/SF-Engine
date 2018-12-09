/*
General rules of the game:
- A mixture of cave flying and real time strategy
- One player (real or computer) can control it all in a team, or certain players can control certain things, player can also be a rogue

Game modes / goals:
- Destroy enemy base
- Capture the flag
- Last man standing (alive)
- Escort hero
- Race against time or other players
- No objective, just fool around

TODO:
- Arcade style self-play demo mode with random values and computer players
*/

#ifndef GAMEPLAY_HPP
	#define GAMEPLAY_HPP

	#include "audio.hpp"
	#include "level.hpp"

	class Gameplay {
		public:
			Level *level;
			std::vector<Player> players;
			std::vector<Rogue> rogues;
			bool gameover = false;
			Audio *music_gameplay;
			void execute();
			//bool state_recording = false;
			//bool load_state();
			//bool save_state();
			Triangle2D *rocket;	// Test
	};

	class Selfplay : public Gameplay {
		// Arcade demo mode
		void init();	// Create a level, players etc.
	};

#endif // GAMEPLAY_HPP
