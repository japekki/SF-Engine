#ifndef PROGRAM_ROCKETZ_HPP
	#define PROGRAM_ROCKETZ_HPP

	#include "program.hpp"
	#include "projectile.hpp"
	#include "geom.hpp"
	#include "effux_circles.hpp"
	#include "water.hpp"

	// SCENES:
		#define SCENE_NONE 0
		#define SCENE_TITLESCREEN 1
		#define SCENE_GAMEPLAY 2

	// BACKGROUND TYPES:
		#define BACKGROUND_NONE 0
		#define BACKGROUND_BITMAP 1
		#define BACKGROUND_EFFUX 2

	// FILE NAMES:
		#define DATAPATH "../data/"
		// Pictures:
			//#define FILENAME_PIC1 DATAPATH "picture.png"
			#define FILENAME_PIC_TITLESCREEN DATAPATH "RocketZ_titlescreen.png"

		// Sounds:
			#define SOUND_EXPLOSION DATAPATH "explosion.wav"
			#define SOUND_IMPLOSION DATAPATH "implosion.wav"
			#define SOUND_BULLETHIT DATAPATH "bullethit.wav"
			#define SOUND_SHOOT DATAPATH "shoot.wav"
			#define SOUND_UKKELIDEATH DATAPATH "ukkelideath.wav"
			#define SOUND_TELEPORT DATAPATH "teleport.wav"
			#define SOUND_CRASH DATAPATH "crash.wav"
			#define SOUND_BUY DATAPATH "buy.wav"
			#define SOUND_SELL DATAPATH "sell.wav"
			#define FILENAME_MUSIC_TITLE DATAPATH "Nuggumath-Wings-pelimusa-ReMix_CROPPED.mp3"
			#define FILENAME_MUSIC_GAMEPLAY DATAPATH "PELIMUSA.S3M"	// Ripped from Wings, not included in git
			//#define FILENAME_AUDIO1 "../data/snd/audio.ogg"

		// Entities:
			//#define FILENAME_ENTITY1 DATAPATH "entity.ent"

	class Player {
		unsigned short type = 0;	// 0 = computer, 1 = human
		unsigned int money = 0;
	};

	class Soldier {
		Player *owner;	// nullptr if computer player
		short lifeforce;
	};

	class Blackhole {
		int gravity;	// negative numbers repel
	};

	class Weapon {
		unsigned short loading_time = 0;
		bool works_under_water;
		unsigned short buy_price;
		unsigned short sell_price;
		// sound
	};

	class Weapon_blackhole : public Weapon {
		// Create a black hole that alters the trajectory of projectiles
	};

	class Weapon_bouncer : public Weapon {
		// Bounces when hit (makes damage every time)
		unsigned short bounces_left = 10;
	};

	class Weapon_duster : public Weapon {
		// Create a chunk of dirt when hit
	};

	class Weapon_cannon : public Weapon {
	};

	class Weapon_cluster : public Weapon {
	};

	class Weapon_dockstation : public Weapon {
		// Drop a docking station
	};

	class Weapon_freezer : public Weapon {
	};

	class Weapon_glitcher : public Weapon {
	};

	class Weapon_grinder : public Weapon {
		// Blades rotating around the rocket, eats a hole in the ground
	};

	class Weapon_hologram : public Weapon {
		// Create a moving image of player's rocket to fool other players
	};

	class Weapon_laser : public Weapon {
		// Shoot straight line
	};

	class Weapon_mine : public Weapon {
	};

	class Weapon_minimissile : public Weapon {
	};

	class Weapon_missile : public Weapon {
	};

	class Weapon_napalm : public Weapon {
		// Drop liquid that keeps burning a while
	};

	class Weapon_rubberband : public Weapon {
	};

	class Weapon_selfdestruct : public Weapon {
		// Destroys the rocket itself with a huge explosion
		unsigned int timer;
	};

	class Weapon_smokescreen : public Weapon {
	};

	class Weapon_soldier : public Weapon {
		// Drop a human soldier that has a gun
	};

	class Weapon_station : public Weapon {
		// Drop an autonomous station that shoots with some weapon
		Weapon weapon;
	};

	class Weapon_teleport : public Weapon {
	};

	class Weapon_torch : public Weapon {
		// Shoot fire
	};

	class Weapon_torpedo : public Weapon {
		// Like missile, but under water
	};

	class Weapon_tracer : public Weapon {
		// Draws a trajectory line with no damage
		// TODO: different weapons have different trajectories
	};

	class Weapon_turbo : public Weapon {
	};

	class Weapon_watergun : public Weapon {
		// Shoot water
	};

	class Bullet : public Projectile2D {
		//Player *owner;
	};

	class Human {
		// max_speed
		Player *owner;
		short lifeforce;
		//bool inside_rocket;
		//void steal(Rocket *rocket);
		//void sabotage(Rocket *rocket);
	};

	class Enemy {
		// Human (or such) belonging to no player
	};

	class Rocket : public Polygon2D, public Projectile2D {
		// max_speed
		Player *owner;
		short lifeforce;
		Human *driver;		// nullptr if nobody inside
		Weapon primaryweapon;
		Weapon secondaryweapon;
		std::vector<Bullet> bullets;
		bool autopilot = false;
		bool sabotaged = false;
	};

	class Background {
		unsigned short type = BACKGROUND_NONE;
		SDL_Surface *bitmap;
		// TODO: pointer for effux
	};

	class Level {
		public:
			std::vector<Background> backgrounds;	// Parallax backgrounds
			std::vector<Waterpixel> water;
	};

	class Shop {
	};

	class Gameplay {
		public:
			Level *level;
			std::vector<Player> players;
			std::vector<Enemy> enemies;
			bool gameover = false;
	};

	class Rocketz : public Program {
		protected:
			unsigned char scene = SCENE_NONE;
		public:
			Rocketz();
			~Rocketz();
			bool init() override;
			Gameplay *gameplay;
			bool mainloop() override;
			EffuxCircles *effux_circles;
			// Polygons:
				//Polygon2D rocket;
				Rocket *rocket;
			// DATA:
				Audio *music_title, *music_gameplay;
				SDL_Surface *pic_titlescreen;
	};

#endif // PROGRAM_ROCKETZ_HPP
