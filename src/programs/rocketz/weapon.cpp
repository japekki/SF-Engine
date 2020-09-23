#include "weapon.hpp"
#include "player.hpp"
#include "vehicle.hpp"
#include "misc.hpp"
#include "gameplay.hpp"
#include "level.hpp"
#include "audio.hpp"
#include "block.hpp"

Bullet::Bullet(Gameplay* gameplay) : Gameblob(gameplay) {
	type = GAMEBLOB_TYPE_BULLET;
	collision_radius = 0.02;
	mass = 0.1;
	health = 50;
	max_health = 500;
}

Bullet::~Bullet() {
}

void Bullet::draw() {
	Point point;
	point.x = this->location.x;
	point.y = this->location.y;
	point = gameplay->display->grid.transform(point);

	SDL_SetRenderDrawColor(gameplay->display->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(gameplay->display->renderer, point.x-1, point.y);
	SDL_RenderDrawPoint(gameplay->display->renderer, point.x+1, point.y);
	SDL_RenderDrawPoint(gameplay->display->renderer, point.x, point.y-1);
	SDL_RenderDrawPoint(gameplay->display->renderer, point.x, point.y+1);
	SDL_RenderDrawPoint(gameplay->display->renderer, point.x, point.y);
}

Bomb::Bomb(Gameplay* gameplay) : Gameblob(gameplay) {
	health = 5;
	timer = -1;
}

void Bomb::defuse() {
	timer = -1;
}

void Bomb::execute() {
	//Explosion* boom = new Explosion(gameplay);
	//boom->create_sparks();
}

Blockbullet::Blockbullet(Gameplay* gameplay) : Gameblob(gameplay) {
	type = GAMEBLOB_TYPE_BLOCKBULLET;
	can_collide = false;
}

Blockbullet::~Blockbullet() {
	// TODO:
	// - Convert block modification into class Level
	// - What if level is without blocks?
	gameplay->level->set_block(gameplay->level->get_width()/2 + int(location.x), gameplay->level->get_height()/2 + int(location.y), COLOR_WATER);
}

void Blockbullet::draw() {
	gameplay->level->set_block(gameplay->level->get_width()/2 + int(location.x), gameplay->level->get_height()/2 + int(location.y), COLOR_WATER);
	expirecounter = 0;
	can_expire = true;
	//printf("%i %i\n", gameplay->level->get_width()/2 + int(location.x), gameplay->level->get_height()/2 + int(location.y));
}

Waterbullet::Waterbullet(Gameplay* gameplay) : Blockbullet(gameplay) {
}

//Waterbullet::~Waterbullet() {
//	Blockbullet::~Blockbullet()
//}

Weapon::Weapon() {
}

Weapon::Weapon(Gameplay* gameplay) {
	this->gameplay = gameplay;
}

Weapon::~Weapon() {
}

void Weapon::shoot(Point location, Vector heading, float angle, float power) {
	if (SDL_GetTicks() - timestamp_lastshoot > loading_time) {
		Bullet* bullet = new Bullet(gameplay);
		//bullet->can_collide = false;	// FIXME: Setting this to false does nothing
		bullet->owner = this->owner;
		bullet->location = location;
		bullet->heading = Vector(0, power);
		bullet->heading.rotate(angle);
		bullet->heading.add(heading);
		//bullet->location.move(bullet->heading);	// Make distance between bullet and shooter to prevent collision:
		gameplay->gamespace->add_blob(bullet);
		timestamp_lastshoot = SDL_GetTicks();
		gameplay->play_shoot = true;
	}
}

Weapon_absorber::Weapon_absorber(Gameplay* gameplay) {
	name = "Absorber";
	description = "Absorb energy from blasts";
}

void Weapon_absorber::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_floatmine::Weapon_floatmine(Gameplay* gameplay) {
	name = "Floating mine";
	description = "Plants a floating mine that explodes if something touches it (or there's a blast near it).";
}

void Weapon_floatmine::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_anchor::Weapon_anchor(Gameplay* gameplay) {
	name = "Anchor";
	description = "Deploy (or shoot) an achor.";
}

void Weapon_anchor::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_blackhole::Weapon_blackhole(Gameplay* gameplay) {
	name = "Black hole";
	description = "Create a black hole that alters the trajectory of projectiles.";
}

void Weapon_blackhole::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_bouncer::Weapon_bouncer(Gameplay* gameplay) {
	name = "Bouncer";
	description = "Bounces when hit (makes damage every time).";
}

void Weapon_bouncer::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_bubblegum::Weapon_bubblegum(Gameplay* gameplay) {
	name = "Bubblegum gun";
	description = "Create sticky goo.";
}

void Weapon_bubblegum::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_cannon::Weapon_cannon(Gameplay* gameplay) {
	name = "Cannon";
	description = "Shoot iron ball.";	// TODO: Explosive version
}

void Weapon_cannon::shoot(Point location, Vector heading, float angle, float power) {
	//this->owner->add_bullet(new Cannonball());
}

Weapon_cluster::Weapon_cluster(Gameplay* gameplay) {
	name = "Cluster bomb";
	description = "Shoot bullets around when timer expire or gets hit.";
}

void Weapon_cluster::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_darkgrenade::Weapon_darkgrenade(Gameplay* gameplay) {
	name = "Dark grenade";
	description = "Like flash grenade, but makes darkness.";
}

void Weapon_darkgrenade::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_disguiser::Weapon_disguiser(Gameplay* gameplay) {
	name = "Disguiser";
	description = "Appear to be different vehicle model or color.";
}

void Weapon_disguiser::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_basemaker::Weapon_basemaker(Gameplay* gameplay) {
	name = "Base maker";
	description = "Drop new base.";
}

void Weapon_basemaker::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_duster::Weapon_duster(Gameplay* gameplay) {
	name = "Duster";
	description = "Make a chunk of dirt.";
}

void Weapon_duster::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_electro::Weapon_electro(Gameplay* gameplay) {
	name = "Electro";
	description = "Make electric lightning arcs.";
}

void Weapon_electro::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_emp::Weapon_emp(Gameplay* gameplay) {
	name = "Emp";
	description = "Make nearby electronics (vehicles and gadgets) to shut down or malfunction.";
}

void Weapon_emp::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_flashbomb::Weapon_flashbomb(Gameplay* gameplay) {
	name = "Flash bomb";
	description = "Flashing light when explodes, causes temporary blindness/darkness.";
}

void Weapon_flashbomb::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_freezer::Weapon_freezer(Gameplay* gameplay) {
	name = "Freezer";
	description = "Shoot ice.";
}

void Weapon_freezer::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_gravity::Weapon_gravity(Gameplay* gameplay) {
	name = "Gravity";
	description = "Cancel or alter gravity (push or pull).";
}

void Weapon_gravity::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_grenade::Weapon_grenade(Gameplay* gameplay) {
	name = "grenade";
	description = "Shoot a grenade that blows up after timer has elapsed.";
}

void Weapon_grenade::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_grinder::Weapon_grinder(Gameplay* gameplay) {
	name = "Grinder";
	description = "Blades rotating around the vehicle, eats a hole in the ground.";
}

void Weapon_grinder::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_hologram::Weapon_hologram(Gameplay* gameplay) {
	name = "Hologram";
	description = "Create a moving image of vehicle, weapon, human, item or gadget to fool other players.";
}

void Weapon_hologram::shoot(Point location, Vector heading, float angle, float power) {
	// Create player with vehicle, add to* shooter's team
}

Weapon_invisibility::Weapon_invisibility(Gameplay* gameplay) {
	name = "Invisibility";
	description = "Make vehicle invisible to others.";
}

void Weapon_invisibility::shoot(Point location, Vector heading, float angle, float power) {
	this->owner->vehicle->shadestyle = POLYGON_SHADESTYLE_NODRAW;
}

Weapon_jammer::Weapon_jammer(Gameplay* gameplay) {
	name = "Jammer";
	description = "Make nearby weapons, radio or remote controllers unusable.";
}

void Weapon_jammer::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_laser::Weapon_laser(Gameplay* gameplay) {
	name = "Laser";
	description = "Shoot straight thin line of burning light.";
	loading_time = 0;	// Continuous beam
	//this->laser = new Beam(this->gameplay);
	//this->laser->can_collide = false;
}

void Weapon_laser::shoot(Point location, Vector heading, float angle, float power) {
	// TODO:
	// - Delete
	//if (SDL_GetTicks() - timestamp_lastshoot > loading_time) {

		//laser->owner = this->owner;
		//laser->location = location;	// Starting point
		//Vector arc(0, 1);
		//arc.rotate(angle);
		//laser->heading = (heading);	// Shooter's heading irrelevant / no momentum in beam
		//laser->heading.add(arc);
		//gameplay->space->add_blob(laser);
			// TODO: Replace previous laser blob (laser beam disappears instantly if not beaming)

		//timestamp_lastshoot = SDL_GetTicks();

		//location = vehicle location
		//heading = vehicle rotation
		// TODO: Bend curve near black holes / worm holes
	//}

}

Weapon_lifestealer::Weapon_lifestealer(Gameplay* gameplay) {
	name = "Lifestealer";
	description = "Steal health from target.";
}

void Weapon_lifestealer::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_minimissile::Weapon_minimissile(Gameplay* gameplay) {
	name = "Mini missile";
	description = "Like missile, but many little missiles launched fast.";
}

void Weapon_minimissile::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_minitorpedo::Weapon_minitorpedo(Gameplay* gameplay) {
	name = "Mini torpedo";
	description = "Like torpedo, but many little torpedoes launched fast.";
}

void Weapon_minitorpedo::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_missile::Weapon_missile(Gameplay* gameplay) {
	name = "Missile";
	description = "Follows / targets to objects.";
}

void Weapon_missile::shoot(Point location, Vector heading, float angle, float power) {
	//this->owner->add_bullet(new Missile());
}

Weapon_moebius::Weapon_moebius(Gameplay* gameplay) {
	name = "Moebius";
	description = "Warp from one level edge to the opposite, or go to the \"other side\" of the 2D world.";
}

void Weapon_moebius::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_napalm::Weapon_napalm(Gameplay* gameplay) {
	name = "Napalm";
	description = "Drop burning napalm.";
}

void Weapon_napalm::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_painter::Weapon_painter(Gameplay* gameplay) {
	name = "Painter";
	description = "Recolor things, like ground, buildings or vehicles.";
}

void Weapon_painter::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_phaser::Weapon_phaser(Gameplay* gameplay) {
	name = "Phaser";
	description = "Go trough solid matter. Instant death if re-appear inside matter.";
}

void Weapon_phaser::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_radialgun::Weapon_radialgun(Gameplay* gameplay) {
	name = "Radial gun";
	description = "Shoot to many directions at once, as a circle of bullets.";
	loading_time = 20000;
}

void Weapon_radialgun::shoot(Point location, Vector heading, float angle, float power) {
	// Create a circle of bullets
	// TODO: weapon level determines amount of bullets and reload time
	if (SDL_GetTicks() - timestamp_lastshoot > loading_time) {
		for (int i=0; i<100; i++) {
			Bullet* bullet = new Bullet(gameplay);
			bullet->owner = this->owner;
			bullet->location = location;
			Vector arc(0, 1);
			arc.rotate(PI / 50 * i);
			bullet->location.move(arc);	// Make distance between bullet and shooter to prevent collision:
			//bullet->heading = arc;
			arc.i = 0;
			arc.j = power*0.75;
			arc.rotate(PI / 50 * i);
			bullet->heading = arc;
			bullet->heading.add(heading);
			gameplay->gamespace->add_blob(bullet);
		}
		timestamp_lastshoot = SDL_GetTicks();
		gameplay->play_radialgun = true;
	}
}

Weapon_radiationbomb::Weapon_radiationbomb(Gameplay* gameplay) {
	name = "Radiation bomb";
	description = "Generate invisible radiation that makes more damage the closer someone gets to it.";
}

void Weapon_radiationbomb::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_random::Weapon_random(Gameplay* gameplay) {
	name = "Random";
	description = "Random weapon each time when shooting.";
	// Create all weapons:
		//this->weapons.push_back(new Weapon_absorber());
		// TODO: some better way to do this?
}

void Weapon_random::shoot(Point location, Vector heading, float angle, float power, std::vector<Weapon*> weaponlist) {
	//this->weapons[rand() % 10)->shoot(Point location, Vector heading, float angle, float power);
	weaponlist[rand() % weaponlist.size()]->shoot(location, heading, angle, power);	// TODO: Randomize
}

Weapon_rubberband::Weapon_rubberband(Gameplay* gameplay) {
	name = "Rubberband";
	description = "Shoot a stretchy harpoon. Second shoot releases the end part. Both endpoints stick to ground, vehicles and gadgets";
}

void Weapon_rubberband::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_selfdestruct::Weapon_selfdestruct(Gameplay* gameplay) {
	name = "Self destruct";
	description = "Destroys the vehicle itself with a huge explosion.";
}

void Weapon_selfdestruct::shoot(Point location, Vector heading, float angle, float power) {
}


Weapon_sinkmine::Weapon_sinkmine(Gameplay* gameplay) {
	name = "Sinking mine";
	description = "Drops a sinking mine that explodes if something touches it (or there's a blast near it).";
}

void Weapon_sinkmine::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_sizer::Weapon_sizer(Gameplay* gameplay) {
	name = "Sizer";
	description = "Change vehicle size.";
}

void Weapon_sizer::shoot(Point location, Vector heading, float angle, float power) {
	//this->owner->vehicle->polygon->scale();
}

Weapon_smokegrenade::Weapon_smokegrenade(Gameplay* gameplay) {
	name = "Smoke grenade";
	description = "Throw a grenade that creates smoke.";
}

void Weapon_smokegrenade::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_smokescreen::Weapon_smokescreen(Gameplay* gameplay) {
	name = "Smoke screen";
	description = "Create smoke around the vehicle.";
}

void Weapon_smokescreen::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_soldier::Weapon_soldier(Gameplay* gameplay) {
	name = "Soldier";
	description = "Drop a human soldier that has a gun.";
}

void Weapon_soldier::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_spinner::Weapon_spinner(Gameplay* gameplay) {
	name = "Spinner";
	description = "Make target object spin.";
}

void Weapon_spinner::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_spraygun::Weapon_spraygun(Gameplay* gameplay) {
	name = "Spray gun";
	description = "Shoot spray of bullets.";
	loading_time = 15;
}

void Weapon_spraygun::shoot(Point location, Vector heading, float angle, float power) {
	if (SDL_GetTicks() - timestamp_lastshoot > loading_time) {
		for (int i=0; i<2; i++) {
			Bullet* bullet = new Bullet(gameplay);
			bullet->owner = this->owner;
			bullet->location = location;
			Vector arc(0, 2);
			arc.rotate(angle);
			bullet->location.move(arc);	// Make distance between bullet and shooter to prevent collision:
			arc.i = 0;
			arc.j = power/2;
			arc.rotate(angle + PIPER2/2 / 100 * float(rand() % 100 - 50));
			bullet->heading = (arc);
			bullet->heading.add(heading);
			gameplay->gamespace->add_blob(bullet);
			timestamp_lastshoot = SDL_GetTicks();
		}
	}
}

Weapon_spycam::Weapon_spycam(Gameplay* gameplay) {
	name = "Spy cam";
	description = "Deploy a spying camera which can be monitored remotely.";
}

void Weapon_spycam::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_stationmaker::Weapon_stationmaker(Gameplay* gameplay) {
	name = "Station maker";
	description = "Drop an autonomous station that shoots with some weapon.";
}

void Weapon_stationmaker::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_stinger::Weapon_stinger(Gameplay* gameplay) {
	name = "Stinger";
	description = "Sword-like sharp spike.";
}

void Weapon_stinger::shoot(Point location, Vector heading, float angle, float power) {
	// this->owner->vehicle->polygon->add_polygon(new Stinger());
}

Weapon_stopper::Weapon_stopper(Gameplay* gameplay) {
	name = "Stopper";
	description = "Slow down or stop target object.";
}

void Weapon_stopper::shoot(Point location, Vector heading, float angle, float power) {
	// Draw sector
	// slow dorn objects that are covered by the sector
}

Weapon_tangler::Weapon_tangler(Gameplay* gameplay) {
	name = "Tangler";
	description = "Make target object attract projectiles.";
}

void Weapon_tangler::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_teleport::Weapon_teleport(Gameplay* gameplay) {
	name = "Teleport";
	description = "Teleport to random location or to previously set location.";
}

void Weapon_teleport::shoot(Point location, Vector heading, float angle, float power) {
	this->owner->vehicle->location = Point(0, 0);
}

Weapon_termite::Weapon_termite(Gameplay* gameplay) {
	name = "Termite";
	description = "Sticky burning bomb.";
}

void Weapon_termite::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_torch::Weapon_torch(Gameplay* gameplay) {
	name = "Torch";
	description = "Shoot fire with flame thrower.";
}

void Weapon_torch::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_torpedo::Weapon_torpedo(Gameplay* gameplay) {
	name = "Torpedo";
	description = "Like missile, but under water.";
}

void Weapon_torpedo::shoot(Point location, Vector heading, float angle, float power) {
	//this->owner->add_bullet(new Torpedo());
}

Weapon_tracer::Weapon_tracer(Gameplay* gameplay) {
	name = "Tracer";
	description = "Draws a trajectory curve with no damage.";
}

void Weapon_tracer::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_tractorbeam::Weapon_tractorbeam(Gameplay* gameplay) {
	name = "Tractor beam";
	description = "Pull stuff or lock into relative position/location. For example, a rocket can move a ship with this. If the movable object is heavy, many rockets with tractor beams can co-operate to move it.";
}

void Weapon_tractorbeam::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_trajectories::Weapon_trajectories(Gameplay* gameplay) {
	name = "Trajectories";
	description = "Show tracers and vectors of all projectiles.";
}

void Weapon_trajectories::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_turbo::Weapon_turbo(Gameplay* gameplay) {
	name = "Turbo";
	description = "Increased max speed and acceleration for a while.";
}

void Weapon_turbo::shoot(Point location, Vector heading, float angle, float power) {
	this->owner->vehicle->acceleration += this->level;
}

Weapon_watergun::Weapon_watergun(Gameplay* gameplay) {
	name = "Watergun";
	description = "Shoot water.";
}

void Weapon_watergun::shoot(Point location, Vector heading, float angle, float power) {
	if (SDL_GetTicks() - timestamp_lastshoot > loading_time) {
		Waterbullet* droplet = new Waterbullet(gameplay);
		//droplet->can_collide = false;	// FIXME: Setting this to false does nothing
		droplet->owner = this->owner;
		droplet->location = location;
		droplet->heading = Vector(0, power);
		droplet->heading.rotate(angle);
		droplet->heading.add(heading);
		//droplet->location.move(droplet->heading);	// Make distance between droplet and shooter to prevent collision:
		gameplay->gamespace->add_blob(droplet);
		timestamp_lastshoot = SDL_GetTicks();
		gameplay->play_watergun = true;
	}
}

Weapon_wormhole::Weapon_wormhole(Gameplay* gameplay) {
	name = "Wormhole";
	description = "Create a wormhole.";
}

void Weapon_wormhole::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_zapper::Weapon_zapper(Gameplay* gameplay) {
	name = "Zapper";
	description = "Zap nearby objects with fast electric discharge.";
}

void Weapon_zapper::shoot(Point location, Vector heading, float angle, float power) {
}

Weapon_zoom::Weapon_zoom(Gameplay* gameplay) {
	name = "Zoomer";
	description = "Zoom closer or further";
}

void Weapon_zoom::shoot(Point location, Vector heading, float angle, float power) {
	//this->owner->viewing_window->
}
