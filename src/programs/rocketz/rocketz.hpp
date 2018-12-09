/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a rocket game.
*/

/*
TODO:
- Server for hosting games, accounts, statistics etc.
- Make some weapons as shields, gadgets or vehicle model features
- Make some shields as vehicle model features
- Sprites or polygons?
- Use Entity class (for animation etc.) instead of plain Sprite or Polygon2D
- Weapons, shields and gadgets for humans (diving suit, heat suit, parachutes)
- Possibility to ride on a different layer (to dodge projectiles or go behind/front of ladders instead of crashing into them)
- Difference between sabotage, EMP and virus?
- Trees, bushes etc.
- More buildings, some of them having stuff inside, some of them not
- Building animations
- Classes for scenes, set and compare variables lastscene and currentscene to do init/deinit with constructors/destructors
- Friction
- Zooming
- Mouse support
- Use MIDI controllers as joystick / game controller
- Stats during and after game (most (total and serial/massacre) kills, most suicides, most damage dealt etc.)
- Replay highlights / most impressive parts after game with fireworks effux
- Turn objects (ejection seat, bullets etc.) into land when hitting the ground
- Status flags for objects if ongoing action takes multiple screens
- Should the vehicle's or gadget's owner change immediately if stolen, or after the match?
- Give damage from all projectiles (like if an Item is falling onto Human)
*/

#ifndef ROCKETZ_HPP
	#define ROCKETZ_HPP

	#include "program.hpp"
	#include "ai.hpp"
	#include "base.hpp"
	#include "building.hpp"
	#include "bullet.hpp"
	#include "gadget.hpp"
	#include "gameplay.hpp"
	#include "human.hpp"
	#include "item.hpp"
	#include "land.hpp"
	#include "level.hpp"
	#include "player.hpp"
	#include "rain.hpp"
	#include "shield.hpp"
	#include "shop.hpp"
	#include "vehicle.hpp"
	#include "weapon.hpp"

	#include "effux_circles.hpp"
	#include "effux_textscroller.hpp"

	// SCENES:
		#define SCENE_NONE 0
		#define SCENE_TITLESCREEN 1
		#define SCENE_SETTINGS 2
		#define SCENE_GAMEPLAY 3
		#define SCENE_SELFPLAY 4
		#define SCENE_SHOP 5

	// FILE NAMES:
		#define DATAPATH "data/"

		// Fonts:
			#define FILENAME_FONT_XENOSPHERE DATAPATH "xenosphere.ttf"
			#define FILENAME_FONT_MODENINE DATAPATH "modenine.ttf"

		// Pictures:

		// Sound effects:
			#define FILENAME_SOUND_ALARM DATAPATH "alarm.wav"
			#define FILENAME_SOUND_BLACKHOLE_CREATED DATAPATH "blackholecreated.wav"
			#define FILENAME_SOUND_EXPLOSION DATAPATH "explosion.wav"
			#define FILENAME_SOUND_IMPLOSION DATAPATH "implosion.wav"
			#define FILENAME_SOUND_SHOOT DATAPATH "shoot.wav"
			#define FILENAME_SOUND_SMOKE DATAPATH "smoke.wav"
			#define FILENAME_SOUND_WORMHOLE_USED DATAPATH "wormholeused.wav"

		// Music:
			#define FILENAME_MUSIC_TITLE DATAPATH "Nuggumath-Wings-pelimusa-ReMix_CROPPED.mp3"
			#define FILENAME_MUSIC_GAMEPLAY DATAPATH "game1.xm"

	class Radar {
		// Radar / Sonar, like a mini-map
		// angle
		unsigned char rotation_speed;
		unsigned int range;
	};

	class Drone {
		// Remote controllable
	};

	class Blackhole {
		// Destroys anything going in
		int gravity = 0;	// negative numbers repel and make it white
		bool stationary;	// cannot move if true
	};

	class Wormhole {
		// Transports anything going in
		// starting_point
		// ending_point
		bool works_both_ways = true;	// TODO: gravity for one-way wormholes
		bool stationary;	// cannot move if true
	};

	//class Parameters {
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
	//};

	class Rocketz : public Program {
		protected:
			unsigned char scene = SCENE_NONE;
		public:
			TTF_Font *font_xenosphere_small;
			//TTF_Font *font_xenosphere_big;
			TTF_Font *font_xenosphere_huge;
			TTF_Font *font_modenine_small;
			Randomlevelgenerator* randomlevelgenerator;
			Rocketz();
			~Rocketz();
			bool init() override;
			bool mainloop() override;
			// FOR TITLESCREEN:
				bool init_titlescreen();
				bool deinit_titlescreen();
				//Triangle2D *rocket;
				//Polygon2D rocket;
				//Rocket *rocket;
				EffuxCircles *effux_circles = nullptr;
				EffuxTextscroller *effux_textscroller_japesoft = nullptr;
				EffuxTextscroller *effux_textscroller_poem = nullptr;
				EffuxTextscroller *effux_textscroller_credits = nullptr;
				int song_start_timestamp;	// for title screen text scroller
				void titlescreen_effux(unsigned int time);
				void titlescreen_textscroller_japesoft(unsigned int time);
				void titlescreen_textscroller_poem(unsigned int time);
				void titlescreen_textscroller_credits(unsigned int time);
				bool resize_titlescreen();
				Audio *music_title;
				SDL_Texture *texture_titlescreen = nullptr;
				SDL_Texture *texture_newgame = nullptr;
				simplesprite textbox_title;
				simplesprite textbox_newgame;
				std::string multilinetext_japesoft =
					"After more than 20 years\n"
					"Japesoft is back on the scene\n"
					"with this magnificient game called...";
				std::string multilinetext_poem =
					"Once upon a time\n"
					"there were V-shaped rockets.\n"
					"While shooting some fire\n"
					"water drained into pockets.\n"
					"\n"
					"Since then the time has passed,\n"
					"no more keyboards are smashed.\n"
					"\n"
					"Gamers' fingers\n"
					"should never linger,\n"
					"so that no lamer\n"
					"could ever win theirs.\n"
					"\n"
					"When poser new age hipsters want to try the game,\n"
					"the chosen real men in vehicles shall fight again!";
				std::string multilinetext_credits =
					"CREDITS\n"
					"\n"
					"Programming :\n"
					"JaPeK\n"
					"\n"
					"Music :\n"
					"Nuggumath\n"
					"\n"
					"Fonts :\n"
					"Darrell Flood\n"
					"Andrew Bulhak";
			// FOR GAMEPLAY:
				Gameplay *gameplay;
				bool init_gameplay();
				bool deinit_gameplay();
	};

#endif // ROCKETZ_HPP
