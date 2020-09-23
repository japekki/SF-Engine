/*
General rules of the game:
- A mixture of cave flying and real time strategy
- One player (real or computer) can control it all in a team, or certain players can control certain things, player can also be a rogue

TODO:
- Replay mode / save and load states
- Resume playing from saved state or chosen time in replay (state recording)
- Arcade style self-play demo mode with random values and computer players
- Option to show a glimpse/glance of the level when gameplay is about to start
- Option to make human player a computer player, or vice versa
- Keyboard bindings
- Grid / viewing area for each player
- Minimap
- Play sounds only if in visible range / adjust volume by distance
- Human sometimes inside vehicle/building, sometimes not, during repair
- Create explosion when vehicle or building is destroyed
- VCR: Create video file (.MP4) or still image file (.PNG) from current or old game
- "You're it" / "hippa" objective (or extra feature) with or without bullets
- Mix_VolumeChunk / Mix_VolumeMusic / ...
- Trophy ceremony between matches (gives money from things like winning the match, most damage/kills, collected money items from previous match etc.)
*/

#ifndef GAMEPLAY_HPP
	#define GAMEPLAY_HPP

	#include <SDL_ttf.h>
	#include <SDL_mixer.h>
	#include <vector>
	#include "audio.hpp"
	#include "display.hpp"
	#include "inputdevices.hpp"

	// Forward declarations:
		class Gamespace;
		class Team;
		class Player;
		class Level;
		class Item;

	// GAME MODES / GOALS:
		#define GAMEPLAYMODE_NONE 0			// No objective, just fool around
		#define GAMEPLAYMODE_EXHIBIT 1		// No objective, just fool around
		#define GAMEPLAYMODE_BASE 2			// Destroy enemy base
		#define GAMEPLAYMODE_CTF 3			// Capture the flag
		#define GAMEPLAYMODE_LMS 4			// Last man standing (alive)
		#define GAMEPLAYMODE_ESCORT 5		// Escort
		#define GAMEPLAYMODE_RACE 6			// Race against time or other players

	// CONTROL MODES:
		#define CONTROLMODE_PLAY 0			// Normal play
		#define CONTROLMODE_TEXTINPUT 1		// Receive text input to widget

	// State for regular savegame from one time position
	// Statevideo for video replay or retry game from any time position

	class Parameters {
		/*
		Adjustable gameplay/level parameters (defaults are saved in level file and user favorite file):
		- Fuel limits
		- Weapon loading time
		- Amount of water rain
		- Amount of snow rain
		- Amount of land rain
		- Amount of lava rain
		- Amount of bomb rain
		- Amount of item rain
		- Amount of light
		- Item spawn rate
		- Team members can damage each other (on/off)
		- Enable or disable certain weapons, shields, gadgets, vehicles etc.
		- Amount of rogues
		- Amount of sharks
		- Amount of clouds (in background or in front layer (ships can hide behind/inside clouds))
		- Planet gravity level
		- General gravity multiplier
		- If gravity calculations go far beyond processing power, make a simplified gravity option
		*/
	};

	struct state_team {
		std::string name;
		std::vector<uint8_t> player_id;
		uint32_t color;
	};

	struct state_player {
		std::vector<uint8_t> player_id;
		uint32_t color;
	};

	class State {
		public:
			// gather all parameters into vector
			//std::vector<Parameter> game_parameters;
			uint32_t timeindex = 0;			// TODO: as in time or as in framecount
			std::vector<state_player> players;
			std::vector<state_team> teams;
			uint32_t get_datasize();
			//bool load(const char* filename);
			//bool save();
	};

	#define STATE_IDLE 0
	#define STATE_RECORDING 1
	#define STATE_PLAYING 2

	struct statevideo_chunk {
		uint32_t framecount;
		uint32_t datasize;
	};

	class Statevideo {
		// For replays (and maybe for game server)
		public:
			bool state = STATE_IDLE;
			std::vector<State*> states;
			std::vector<statevideo_chunk> index;
			Statevideo();
			~Statevideo();
			uint32_t get_datasize();
			void record_state(State* state);	// Record a state
			void play();						// Play states
			void stop();						// Stop recording or playing
			bool load(const char* filename);	// Load replay from file
			bool save(const char* filename);	// Save replay to file
			bool set_position();
			bool seek_frames(int frames);
			bool seek_time(int time);
			State* next();
			State* previous();
	};

	#define GAME_TYPE_NONE 0
	#define GAME_TYPE_SINGLEMATCH 1
	#define GAME_TYPE_MULTIROUND 2

	class Round {
		uint8_t type = GAME_TYPE_NONE;
		Team* winner_team = nullptr;
		Player* winner_player = nullptr;
	};

	class Game {
		public:
			uint8_t type = GAME_TYPE_NONE;	// type is used as default value for new rounds
			std::vector<Round> rounds;
			// TODO: Player stats
			Team* leading_team = nullptr;
			Player* leading_player = nullptr;
			Team* winner_team = nullptr;
			Player* winner_player = nullptr;
	};

	class Gameplay {
		public:
			Game game;
			Display* display = nullptr;
			Audio* audio = nullptr;
			Jukebox* jukebox = nullptr;
			Keyboard* keyboard = nullptr;
			Mouse* mouse = nullptr;
			Joystick* joystick = nullptr;
			bool play_sound = true;
			bool play_music = true;
			Uint8 volume_sfx = 64;		// max = 128
			//Uint8 volume_music;
			//SDL_Texture* textwindow = nullptr;
			bool demoplay = false;
			Grapher minimap;
			Simplesprite* texture_gameover = nullptr;
			Simplesprite* texture_pause = nullptr;
			std::vector<Grapher*> playerwindows;
			unsigned char goal_type = GAMEPLAYMODE_NONE;
			bool view_info = false;
			bool view_help = false;
			bool gameover = false;		// Set to true when objective reached
			uint8_t delay_gameover = 255;
			uint32_t expiretime = 0;
			Level *level = nullptr;
			Gamespace* gamespace = nullptr;
			Statevideo* statevideo = nullptr;
			std::vector<Team*> teams;
			std::vector<Item*> items;
			Player* highlighted_player = nullptr;
			//void add_team(Team* team);
			void add_item(Item* item);
			void delete_expired();
			void spawn_items();
			//std::vector<Rogue*> rogues;

			// Widgets:
				//Input_text *test_widget;

			// FONTS:
				TTF_Font *font_glasstty_tiny = nullptr;
				TTF_Font *font_glasstty_small = nullptr;
				TTF_Font *font_glasstty_big = nullptr;

			// Sounds:
				Mix_Chunk *sound_hit = nullptr;
				Mix_Chunk *sound_scream = nullptr;
				Mix_Chunk *sound_shoot = nullptr;
				Mix_Chunk *sound_radialgun = nullptr;
				Mix_Chunk *sound_explosion = nullptr;
				Mix_Chunk *sound_watergun = nullptr;
				//Mix_Chunk *sound_building_explode = nullptr;

			// Sound triggers:
				bool play_hit = false;
				bool play_scream = false;
				bool play_shoot = false;
				bool play_radialgun = false;
				bool play_explosion = false;
				bool play_watergun = false;

			Gameplay(Display* display, Audio* audio, Jukebox* jukebox, Keyboard* keyboard, Mouse* mouse, Joystick* joystick);
			~Gameplay();
			void set_volume_sfx(Uint8 volume);
			void create_random_computers(int players, int teams);
			void setup_demoplay();
			void setup_gameplay();
			void create_debree();
			void set_grid();
			void resize();
			bool execute();		// Returns false when everything in gameplay is done (including gameover text delay)
			State* get_state();
			bool retry_from_frame(int framenumber);
			SDL_Texture* texture_help = nullptr;
			const std::string helptext =
				"KEYS:\n"
				" \n"
				"Global:\n"
				"  F1              = gameplay\n"
				"  F2              = demoplay\n"
				"  F5              = title screen\n"
				"  F11             = fullscreen toggle (change resolution)\n"
				"  F12             = fullsreen toggle (keep desktop resolution)\n"
				"  H               = help\n"
				"  P, Pause        = toggle pause\n"
				"  PrintScreen     = save screenshot\n"
				" \n"
				"Gameplay & Demoplay:\n"
				"  PageUp          = next tune\n"
				"  PageDown        = previous tune\n"
				"  Home            = first tune\n"
				"  End             = last tune\n"
				"  Insert          = restart current tune\n"
				"  Delete          = random tune\n"
				"  Numpad +        = zoom in\n"
				"  Numpad -        = zoom out\n"
				"  Tab             = toggle info/stats/grid\n"
				"  M               = toggle music on/off\n"
				"  S               = toggle sound on/off\n"
				"  Esc             = game over (or skip delay during game over text)\n"
				" \n"
				"Gameplay:\n"
				"  Left             = rotate vehicle counter clockwise, move human left\n"
				"  Right            = rotate vehicle clockwise, move human right\n"
				"  Ctrl, Shift, Alt = shoot weapon 0\n"
				"  1..0             = shoot weapon 1..10\n"
				"  Enter            = human get in/out vehicle\n"
				"  Space            = toggle vehicle slowdown mode, human jump";
	};

#endif // GAMEPLAY_HPP
