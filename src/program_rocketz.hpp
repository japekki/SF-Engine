#ifndef PROGRAM_ROCKETZ_HPP
	#define PROGRAM_ROCKETZ_HPP

	#include "program.hpp"
	#include "projectile.hpp"
	#include "geom.hpp"
	#include "effux_circles.hpp"
	#include "effux_sky.hpp"
	#include "smoke.hpp"
	#include "water.hpp"

	// SCENES:
		#define SCENE_NONE 0
		#define SCENE_TITLESCREEN 1
		#define SCENE_GAMEPLAY 2
		#define SCENE_SHOP 3

	// LAYER TYPES:
		#define LAYER_NONE 0
		#define LAYER_COLOR 1
		#define LAYER_BITMAP 2
		#define LAYER_EFFUX 3

	// FILE NAMES:
		#define DATAPATH "data/"
		// Pictures:
			#define FILENAME_PIC_TITLESCREEN DATAPATH "RocketZ_titlescreen.png"

		// Sound effects:
			#define FILENAME_SOUND_JETENGINE DATAPATH "jetengine.wav"
			#define FILENAME_SOUND_DIESELMOTOR DATAPATH "dieselmotor.wav"
			#define FILENAME_SOUND_EXPLOSION DATAPATH "explosion.wav"
			#define FILENAME_SOUND_IMPLOSION DATAPATH "implosion.wav"
			#define FILENAME_SOUND_BULLETHIT DATAPATH "bullethit.wav"
			#define FILENAME_SOUND_SHOOT DATAPATH "shoot.wav"
			#define FILENAME_SOUND_HUMANDEATH DATAPATH "humandeath.wav"
			#define FILENAME_SOUND_TELEPORT DATAPATH "teleport.wav"
			#define FILENAME_SOUND_CRASH DATAPATH "crash.wav"
			#define FILENAME_SOUND_BUY DATAPATH "buy.wav"
			#define FILENAME_SOUND_SELL DATAPATH "sell.wav"
			#define FILENAME_SOUND_BLACKHOLE_CREATED DATAPATH "blackholecreated.wav"
			#define FILENAME_SOUND_BLACKHOLE_USED DATAPATH "blackholeused.wav"
			#define FILENAME_SOUND_SELFDESTRUCT_INIT DATAPATH "selfdestructinit.wav"
			#define FILENAME_SOUND_ABSORB DATAPATH "absorb.wav"
			#define FILENAME_SOUND_BOUNCE DATAPATH "bouce.wav"
			#define FILENAME_SOUND_ELECTRO DATAPATH "electro.wav"
			#define FILENAME_SOUND_FREEZER DATAPATH "freezer.wav"
			#define FILENAME_SOUND_EMP DATAPATH "emp.wav"
			#define FILENAME_SOUND_GRIND DATAPATH "grind.wav"
			#define FILENAME_SOUND_HOLOGRAM DATAPATH "hologram.wav"
			#define FILENAME_SOUND_LIFESTEAL DATAPATH "lifesteal.wav"
			#define FILENAME_SOUND_MINIMISSILE DATAPATH "minimissile.wav"
			#define FILENAME_SOUND_MOEBIUS DATAPATH "moebius.wav"
			#define FILENAME_SOUND_PAINT DATAPATH "paint.wav"
			#define FILENAME_SOUND_PHASE DATAPATH "phase.wav"
			#define FILENAME_SOUND_SIZER DATAPATH "sizer.wav
			#define FILENAME_SOUND_SMOKE DATAPATH "smoke.wav"
			#define FILENAME_SOUND_TRACTORBEAM DATAPATH "tractorbeam.wav"
			#define FILENAME_SOUND_ALARM DATAPATH "alarm.wav"
			#define FILENAME_SOUND_BASEATTACK DATAPATH "baseattack.wav"

		// Music:
			#define FILENAME_MUSIC_TITLE DATAPATH "Nuggumath-Wings-pelimusa-ReMix_CROPPED.mp3"
			#define FILENAME_MUSIC_GAMEPLAY DATAPATH "PELIMUSA.S3M"	// Ripped from Wings, not included in git

	// General rules of the game:
	// - A mixture of cave flying and real time strategy
	// - One player (real or computer) can control it all in a team, or certain players can control certain things, player can also be a rogue

	// Game modes:
	// - Capture the flag
	// - Destroy enemy base
	// - Escort hero

	// TODO:
	// - Make some weapons as shields, gadgets or vehicle model features
	// - Level editor
	// - Random level generator
	// - Level file format
	// - Sprites or polygons?
	// - Use Entity class (for animation etc.) instead of plain Sprite or Polygon2D
	// - Weapons, shields and gadgets for humans (diving suit, heat suit, parachutes)
	// - If volcanoes, lava etc. are on a background layer, they're not dangerous
	// - Possibility to ride on a different layer
	// - Difference between sabotage, emp and virus?

	// Adjustable gameplay/level parameters (defaults are saved in level file and user favorite file):
	// - Fuel limits (or off)
	// - Weapon loading time
	// - Amount of water rain
	// - Amount of snow rain
	// - Amount of land rain
	// - Amount of lava rain
	// - Amount of bomb rain
	// - Amount of item rain
	// - Amount of light
	// - Item spawn rate
	// - Team members can damage each other (on/off)
	// - Enable or disable certain weapons, shields, gadgets, vehicles etc.
	// - Amount of rogues
	// - Amount of sharks
	// - Amount of clouds (in background or in front layer (ships can hide behind/inside clouds))
	// - Planet gravity level
	// - General gravity multiplier
	// - If gravity calculations go far beyond processing power, make a simplified gravity option

	class Gadget : public Polygon2D, public Projectile2D {
		// To be planted, not collectible, can be moved with tractor beam etc.
		// TODO: think this over
		bool works_under_water;
		bool sabotable;
		bool sabotaged;
	};

	class Gadget_torch : public Gadget {
		// Creates light, like a torch or candle
	};

	class Gadget_pump : public Gadget {
		// Pumps water, connects to hose
	};

	class Gadget_hose : public Gadget {
		// Water goes trough this, connects to hose
	};

	class Gadget_tunnel : public Gadget {
		// Pipe or tunnel, humans and vehicles can go trough this, water can flow trough this
	};

	class Item {
		// Collectible items by humans, not by vehicles.
		// Items are used immediately when touching with human, or collected to base when carried by hoarders.
		// Usually some sort of power-ups.
		// Can be transported with tractor beam, or crushed by tank or blasted by weapon.
	};

	class Item_medkit : public Item {
		// Heals a human
		unsigned int health;
	};

	class Item_extralife : public Item {
	};

	class Item_money : public Item {
		unsigned short amount;
	};

	class Radar {
		// Radar / Sonar, like a mini-map
		// angle
		unsigned char rotation_speed;
		unsigned int range;
	};

	class Drone {
		// Remote controllable
	};

	class Building {
		// Stationary, does not move
	};

	class Base : public Building {
		// Player's base
	};

	class Player {
		std::string name;
		unsigned char type = 0;	// computer or human
		bool remote;	// remote if controlled over network
		unsigned int money = 0;
		//Client client;	// for network game
	};

	class Human {
		// max_speed
		Player *owner;
		short lifeforce;
		unsigned char parachutes;	// Don't get hit if dropping down to ground
		bool parachute_burning = false;
		short temperature;	// minus for cold, plus for hot
		unsigned short air_left;	// TODO: infinite
		short ammo;	// TODO: infinite
		//bool inside_rocket;
		//void steal(Rocket *rocket);
		//void sabotage(Vehicle *vehicle);	// TODO: sabotage gadgets
		//void plant_virus(Vehicle *vehicle);	// TODO: same as sabotage?
	};

	class Hoarder : public Human {
		// Human that hoards items on the field and take them to base, or vice versa
		std::vector<Item> items;
	};

	class Soldier : public Human {
		Player *owner;	// nullptr if rogue
		short lifeforce;
	};

	class Guardian : public Human {
		// Doesn't move a lot, sticks to a single place or patrols a certain area
		// Can stand for example on the entrance of a tunnel or base
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

	class Shield {
		// Always on, unlike Weapon
		unsigned int condition;	// 0 if worn out
		bool works_under_water;
		unsigned char level;	// How powerful the weapon is
		unsigned short buy_price;
		unsigned short sell_price;
		//Polygon2D picture;	// Or Sprite - shows up in shop and menus
	};

	class Shield_emp {
		// Protect from EMP
	};

	class Shield_lightscreen : public Shield {
		// Allows to see in bright ligh, protects from blindness caused by flashes
	};

	class Shield_mirror : public Shield {
		// Reflects laser away
	};

	class Shield_inertialdamper : public Shield {
		// Keep trajectory still at collision, recoil or when being blasted at
		// Doesn't work with gravity or tractor beam
	};

	class Weapon {
		// Has to be triggered, unlike Shield
		unsigned short loading_time = 0;
		bool works_under_water;
		unsigned char level;	// How powerful the weapon is
		unsigned short buy_price;
		unsigned short sell_price;
		std::string name;
		std::string description;
		short recoil;	// if negative, the weapon pulls the vehicle forwards when shooting (depending of course where the weapon is located in the vehicle)
		//Polygon2D picture;	// Or Sprite - shows up in shop and menus
		// sound
	};

	class Weapon_absorber : public Weapon {
		// Absorb energy from blasts
	};

	class Weapon_anchor : public Weapon {
		// Deploy (or shoot) an achor/pendulum that has high mass and sticks to ground
		// Attaches to vehicle
	};

	class Weapon_blackhole : public Weapon {
		// Create a black hole that alters the trajectory of projectiles
	};

	class Weapon_bouncer : public Weapon {
		// Bounces when hit (makes damage every time)
		unsigned short bounces_left = 10;
	};

	class Weapon_bubblegum : public Weapon {
		// Create sticky goo
	};

	class Weapon_duster : public Weapon {
		// Create a chunk of dirt when hit
	};

	class Weapon_cannon : public Weapon {
	};

	class Weapon_cluster : public Weapon {
	};

	class Weapon_darkgrenade : public Weapon {
		// Like flash grenade, but makes darkness
	};

	class Weapon_disguise : public Weapon {
		// Appear to be different rocket model or color
	};

	class Weapon_dockstation : public Weapon {
		// Drop a docking station
	};

	class Weapon_electro : public Weapon {
	};

	class Weapon_flashgrenade : public Weapon {
		// Fast flash of light, causes temporary blindness/darkness afterwards
	};

	class Weapon_freezer : public Weapon {
	};

	class Weapon_emp : public Weapon {
		// Make electronics (vehicles and gadgets) to shut down or malfunction for a while
	};

	class Weapon_gravity : public Weapon {
		// Cancel or alter gravity (push or pull)
	};

	class Weapon_grenade : public Weapon {
		unsigned short timer;
	};

	class Weapon_grinder : public Weapon {
		// Blades rotating around the rocket, eats a hole in the ground
	};

	class Weapon_hologram : public Weapon {
		// Create a moving image of player's rocket to fool other players
	};

	class Weapon_invisibility : public Weapon {
	};

	class Weapon_jammer : public Weapon {
		// Make nearby weapons, radio or remote controllers unusable
	};

	class Weapon_laser : public Weapon {
		// Shoot straight thin line of burning light
	};

	class Weapon_lifestealer : public Weapon {
	};

	class Weapon_mine : public Weapon {
		// Leaves a mine behind that explodes if something touches it (or there's a blast near it)
	};

	class Weapon_minimissile : public Weapon {
		// Like missile, but many little missiles launched fast
	};

	class Weapon_missile : public Weapon {
		// Follows / targets to objects
	};

	class Weapon_moebius : public Weapon {
		// Warp from one level edge to the opposite, or go to the "other side" of the 2D world
	};

	class Weapon_napalm : public Weapon {
		// Drop liquid that keeps burning a while
	};

	class Weapon_painter : public Weapon {
		// Recolor things, like ground, buildings or rockets
	};

	class Weapon_phaser : public Weapon {
		// Go trough solid matter
		// Instant death if re-appear inside matter
	};

	class Weapon_radialgun : public Weapon {
		// Shoot to many directions at once, as a circle of bullets
	};

	class Weapon_radiationbomb : public Weapon {
		// Generate invisible radiation that makes more damage the closer someone gets to it
	};

	class Weapon_random : public Weapon {
		// Random weapon each time when shooting
	};

	class Weapon_rubberband : public Weapon {
		// Shoot a stretchy harpoon
		// Second shoot releases the end part
		// Both endpoint stick to ground and vehicles
	};

	class Weapon_selfdestruct : public Weapon {
		// Destroys the vehicle itself with a huge explosion
		unsigned int timer;
	};

	class Weapon_sizer : public Weapon {
		// Change size
	};

	class Weapon_smokegrenade : public Weapon {
		// Throw a grenade that creates smoke
	};

	class Weapon_smokescreen : public Weapon {
		// Create smoke around the vehicle
	};

	class Weapon_spraygun : public Weapon {
		// A bit like shotgun in other games
	};

	class Weapon_spycam : public Weapon {
	};

	class Weapon_soldier : public Weapon {
		// Drop a human soldier that has a gun
	};

	class Weapon_station : public Weapon {
		// Drop an autonomous station that shoots with some weapon
		Weapon weapon;
	};

	class Weapon_stinger : public Weapon {
		// Sword-like sharp spike
	};

	class Weapon_teleport : public Weapon {
	};

	class Weapon_termite : public Weapon {
		// Sticky
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

	class Weapon_tractorbeam : public Weapon {
		// Pull stuff or lock into relative position/location
		// For example, a rocket can move a ship with this
	};

	class Weapon_turbo : public Weapon {
		// Increased speed and acceleration for a while
	};

	class Weapon_watergun : public Weapon {
		// Shoot water
	};

	class Weapon_wormhole : public Weapon {
		// Create a wormhole
	};

	class Bullet : public Projectile2D {
		//Player *owner;
	};

	class Rogue {
		// Human or vehicle not belonging to any player (or team)
	};

	class Anchor : public Gadget {
	};

	class Vehicle : public Polygon2D, public Projectile2D {
		// max_speed
		Player *owner;
		short lifeforce;
		Human *driver;		// nullptr if nobody inside, can also be a rogue
		unsigned char weapon_slots;
		Weapon primaryweapon;
		Weapon secondaryweapon;
		std::vector<Bullet> bullets;
		unsigned short max_speed;
		unsigned char acceleration;
		// TODO: brakes
		bool autopilot = false;
		bool sabotaged = false;
		short temperature;	// minus if cold, plus if hot
	};

	class Submarine : public Vehicle {
		bool works_on_air = false;
		bool works_on_land = false;
		bool works_on_water = true;
		bool works_under_water = true;
		bool can_float = true;
	};

	class Boat : public Vehicle {
		bool works_on_air = false;
		bool works_on_land = false;
		bool works_on_water = true;
		bool works_under_water = false;
		bool can_float = true;
		char cannon_angle;
		unsigned short cannon_power;
	};

	class Tank : public Vehicle {
		bool works_on_air = false;
		bool works_on_land = true;
		bool works_on_water = false;
		bool works_under_water = false;
		bool can_float = false;
		char cannon_angle;
		unsigned short cannon_power;
	};

	class Rocket : public Vehicle {
		bool works_on_air = true;
		bool works_on_land = false;
		bool works_on_water = true;
		bool works_under_water = false;	// advanced models can go under water
		bool can_float = true;
	};

	class Background {
		unsigned short type = LAYER_NONE;
		//SDL_Surface *bitmap;
		// TODO: pointer for effux
	};

	class Land {
		// bool soft, sticky, slippery, burning, freezing
		// bool flammable, meltable, steamable/vaporable, smokable (???)
		// If land is soft, it makes damage on impact and leaves a hole when blasted
		// If land is hard, it doesn't make damage on impact and falls straight down without leaving a hole when blasted
		short temperature;	// minus if cold, plus if hot
	};

	class Ice : public Land {
		bool soft = false;
		bool sticky = false;
		bool slippery = true;
		bool burning = false;
		bool freezing = true;
	};

	class Bubblegum : public Land {
		bool soft = true;
		bool sticky = true;
		bool slippery = false;
		bool burning = false;
		bool freezing = false;
	};

	class Water : public Land {
		bool soft = true;
		bool sticky = false;
		bool slippery = true;
		bool burning = false;
		bool freezing = false;
	};

	class Oil : public Water {
		bool soft = true;
		bool sticky = false;
		bool slippery = true;
		bool burning = true;
		bool freezing = false;
	};

	class Lava : public Water {
		bool soft = true;
		bool sticky = false;
		bool slippery = false;
		bool burning = true;
		bool freezing = false;
	};

	class Napalm : public Water {
		bool soft = true;
		bool sticky = true;
		bool slippery = false;
		bool burning = true;
		bool freezing = false;
	};

	class Wind {
		short speed;	// minus winds to the left, plus winds to the right
	};

	class Rain {
		unsigned int intensity;
		void execute();
	};

	class Waterrain : public Rain {
	};

	class Snowrain : public Rain {
	};

	class Landrain : public Rain {
	};

	class Lavarain : public Rain {
	};

	class Bombrain : public Rain {
	};

	class Itemrain : public Rain {
	};

	class Volcano {
		// Spills out lava slowly, may erupt and spill a lot of lava into the sky
		// Generates smoke
		unsigned short lava_intensity;
		unsigned short erupt_intensity;
	};

	class Shark : public Polygon2D {
		// Eats swimming humans
		unsigned char hungryness;
	};

	class Level {
		public:
			std::vector<Background> backgrounds;	// Parallax backgrounds
			//std::vector<Waterpixel> water;
			std::vector<Volcano> volcanos;
			std::vector<Shark> sharks;
	};

	class Randomlevelgenerator {
		int seed;
		unsigned int wateramount;
		unsigned int landamount;
		unsigned int blackholes;
		unsigned int scatterness;
		unsigned int pipe_amount;
		unsigned int volcano_amount;
		int temperature;	// minus for more ice/snow, plus for more lava
		// randomize base locations (players can change it)
	};

	class Shop {
		std::vector<Vehicle> vehicles_available;
		std::vector<Weapon> weapons_available;
		std::vector<Shield> shields_available;
		std::vector<Gadget> gadgets_available;
	};

	class Gameplay {
		public:
			Level *level;
			std::vector<Player> players;
			std::vector<Rogue> rogues;
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
			bool init_titlescreen();
			bool deinit_titlescreen();
			bool init_gameplay();
			bool deinit_gameplay();
			bool mainloop() override;
			EffuxCircles *effux_circles;
			// Polygons:
				Triangle2D *rocket;
				//Polygon2D rocket;
				//Rocket *rocket;
			// DATA:
				Audio *music_title, *music_gameplay;
				SDL_Texture *pic_titlescreen;
	};

#endif // PROGRAM_ROCKETZ_HPP
