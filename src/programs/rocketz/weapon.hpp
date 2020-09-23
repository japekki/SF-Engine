/*
TODO:
- Option to make any weapon a bouncer
- Human weapons
- weapon_stop_target
- weapon_spin_target
*/

#ifndef WEAPON_HPP
	#define WEAPON_HPP

	#include <string>
	#include <vector>
	#include "gamespace.hpp"

	// Forward declarations:
		class Gameplay;
		class Trianglelist;
		class Player;

	class Bullet : public Gameblob {
		public:
			SDL_Color color = SDLCOLOR_GREY;
			Bullet(Gameplay* gameplay);
			~Bullet();
			void draw();
	};

	class Blockbullet : public Gameblob {
		// bullet as level block
		public:
			uint8_t blocktype = 0;
			Blockbullet(Gameplay* gameplay);
			~Blockbullet();
			void draw();
	};

	class Waterbullet : public Blockbullet {
		// when hits land block, expires and creates water block in level
		public:
			Waterbullet(Gameplay* gameplay);
			//~Waterbullet();
			//void draw();
	};

	class Bomb : public Gameblob {
		public:
			Bomb(Gameplay* gameplay);
			int timer;		// -1 = explosion timer disabled
			void defuse();
			void execute();
	};

	class Cannonball : public Gameblob {
	};

	class Missile : public Gameblob {
	};

	class Torpedo : public Gameblob {
	};

	class Mine : public Gameblob {
	};

/*
	template<class T> class Shooter {
		public:
			Shooter();
			~Shooter();
	}
*/

/*
	class Shooter {
		public:
			Shooter();
			~Shooter();
	};
*/

	class Weapon {
		public:
			// Has to be triggered, unlike Shield
			std::string name;
			std::string description;
			Gameplay* gameplay;
			Player* owner = nullptr;
			uint32_t timestamp_lastshoot = 0;
			uint16_t loading_time = 150;
			bool works_under_water;
			unsigned char level;	// How powerful the weapon is
			uint16_t buy_price = 0;
			uint16_t sell_price = 0;
			short recoil;	// if negative, the weapon pulls the vehicle forwards when shooting (depending of course where the weapon is located in the vehicle) // TODO: Calculate as projectile collisions?
			//Trianglelist* picture = nullptr;	// Or Sprite - shows up in shop and menus
			//Mix_Chunk* sound = nullptr;
			Weapon();
			Weapon(Gameplay* gameplay);
			~Weapon();
			virtual void shoot(Point location, Vector heading, float angle, float power);
	};

	class Weapon_absorber : public Weapon {
		public:
			Weapon_absorber(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_anchor : public Weapon {
		public:
			Weapon_anchor(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_blackhole : public Weapon {
		public:
			Weapon_blackhole(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_bouncer : public Weapon {
		public:
			uint16_t bounces_left = 10;
			Weapon_bouncer(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_bubblegum : public Weapon {
		public:
			Weapon_bubblegum(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_cannon : public Weapon {
		public:
			Weapon_cannon(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_cluster : public Weapon {
		public:
			Weapon_cluster(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_darkgrenade : public Weapon {
		public:
			Weapon_darkgrenade(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_disguiser : public Weapon {
		public:
			Weapon_disguiser(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_basemaker : public Weapon {
		public:
			Weapon_basemaker(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_duster : public Weapon {
		public:
			Weapon_duster(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_electro : public Weapon {
		public:
			Weapon_electro(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_emp : public Weapon {
		public:
			Weapon_emp(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_flashbomb : public Weapon {
		public:
			Weapon_flashbomb(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_freezer : public Weapon {
		public:
			Weapon_freezer(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_gravity : public Weapon {
		public:
			Weapon_gravity(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_grenade : public Weapon {
		public:
			uint16_t timer;
			Weapon_grenade(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_grinder : public Weapon {
		public:
			Weapon_grinder(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_hologram : public Weapon {
		public:
			Weapon_hologram(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_invisibility : public Weapon {
		public:
			Weapon_invisibility(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_jammer : public Weapon {
		public:
			Weapon_jammer(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_laser : public Weapon {
		public:
			//Beam* laser;
			Weapon_laser(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_lifestealer : public Weapon {
		public:
			Weapon_lifestealer(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_floatmine : public Weapon {
		public:
			Weapon_floatmine(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_sinkmine : public Weapon {
		public:
			Weapon_sinkmine(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_minimissile : public Weapon {
		public:
			Weapon_minimissile(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_minitorpedo : public Weapon {
		public:
			Weapon_minitorpedo(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_missile : public Weapon {
		public:
			Weapon_missile(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_moebius : public Weapon {
		public:
			Weapon_moebius(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_napalm : public Weapon {
		public:
			Weapon_napalm(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_painter : public Weapon {
		public:
			Weapon_painter(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_phaser : public Weapon {
		public:
			Weapon_phaser(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_radialgun : public Weapon {
		public:
			Weapon_radialgun(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_radiationbomb : public Weapon {
		public:
			Weapon_radiationbomb(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_random : public Weapon {
		public:
			std::vector<Weapon*> weapons;
			Weapon_random(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power, std::vector<Weapon*> weaponlist);
	};

	class Weapon_rubberband : public Weapon {
		public:
			Weapon_rubberband(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_selfdestruct : public Weapon {
		public:
			uint32_t timer;
			Weapon_selfdestruct(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_sizer : public Weapon {
		public:
			Weapon_sizer(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_smokegrenade : public Weapon {
		public:
			Weapon_smokegrenade(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_smokescreen : public Weapon {
		public:
			Weapon_smokescreen(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_soldier : public Weapon {
		public:
			Weapon_soldier(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_spinner : public Weapon {
		public:
			Weapon_spinner(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_spraygun : public Weapon {
		public:
			Weapon_spraygun(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_spycam : public Weapon {
		public:
			Weapon_spycam(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_stationmaker : public Weapon {
		public:
			Weapon weapon;
			Weapon_stationmaker(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_stinger : public Weapon {
		public:
			Weapon_stinger(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_stopper : public Weapon {
		public:
			Weapon_stopper(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_tangler : public Weapon {
		public:
			Weapon_tangler(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_teleport : public Weapon {
		public:
			Weapon_teleport(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_termite : public Weapon {
		public:
			Weapon_termite(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_torch : public Weapon {
		public:
			Weapon_torch(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_torpedo : public Weapon {
		public:
			Weapon_torpedo(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_tracer : public Weapon {
		// TODO: different weapons have different trajectories
		public:
			Weapon_tracer(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_tractorbeam : public Weapon {
		public:
			Weapon_tractorbeam(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_trajectories : public Weapon {
		public:
			Weapon_trajectories(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_turbo : public Weapon {
		public:
			Weapon_turbo(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_watergun : public Weapon {
		public:
			Weapon_watergun(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_wormhole : public Weapon {
		public:
			Weapon_wormhole(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_zapper : public Weapon {
		public:
			Weapon_zapper(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

	class Weapon_zoom : public Weapon {
		public:
			Weapon_zoom(Gameplay* gameplay);
			void shoot(Point location, Vector heading, float angle, float power) override;
	};

#endif // WEAPON_HPP
