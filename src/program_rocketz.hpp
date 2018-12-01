/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a rocket game.
*/

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
- Make some weapons as shields, gadgets or vehicle model features
- Level editor
- Level file format
- Random level generator
- Sprites or polygons?
- Use Entity class (for animation etc.) instead of plain Sprite or Polygon2D
- Weapons, shields and gadgets for humans (diving suit, heat suit, parachutes)
- If volcanoes, lava etc. are on a background layer, they're not dangerous
- Possibility to ride on a different layer (to dodge projectiles or go behind/front of ladders instead of crashing into them)
- Difference between sabotage, emp and virus?
- Trees, bushes etc.
- Arcade style self-play demo mode with random values and computer players
- Classes for scenes, set and compare variables lastscene and currentscene to do init/deinit with constructors/destructors
- Friction
- Zooming
- Mouse support
- Use MIDI controllers as joystick / game controller
- Stats during and after game (most (total and serial/massacre) kills, most suicides, most damage dealt etc.)
- Replay highlights / most impressive parts after game with fireworks effux
- Separate code into many program_rocketz_* files
*/

#ifndef PROGRAM_ROCKETZ_HPP
	#define PROGRAM_ROCKETZ_HPP

	#include "program.hpp"
	#include "projectile.hpp"
	#include "geom.hpp"
	#include "effux_circles.hpp"
	#include "effux_textscroller.hpp"
	#include "effux_sky.hpp"
	#include "effux_fire.hpp"
	#include "effux_smoke.hpp"
	#include "water.hpp"

	// SCENES:
		#define SCENE_NONE 0
		#define SCENE_TITLESCREEN 1
		#define SCENE_SETTINGS 2
		#define SCENE_GAMEPLAY 3
		#define SCENE_SELFPLAY 4
		#define SCENE_SHOP 5
		#define SCENE_CREDITS 6

	// LAYER TYPES:
		#define LAYER_NONE 0
		#define LAYER_COLOR 1
		#define LAYER_BITMAP 2
		#define LAYER_EFFUX 3

	// FILE NAMES:
		#define DATAPATH "data/"

		// Fonts:
			#define FILENAME_FONT_XENOSPHERE DATAPATH "xenosphere.ttf"
			#define FILENAME_FONT_MODENINE DATAPATH "MODENINE.TTF"

		// Pictures:
			#define FILENAME_PIC_TITLESCREEN_WITH_TEXT DATAPATH "RocketZ_titlescreen.png"	// TODO: generate with code, or make fancier picture
			#define FILENAME_PIC_TITLESCREEN DATAPATH "titlescreen.png"

		// Sound effects:
			#define FILENAME_SOUND_JETENGINE DATAPATH "jetengine.wav"
			#define FILENAME_SOUND_DIESELMOTOR DATAPATH "dieselmotor.wav"
			#define FILENAME_SOUND_EXPLOSION DATAPATH "explosion.wav"
			#define FILENAME_SOUND_IMPLOSION DATAPATH "implosion.wav"
			#define FILENAME_SOUND_BULLETHIT DATAPATH "bullethit.wav"
			#define FILENAME_SOUND_SHOOT DATAPATH "shoot.wav"
			#define FILENAME_SOUND_HUMANSCREAM DATAPATH "humanscream.wav"
			#define FILENAME_SOUND_TELEPORT DATAPATH "teleport.wav"
			#define FILENAME_SOUND_CRASH DATAPATH "crash.wav"
			#define FILENAME_SOUND_BUY DATAPATH "buy.wav"
			#define FILENAME_SOUND_SELL DATAPATH "sell.wav"
			#define FILENAME_SOUND_NOTENOUGHMONEY DATAPATH "notenoughmoney.wav"
			#define FILENAME_SOUND_BLACKHOLE_CREATED DATAPATH "blackholecreated.wav"
			#define FILENAME_SOUND_WORMHOLE_USED DATAPATH "wormholeused.wav"
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
			#define FILENAME_SOUND_SIZER DATAPATH "sizer.wav"
			#define FILENAME_SOUND_SMOKE DATAPATH "smoke.wav"
			#define FILENAME_SOUND_TRACTORBEAM DATAPATH "tractorbeam.wav"
			#define FILENAME_SOUND_ALARM DATAPATH "alarm.wav"
			#define FILENAME_SOUND_BASEATTACKWARNING DATAPATH "baseattackwarning.wav"
			#define FILENAME_SOUND_VOLCANO_ERUPT DATAPATH "volcanoerupt.wav"

		// Music:
			#define FILENAME_MUSIC_TITLE DATAPATH "Nuggumath-Wings-pelimusa-ReMix_CROPPED.mp3"
			#define FILENAME_MUSIC_GAMEPLAY DATAPATH "game1.xm"

	class Gadget : public Polygon2D, public Projectile2D {
		// To be planted, not collectible, can be moved with tractor beam etc.
		// TODO: think this over
		bool can_float;
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

	class Anchor : public Gadget {
		// Attaches to vehicle, sticks to ground
	};

	class Ladders : public Gadget {
		// For humans to climb up and down
		// Can go vertically, horizontally (bridge) or diagonally
		Coordinate2D starting_point;
		Coordinate2D ending_point;
		// TODO: what happens when hit in the middle
	};

	class Boulder : public Gadget {
		// Stones rolling down a hill, crushing stuff
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
		unsigned short ammo;	// TODO: infinite
		//bool inside_vehicle;
		//void steal(Vehicle *vehicle);
		//void sabotage(Vehicle *vehicle);	// TODO: sabotage gadgets
		//void plant_virus(Vehicle *vehicle);	// TODO: same as sabotage?
	};

	class Hoarder : public Human {
		// Human that hoards items on the field and take them to base, or vice versa
		// Can also steal items from enemy base
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
		std::string name;
		std::string description;
		unsigned int condition;	// 0 if worn out
		bool works_under_water;
		unsigned char level;	// How powerful the shield is
		unsigned short buy_price;
		unsigned short sell_price;
		//Polygon2D picture;	// Or Sprite - shows up in shop and menus
		// sound
	};

	class Shield_emp {
		// Protect from EMP
	};

	class Shield_lightscreen : public Shield {
		// Allows to see in bright light, protects from blindness caused by flashes
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
		std::string name;
		std::string description;
		unsigned short loading_time = 0;
		bool works_under_water;
		unsigned char level;	// How powerful the weapon is
		unsigned short buy_price;
		unsigned short sell_price;
		short recoil;	// if negative, the weapon pulls the vehicle forwards when shooting (depending of course where the weapon is located in the vehicle)
		//Polygon2D picture;	// Or Sprite - shows up in shop and menus
		// sound
	};

	class Weapon_absorber : public Weapon {
		// Absorb energy from blasts
	};

	class Weapon_anchor : public Weapon {
		// Deploy (or shoot) an achor
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
		// Appear to be different vehicle model or color
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
		// Create a moving image of weapon, human or gadget to fool other players
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
		// Recolor things, like ground, buildings or vehicles
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
		// Both endpoints stick to ground, vehicles and gadgets
	};

	class Weapon_selfdestruct : public Weapon {
		// Destroys the vehicle itself with a huge explosion
		unsigned int timer;
	};

	class Weapon_sizer : public Weapon {
		// Change vehicle size
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
		// Teleport to random location or to previously set location
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

	class Weapon_minitorpedo : public Weapon {
		// Like torpedo, but many little torpedoes launched fast
	};

	class Weapon_tracer : public Weapon {
		// Draws a trajectory curve with no damage
		// TODO: different weapons have different trajectories
	};

	class Weapon_tractorbeam : public Weapon {
		// Pull stuff or lock into relative position/location
		// For example, a rocket can move a ship with this
		// If the movable object is heavy, many rockets with tractor beams can co-operate to move it
	};

	class Weapon_trajectories : public Weapon {
        // Show tracers and vectors of all projectiles
	};

	class Weapon_turbo : public Weapon {
		// Increased max speed and acceleration for a while
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
		//SDL_Texture *bitmap;
		// TODO: pointer for effux
	};

	class Land {
		// bool soft, sticky, slippery, burning, freezing
		// bool flammable, meltable, steamable/vaporable, smokable (???)
		// If land is hard, it makes damage on impact and leaves a hole when blasted
		// If land is soft, it doesn't make damage on impact and falls straight down without leaving a hole when blasted
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
		short lifeforce;
		unsigned char hungryness;
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

	class Level {
		public:
			//Parameters parameters;
			std::vector<Background> backgrounds;	// Parallax backgrounds
			//std::vector<Waterpixel> water;
			std::vector<Volcano> volcanos;
			std::vector<Shark> sharks;
	};

	class Randomlevelgenerator {
			public:
			Level *level;
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
		std::vector<Item> items_available;
	};

	class Gameplay {
		public:
			Level *level;
			std::vector<Player> players;
			std::vector<Rogue> rogues;
			bool gameover = false;
			void execute();
			//bool state_recording = false;
			//bool load_state();
			//bool save_state();
			Triangle2D *rocket;	// Test
	};

	class Selfplay : public Gameplay {
		// Arcade demo mode
	};

	class AI {
		// Artificial intelligence / computer player
		/*
			TODO:
            - calculate rocket steering maneuvers to go forwards to a specific location
            - difficulty adjustment
            - decision making balancer:
                - pursue game mode goal/objective
                - need for power-ups
                - need for money
                - need for items
                - flee or attack
                - use gadgets
                - select good weapons and shields (like if enemy has a laser, then use mirror)
            - get fooled like human player would (like if enemy is invisible or has disguised)
            - get information only from visible range (including spycam, radar etc.)
            - calculate trajectories (makes tracer and Weapon_trajectories obsolete?)
            - guess what enemy is doing (like pursuing a power-up and possibly give up pursuing the same item if it seems that the enemy will get it first)
		*/
		/*
			select nearest enemy
			calculate trajectories for weapon and target
			shoot at the enemy

			select nearest power-up
			go towards power-up

			if lifeforce below half:
				check if health power-up available
				go towards power-up
				shoot at nearby enemies

			calculate trajectories
			do extra maneuvers or use shield/weapon to avoid getting hit
		*/
	};

	class Rocketz : public Program {
		protected:
			unsigned char scene = SCENE_NONE;
		public:
			Rocketz();
			~Rocketz();
			bool init() override;
			Gameplay *gameplay;
			// Scene init and deinit functions:
				bool init_titlescreen();
				bool deinit_titlescreen();
				void titlescreen_effux(unsigned int time);					// TODO: move to titlescreen scene class
				void titlescreen_textscroller_japesoft(unsigned int time);	// TODO: move to titlescreen scene class
				void titlescreen_textscroller_poem(unsigned int time);		// TODO: move to titlescreen scene class
				void titlescreen_textscroller_credits(unsigned int time);	// TODO: move to titlescreen scene class
				bool init_gameplay();
				bool deinit_gameplay();
			bool mainloop() override;
			// Effuxes:
				EffuxCircles *effux_circles;
				EffuxTextscroller *effux_textscroller_japesoft;
				EffuxTextscroller *effux_textscroller_poem;
				EffuxTextscroller *effux_textscroller_credits;
				int song_start_timestamp;	// for title screen text scroller
			// Polygons:
				//Triangle2D *rocket;
				//Polygon2D rocket;
				//Rocket *rocket;
			// DATA:
				Audio *music_title;
				//Audio *music_gameplay;
				SDL_Texture *pic_titlescreen;
				SDL_Texture *pic_titlescreen_with_text;
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
					"the chosen real men's vehicles shall fight again!";
				std::string multilinetext_credits =
					"CREDITS:\n"
					"\n"
					"Programming: JaPeK\n"
					"\n"
					"Music: Nuggumath\n"
					"\n"
					"Fonts: Darrell Flood, Andrew Bulhak";
	};

#endif // PROGRAM_ROCKETZ_HPP
