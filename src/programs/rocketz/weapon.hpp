// TODO: Option to make any weapon a bouncer?

#ifndef WEAPON_HPP
	#define WEAPON_HPP

	#include <string>
	#include "geom.hpp"

	// FILE NAMES:
		#define DATAPATH "data/"

		// Sound effects:
			#define FILENAME_SOUND_SELFDESTRUCT_INIT DATAPATH "selfdestructinit.wav"
			#define FILENAME_SOUND_ABSORB DATAPATH "absorb.wav"
			#define FILENAME_SOUND_BOUNCE DATAPATH "bounce.wav"
			#define FILENAME_SOUND_ELECTRO DATAPATH "electro.wav"
			#define FILENAME_SOUND_FREEZER DATAPATH "freezer.wav"
			#define FILENAME_SOUND_EMP DATAPATH "emp.wav"
			#define FILENAME_SOUND_GRIND DATAPATH "grind.wav"
			#define FILENAME_SOUND_HOLOGRAM DATAPATH "hologram.wav"
			#define FILENAME_SOUND_LIFESTEAL DATAPATH "lifesteal.wav"
			#define FILENAME_SOUND_MINIMISSILE DATAPATH "minimissile.wav"
			#define FILENAME_SOUND_MOEBIUS DATAPATH "moebius.wav"
			#define FILENAME_SOUND_PAINT DATAPATH "paint.wav"
			#define FILENAME_SOUND_PHASER DATAPATH "phaser.wav"
			#define FILENAME_SOUND_SIZER DATAPATH "sizer.wav"
			#define FILENAME_SOUND_TELEPORT DATAPATH "teleport.wav"
			#define FILENAME_SOUND_TRACTORBEAM DATAPATH "tractorbeam.wav"

	class Weapon {
		public:
			// Has to be triggered, unlike Shield
			std::string name;
			std::string description;
			unsigned short loading_time = 0;
			bool works_under_water;
			unsigned char level;	// How powerful the weapon is
			unsigned short buy_price;
			unsigned short sell_price;
			short recoil;	// if negative, the weapon pulls the vehicle forwards when shooting (depending of course where the weapon is located in the vehicle)
			Polygon2D *picture;	// Or Sprite - shows up in shop and menus
			// sound
	};

	class Weapon_absorber : public Weapon {
		Weapon_absorber();
	};

	class Weapon_anchor : public Weapon {
		Weapon_anchor();
	};

	class Weapon_blackhole : public Weapon {
		Weapon_blackhole();
	};

	class Weapon_bouncer : public Weapon {
		unsigned short bounces_left = 10;
		Weapon_bouncer();
	};

	class Weapon_bubblegum : public Weapon {
		Weapon_bubblegum();
	};

	class Weapon_cannon : public Weapon {
		Weapon_cannon();
	};

	class Weapon_cluster : public Weapon {
		Weapon_cluster();
	};

	class Weapon_darkgrenade : public Weapon {
		Weapon_darkgrenade();
	};

	class Weapon_disguise : public Weapon {
		Weapon_disguise();
	};

	class Weapon_dockstation : public Weapon {
		Weapon_dockstation();
	};

	class Weapon_duster : public Weapon {
		Weapon_duster();
	};

	class Weapon_ejectionseat : public Weapon {
		Weapon_ejectionseat();
	};

	class Weapon_electro : public Weapon {
		Weapon_electro();
	};

	class Weapon_emp : public Weapon {
		Weapon_emp();
	};

	class Weapon_flashgrenade : public Weapon {
		Weapon_flashgrenade();
	};

	class Weapon_freezer : public Weapon {
		Weapon_freezer();
	};

	class Weapon_gravity : public Weapon {
		Weapon_gravity();
	};

	class Weapon_grenade : public Weapon {
		unsigned short timer;
		Weapon_grenade();
	};

	class Weapon_grinder : public Weapon {
		Weapon_grinder();
	};

	class Weapon_hologram : public Weapon {
		Weapon_hologram();
	};

	class Weapon_invisibility : public Weapon {
		Weapon_invisibility();
	};

	class Weapon_jammer : public Weapon {
		Weapon_jammer();
	};

	class Weapon_laser : public Weapon {
		Weapon_laser();
	};

	class Weapon_lifestealer : public Weapon {
		Weapon_lifestealer();
	};

	class Weapon_mine : public Weapon {
		Weapon_mine();
	};

	class Weapon_minimissile : public Weapon {
		Weapon_minimissile();
	};

	class Weapon_minitorpedo : public Weapon {
		Weapon_minitorpedo();
	};

	class Weapon_missile : public Weapon {
		Weapon_missile();
	};

	class Weapon_moebius : public Weapon {
		Weapon_moebius();
	};

	class Weapon_napalm : public Weapon {
		Weapon_napalm();
	};

	class Weapon_painter : public Weapon {
		Weapon_painter();
	};

	class Weapon_phaser : public Weapon {
		Weapon_phaser();
	};

	class Weapon_radialgun : public Weapon {
		Weapon_radialgun();
	};

	class Weapon_radiationbomb : public Weapon {
		Weapon_radiationbomb();
	};

	class Weapon_random : public Weapon {
		Weapon_random();
	};

	class Weapon_rubberband : public Weapon {
		Weapon_rubberband();
	};

	class Weapon_selfdestruct : public Weapon {
		unsigned int timer;
		Weapon_selfdestruct();
	};

	class Weapon_sizer : public Weapon {
		Weapon_sizer();
	};

	class Weapon_smokegrenade : public Weapon {
		Weapon_smokegrenade();
	};

	class Weapon_smokescreen : public Weapon {
		Weapon_smokescreen();
	};

	class Weapon_soldier : public Weapon {
		Weapon_soldier();
	};

	class Weapon_spraygun : public Weapon {
		Weapon_spraygun();
	};

	class Weapon_spycam : public Weapon {
		Weapon_spycam();
	};

	class Weapon_station : public Weapon {
		Weapon weapon;
		Weapon_station();
	};

	class Weapon_stinger : public Weapon {
		Weapon_stinger();
	};

	class Weapon_teleport : public Weapon {
		Weapon_teleport();
	};

	class Weapon_termite : public Weapon {
		Weapon_termite();
	};

	class Weapon_torch : public Weapon {
		Weapon_torch();
	};

	class Weapon_torpedo : public Weapon {
		Weapon_torpedo();
	};

	class Weapon_tracer : public Weapon {
		// TODO: different weapons have different trajectories";
		Weapon_tracer();
	};

	class Weapon_tractorbeam : public Weapon {
		Weapon_tractorbeam();
	};

	class Weapon_trajectories : public Weapon {
		Weapon_trajectories();
	};

	class Weapon_turbo : public Weapon {
		Weapon_turbo();
	};

	class Weapon_watergun : public Weapon {
		Weapon_watergun();
	};

	class Weapon_wormhole : public Weapon {
		Weapon_wormhole();
	};

	class Weapon_zoom : public Weapon {
		Weapon_zoom();
	};

#endif // WEAPON_HPP
