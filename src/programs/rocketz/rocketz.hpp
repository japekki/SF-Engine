/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a rocket game,
	similar to Auts, Wings, Kops, Rocket Chase, Turboraketti, V-Wing etc.
*/

/*
TODO:
- Server for hosting games, accounts, statistics etc.
- Save state in server so it can be continued (if networks breaks, or if users want to play again from some point of previous game)
- Make some weapons as shields, gadgets or vehicle model features
- Make some shields as vehicle model features
- Sprites or polygons?
- Timed states for blobs (for things happening during many frames)
- Weapons, shields and gadgets for humans (diving suit, heat suit, parachutes)
- Possibility to ride on a different layer (to dodge projectiles or go behind/front of ladders instead of crashing into them)
- Difference between sabotage, EMP and virus?
- Trees, bushes etc.
- Smoking vehicles, gadgets and buildings when low health
- Burning grounds, vehicles, gadgets and building, burning causes damage, put out fire with water, freezer, snow etc.
- Flammability / burning sensitivity
- Gas (from pipes etc.) (makes damage to humans)
- More buildings, some of them having stuff inside, some of them not
- Building animations
- Classes for scenes, set and compare variables previous_scene and currentscene to do init/deinit with constructors/destructors
- Friction (like vehicle sliding on ice / stone)
- Mouse support
- Use MIDI controllers as joystick / game controller
- Stats during and after game (most (total and serial/massacre) kills, most suicides, most damage dealt etc.)
- Replay highlights / most impressive parts after game with fireworks effux
- Turn objects (ejection seat, bullets etc.) into land when hitting the ground
- Action/animations over multiple screens
- Give damage from all projectiles (like if an Item is falling onto Human)
- Spectator mode
- Heat conduction / temperature balancing (between objects and/or land)
- Space debris
- Folder for user defined music files
*/

/*
Game widgets:
	- System notifications ("song changed to X" etc.)
	- Gameplay messages ("team X demolished" etc.)
*/

#ifndef ROCKETZ_HPP
	#define ROCKETZ_HPP

	#include <SDL_mixer.h>
	#include <SDL_ttf.h>
	#include "filenames.hpp"
	#include "audio.hpp"
	#include "program.hpp"
	#include "gamespace.hpp"

	// Forward declarations:
		class Simplesprite;
		class EffuxTextscroller;
		class EffuxCircles;
		class Gameplay;
		class Shop;

	// SCENES:
		#define SCENE_NONE 0
		#define SCENE_PAUSE 1
		#define SCENE_TITLESCREEN 2
		#define SCENE_SETTINGS 3
		#define SCENE_GAMEPLAY 4
		#define SCENE_DEMOPLAY 5
		#define SCENE_SHOP 6
		#define SCENE_REPLAY 7

	// TIMESTAMPS:
		#define TIMESTAMP_JAPEKSLAB		0		// ~0:00
		#define TIMESTAMP_CIRCLES1		15400	// ~0:15
		#define TIMESTAMP_TEXT			46000	// ~0:46
		#define TIMESTAMP_CIRCLES2		61400	// ~1:01
		#define TIMESTAMP_CREDITS		92000	// ~1:32
		#define TIMESTAMP_CIRCLES3		107500	// ~1:47
		#define TIMESTAMP_FADEOUT		165000
		#define TIMESTAMP_END			167500	// ~2:47
		#define TIMESTAMP_DEMOPLAY_END	300000

	class Rocketz : public Program {
		protected:
			unsigned char scene = SCENE_NONE;
			unsigned char previous_scene = SCENE_NONE;		// Where to return from pause or other scenes
		public:

			// FONTS:
				TTF_Font *font_xenosphere_small = nullptr;
				TTF_Font *font_xenosphere_huge = nullptr;
				TTF_Font *font_modenine_small = nullptr;
				TTF_Font *font_glasstty_big = nullptr;
				//TTF_Font *font_xenosphere_big = nullptr;
				//TTF_Font *font_modenine_tiny = nullptr;

			Rocketz(int argc, char** argv);
			~Rocketz();
			bool init() override;
			void reset();
			bool mainloop() override;

			// FOR TITLESCREEN:
				bool init_titlescreen();
				bool deinit_titlescreen();
				EffuxCircles *effux_circles = nullptr;
				EffuxTextscroller *effux_textscroller_japekslab = nullptr;
				EffuxTextscroller *effux_textscroller_poem = nullptr;
				EffuxTextscroller *effux_textscroller_credits = nullptr;
				int song_start_timestamp = 0;	// for title screen text scroller
				void titlescreen_textscroller_japekslab(uint32_t time);
				void titlescreen_textscroller_poem(uint32_t time);
				void titlescreen_textscroller_credits(uint32_t time);
				bool resize_titlescreen();
				Mix_Music *music_title = nullptr;
				SDL_Texture *texture_alphacircle = nullptr;
				SDL_Texture *texture_newgame = nullptr;
				Simplesprite* textbox_title = nullptr;
				Simplesprite* textbox_newgame = nullptr;
				const std::string multilinetext_japekslab =
					"JaPeK's Lab_ presents...";			// TODO: Font change, blinking cursor
				const std::string multilinetext_poem =
					"Once upon a time\n"
					"there were V-shaped rockets.\n"
					"While shooting some fire\n"
					"water drained into pockets.\n"
					" \n"
					"Since then the time has passed,\n"
					"no more keyboards are smashed.\n"
					" \n"
					"Gamers' fingers\n"
					"should never linger,\n"
					"so that no lamer\n"
					"could ever win theirs.";
				const std::string multilinetext_credits =
					"Programming :\n"
					"JaPeK\n"
					" \n"
					"Fonts :\n"
					"Andrew Bulhak\n"
					"Darrell Flood\n"
					"Graham H Freeman\n"
					" \n"
					"Music :\n"
					"Nuggumath\n"
					" \n"
					"Sound effects :\n"
					"Daniel Simion\n"
					"Mike Koenig\n"
					" \n"
					"http://japekslab.com/rocketz/";
				const std::string menutext =
					" F1 = New game\n"
					" F2 = Demo play\n"
					" F5 = Reset\n"
					//" F8 = Settings\n"
					"F11 = Fullscreen 1\n"
					"F12 = Fullscreen 2\n"
					"Esc = Exit";

			// FOR GAMEPLAY:
				Gameplay *gameplay;
				Shop* shop;
				Jukebox* jukebox = nullptr;
				std::string filepath_music = FILEPATH_MUSIC;
	};

#endif // ROCKETZ_HPP
