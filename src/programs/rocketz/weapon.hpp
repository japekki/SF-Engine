/*
TODO:
- Option to make any weapon a bouncer
- Human weapons
*/

#ifndef WEAPON_HPP
	#define WEAPON_HPP

	#include <string>

	// Forward declarations:
	class Polygon;
	class Player;

	class Weapon {
		public:
			// Has to be triggered, unlike Shield
			std::string name;
			std::string description;
			Player* owner;
			unsigned short loading_time = 0;
			bool works_under_water;
			unsigned char level;	// How powerful the weapon is
			unsigned short buy_price;
			unsigned short sell_price;
			short recoil;	// if negative, the weapon pulls the vehicle forwards when shooting (depending of course where the weapon is located in the vehicle)
			Polygon *picture;	// Or Sprite - shows up in shop and menus
			// sound
			Weapon();
			~Weapon();
			virtual void shoot();
	};

	class Weapon_absorber : public Weapon {
		public:
			Weapon_absorber();
			void shoot() override;
	};

	class Weapon_anchor : public Weapon {
		public:
			Weapon_anchor();
			void shoot() override;
	};

	class Weapon_blackhole : public Weapon {
		public:
			Weapon_blackhole();
			void shoot() override;
	};

	class Weapon_bouncer : public Weapon {
		public:
			unsigned short bounces_left = 10;
			Weapon_bouncer();
			void shoot() override;
	};

	class Weapon_bubblegum : public Weapon {
		public:
			Weapon_bubblegum();
			void shoot() override;
	};

	class Weapon_cannon : public Weapon {
		public:
			Weapon_cannon();
			void shoot() override;
	};

	class Weapon_cluster : public Weapon {
		public:
			Weapon_cluster();
			void shoot() override;
	};

	class Weapon_darkgrenade : public Weapon {
		public:
			Weapon_darkgrenade();
			void shoot() override;
	};

	class Weapon_disguise : public Weapon {
		public:
			Weapon_disguise();
			void shoot() override;
	};

	class Weapon_dockstation : public Weapon {
		public:
			Weapon_dockstation();
			void shoot() override;
	};

	class Weapon_duster : public Weapon {
		public:
			Weapon_duster();
			void shoot() override;
	};

	class Weapon_ejectionseat : public Weapon {
		public:
			Weapon_ejectionseat();
			void shoot() override;
	};

	class Weapon_electro : public Weapon {
		public:
			Weapon_electro();
			void shoot() override;
	};

	class Weapon_emp : public Weapon {
		public:
			Weapon_emp();
			void shoot() override;
	};

	class Weapon_flashgrenade : public Weapon {
		public:
			Weapon_flashgrenade();
			void shoot() override;
	};

	class Weapon_freezer : public Weapon {
		public:
			Weapon_freezer();
			void shoot() override;
	};

	class Weapon_gravity : public Weapon {
		public:
			Weapon_gravity();
			void shoot() override;
	};

	class Weapon_grenade : public Weapon {
		public:
			unsigned short timer;
			Weapon_grenade();
			void shoot() override;
	};

	class Weapon_grinder : public Weapon {
		public:
			Weapon_grinder();
			void shoot() override;
	};

	class Weapon_hologram : public Weapon {
		public:
			Weapon_hologram();
			void shoot() override;
	};

	class Weapon_invisibility : public Weapon {
		public:
			Weapon_invisibility();
			void shoot() override;
	};

	class Weapon_jammer : public Weapon {
		public:
			Weapon_jammer();
			void shoot() override;
	};

	class Weapon_laser : public Weapon {
		public:
			Weapon_laser();
			void shoot() override;
	};

	class Weapon_lifestealer : public Weapon {
		public:
			Weapon_lifestealer();
			void shoot() override;
	};

	class Weapon_mine : public Weapon {
		public:
			Weapon_mine();
			void shoot() override;
	};

	class Weapon_minimissile : public Weapon {
		public:
			Weapon_minimissile();
			void shoot() override;
	};

	class Weapon_minitorpedo : public Weapon {
		public:
			Weapon_minitorpedo();
			void shoot() override;
	};

	class Weapon_missile : public Weapon {
		public:
			Weapon_missile();
			void shoot() override;
	};

	class Weapon_moebius : public Weapon {
		public:
			Weapon_moebius();
			void shoot() override;
	};

	class Weapon_napalm : public Weapon {
		public:
			Weapon_napalm();
			void shoot() override;
	};

	class Weapon_painter : public Weapon {
		public:
			Weapon_painter();
			void shoot() override;
	};

	class Weapon_phaser : public Weapon {
		public:
			Weapon_phaser();
			void shoot() override;
	};

	class Weapon_radialgun : public Weapon {
		public:
			Weapon_radialgun();
			void shoot() override;
	};

	class Weapon_radiationbomb : public Weapon {
		public:
			Weapon_radiationbomb();
			void shoot() override;
	};

	class Weapon_random : public Weapon {
		public:
			Weapon_random();
			void shoot() override;
	};

	class Weapon_rubberband : public Weapon {
		public:
			Weapon_rubberband();
			void shoot() override;
	};

	class Weapon_selfdestruct : public Weapon {
		public:
			unsigned int timer;
			Weapon_selfdestruct();
			void shoot() override;
	};

	class Weapon_sizer : public Weapon {
		public:
			Weapon_sizer();
			void shoot() override;
	};

	class Weapon_smokegrenade : public Weapon {
		public:
			Weapon_smokegrenade();
			void shoot() override;
	};

	class Weapon_smokescreen : public Weapon {
		public:
			Weapon_smokescreen();
			void shoot() override;
	};

	class Weapon_soldier : public Weapon {
		public:
			Weapon_soldier();
			void shoot() override;
	};

	class Weapon_spraygun : public Weapon {
		public:
			Weapon_spraygun();
			void shoot() override;
	};

	class Weapon_spycam : public Weapon {
		public:
			Weapon_spycam();
			void shoot() override;
	};

	class Weapon_station : public Weapon {
		public:
			Weapon weapon;
			Weapon_station();
			void shoot() override;
	};

	class Weapon_stinger : public Weapon {
		public:
			Weapon_stinger();
			void shoot() override;
	};

	class Weapon_tangler : public Weapon {
		public:
			Weapon_tangler();
			void shoot() override;
	};

	class Weapon_teleport : public Weapon {
		public:
			Weapon_teleport();
			void shoot() override;
	};

	class Weapon_termite : public Weapon {
		public:
			Weapon_termite();
			void shoot() override;
	};

	class Weapon_torch : public Weapon {
		public:
			Weapon_torch();
			void shoot() override;
	};

	class Weapon_torpedo : public Weapon {
		public:
			Weapon_torpedo();
			void shoot() override;
	};

	class Weapon_tracer : public Weapon {
		// TODO: different weapons have different trajectories
		public:
			Weapon_tracer();
			void shoot() override;
	};

	class Weapon_tractorbeam : public Weapon {
		public:
			Weapon_tractorbeam();
			void shoot() override;
	};

	class Weapon_trajectories : public Weapon {
		public:
			Weapon_trajectories();
			void shoot() override;
	};

	class Weapon_turbo : public Weapon {
		public:
			Weapon_turbo();
			void shoot() override;
	};

	class Weapon_watergun : public Weapon {
		public:
			Weapon_watergun();
			void shoot() override;
	};

	class Weapon_wormhole : public Weapon {
		public:
			Weapon_wormhole();
			void shoot() override;
	};

	class Weapon_zoom : public Weapon {
		public:
			Weapon_zoom();
			void shoot() override;
	};

#endif // WEAPON_HPP
