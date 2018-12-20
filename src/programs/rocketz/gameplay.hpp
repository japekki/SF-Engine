/*
General rules of the game:
- A mixture of cave flying and real time strategy
- One player (real or computer) can control it all in a team, or certain players can control certain things, player can also be a rogue

TODO:
- Arcade style self-play demo mode with random values and computer players
- Option to show a glimpse/glance of the level when gameplay is about to start
- Option to make human player a computer player, or vice versa
- Keyboard binging
- Player's position if human or vehicle
- Grid / viewing area for each player
*/

#ifndef GAMEPLAY_HPP
	#define GAMEPLAY_HPP

	#include <SDL_mixer.h>
	#include <vector>

	class Display;
	class Audio;
	class Gameobject;
	class Keyboard;
	class Mouse;
	class Team;
	class Level;

	// GAME MODES / GOALS:
		#define GAMEPLAYMODE_NONE 0			// No objective, just fool around
		#define GAMEPLAYMODE_BASE 1			// Destroy enemy base
		#define GAMEPLAYMODE_CTF 2			// Capture the flag
		#define GAMEPLAYMODE_LMS 3			// Last man standing (alive)
		#define GAMEPLAYMODE_ESCORT 4		// Escort
		#define GAMEPLAYMODE_RACE 5			// Race against time or other players

	class Gameplay {
		public:
			Display *display;
			Audio *audio;
			Keyboard *keyboard;
			Mouse *mouse;
			unsigned char goal_type = GAMEPLAYMODE_NONE;
			Level *level;
			std::vector<Gameobject*> gameobjects;
			std::vector<Team*> teams;
			//std::vector<Rogue*> rogues;
			bool gameover = false;

			// Sounds:
				Mix_Chunk *sound_shoot = nullptr;
				Mix_Chunk *sound_building_explode = nullptr;

			Gameplay(Display *display, Audio *audio, Keyboard *keyboard, Mouse *mouse);
			~Gameplay();
			void init();
			void execute();
			bool recording = false;
			bool load_state();
			bool save_state();
	};

	class Selfplay : public Gameplay {
		// Arcade demo mode
		void init();	// Create a level, players etc.
	};

#endif // GAMEPLAY_HPP
