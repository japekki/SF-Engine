#include "weapon.hpp"
#include "player.hpp"
#include "vehicle.hpp"
#include "geom.hpp"

Weapon::Weapon() {
}

Weapon::~Weapon() {
}

void Weapon::shoot() {
}

Weapon_absorber::Weapon_absorber() {
	// Absorb energy from blasts
}

void Weapon_absorber::shoot() {
}

Weapon_anchor::Weapon_anchor() {
	description = "Deploy (or shoot) an achor.";
}

void Weapon_anchor::shoot() {
}

Weapon_blackhole::Weapon_blackhole() {
	description = "Create a black hole that alters the trajectory of projectiles.";
}

void Weapon_blackhole::shoot() {
}

Weapon_bouncer::Weapon_bouncer() {
	description = "Bounces when hit (makes damage every time).";
}

void Weapon_bouncer::shoot() {
}

Weapon_bubblegum::Weapon_bubblegum() {
	description = "Create sticky goo.";
}

void Weapon_bubblegum::shoot() {
}

Weapon_cannon::Weapon_cannon() {
	description = "Shoot iron ball.";	// TODO: Explosive version
}

void Weapon_cannon::shoot() {
}

Weapon_cluster::Weapon_cluster() {
	description = "Shoot bullets around when gets hit.";
}

void Weapon_cluster::shoot() {
}

Weapon_darkgrenade::Weapon_darkgrenade() {
	description = "Like flash grenade, but makes darkness.";
}

void Weapon_darkgrenade::shoot() {
}

Weapon_disguise::Weapon_disguise() {
	description = "Appear to be different vehicle model or color.";
}

void Weapon_disguise::shoot() {
}

Weapon_dockstation::Weapon_dockstation() {
	description = "Drop a docking station.";
}

void Weapon_dockstation::shoot() {
}

Weapon_duster::Weapon_duster() {
	description = "Create a chunk of dirt when hit.";
}

void Weapon_duster::shoot() {
}

Weapon_ejectionseat::Weapon_ejectionseat() {
	description = "Eject the human driver away from the vehicle.";
}

void Weapon_ejectionseat::shoot() {
}

Weapon_electro::Weapon_electro() {
	description = "Electric lightning arc.";
}

void Weapon_electro::shoot() {
}

Weapon_emp::Weapon_emp() {
	description = "Make nearby electronics (vehicles and gadgets) to shut down or malfunction for a while.";
}

void Weapon_emp::shoot() {
}

Weapon_flashgrenade::Weapon_flashgrenade() {
	description = "Fast flash of light, causes temporary blindness/darkness afterwards.";
}

void Weapon_flashgrenade::shoot() {
}

Weapon_freezer::Weapon_freezer() {
	description = "Shoot ice.";
}

void Weapon_freezer::shoot() {
}

Weapon_gravity::Weapon_gravity() {
	description = "Cancel or alter gravity (push or pull).";
}

void Weapon_gravity::shoot() {
}

Weapon_grenade::Weapon_grenade() {
	description = "Shoot a grenade that blows up after timer has elapsed.";
}

void Weapon_grenade::shoot() {
}

Weapon_grinder::Weapon_grinder() {
	description = "Blades rotating around the vehicle, eats a hole in the ground.";
}

void Weapon_grinder::shoot() {
}

Weapon_hologram::Weapon_hologram() {
	description = "Create a moving image of vehicle, weapon, human, item or gadget to fool other players.";
}

void Weapon_hologram::shoot() {
	// Create player with vehicle, add to shooter's team
}

Weapon_invisibility::Weapon_invisibility() {
	description = "Make vehicle invisible to others.";
}

void Weapon_invisibility::shoot() {
	this->owner->vehicle->polygon->shadestyle = POLYGON_SHADESTYLE_NODRAW;
}

Weapon_jammer::Weapon_jammer() {
	description = "Make nearby weapons, radio or remote controllers unusable.";
}

void Weapon_jammer::shoot() {
}

Weapon_laser::Weapon_laser() {
	description = "Shoot straight thin line of burning light.";
}

void Weapon_laser::shoot() {
	// Create new line
		//Linesegment2D* line;
}

Weapon_lifestealer::Weapon_lifestealer() {
	description = "Steal health from target.";
}

void Weapon_lifestealer::shoot() {
}

Weapon_mine::Weapon_mine() {
	description = "Leaves a mine behind that explodes if something touches it (or there's a blast near it).";
}

void Weapon_mine::shoot() {
}

Weapon_minimissile::Weapon_minimissile() {
	description = "Like missile, but many little missiles launched fast.";
}

void Weapon_minimissile::shoot() {
}

Weapon_minitorpedo::Weapon_minitorpedo() {
	description = "Like torpedo, but many little torpedoes launched fast.";
}

void Weapon_minitorpedo::shoot() {
}

Weapon_missile::Weapon_missile() {
	description = "Follows / targets to objects.";
}

void Weapon_missile::shoot() {
}

Weapon_moebius::Weapon_moebius() {
	description = "Warp from one level edge to the opposite, or go to the \"other side\" of the 2D world.";
}

void Weapon_moebius::shoot() {
}

Weapon_napalm::Weapon_napalm() {
	description = "Drop liquid that keeps burning a while.";
}

void Weapon_napalm::shoot() {
}

Weapon_painter::Weapon_painter() {
	description = "Recolor things, like ground, buildings or vehicles.";
}

void Weapon_painter::shoot() {
}

Weapon_phaser::Weapon_phaser() {
	description = "Go trough solid matter. Instant death if re-appear inside matter.";
}

void Weapon_phaser::shoot() {
}

Weapon_radialgun::Weapon_radialgun() {
	description = "Shoot to many directions at once, as a circle of bullets.";
}

void Weapon_radialgun::shoot() {
}

Weapon_radiationbomb::Weapon_radiationbomb() {
	description = "Generate invisible radiation that makes more damage the closer someone gets to it.";
}

void Weapon_radiationbomb::shoot() {
}

Weapon_random::Weapon_random() {
	description = "Random weapon each time when shooting.";
}

void Weapon_random::shoot() {
}

Weapon_rubberband::Weapon_rubberband() {
	description = "Shoot a stretchy harpoon. Second shoot releases the end part. Both endpoints stick to ground, vehicles and gadgets";
}

void Weapon_rubberband::shoot() {
}

Weapon_selfdestruct::Weapon_selfdestruct() {
	description = "Destroys the vehicle itself with a huge explosion.";
}

void Weapon_selfdestruct::shoot() {
}

Weapon_sizer::Weapon_sizer() {
	description = "Change vehicle size.";
}

void Weapon_sizer::shoot() {
	//this->owner->vehicle->polygon->scale();
}

Weapon_smokegrenade::Weapon_smokegrenade() {
	description = "Throw a grenade that creates smoke.";
}

void Weapon_smokegrenade::shoot() {
}

Weapon_smokescreen::Weapon_smokescreen() {
	description = "Create smoke around the vehicle.";
}

void Weapon_smokescreen::shoot() {
}

Weapon_soldier::Weapon_soldier() {
	description = "Drop a human soldier that has a gun.";
}

void Weapon_soldier::shoot() {
}

Weapon_spraygun::Weapon_spraygun() {
	description = "A bit like shotgun in other games.";
}

void Weapon_spraygun::shoot() {
}

Weapon_spycam::Weapon_spycam() {
	description = "Deploy a spying camera which can be monitored remotely.";
}

void Weapon_spycam::shoot() {
}

Weapon_station::Weapon_station() {
	description = "Drop an autonomous station that shoots with some weapon.";
}

void Weapon_station::shoot() {
}

Weapon_stinger::Weapon_stinger() {
	description = "Sword-like sharp spike.";
}

void Weapon_stinger::shoot() {
	// this->owner->vehicle->polygon->add_polygon(new Stinger());
}

Weapon_tangler::Weapon_tangler() {
	description = "Make target object attract projectiles.";
}

void Weapon_tangler::shoot() {
}

Weapon_teleport::Weapon_teleport() {
	description = "Teleport to random location or to previously set location.";
}

void Weapon_teleport::shoot() {
	this->owner->set_location(0, 0);
}

Weapon_termite::Weapon_termite() {
	description = "Sticky burning bomb.";
}

void Weapon_termite::shoot() {
}

Weapon_torch::Weapon_torch() {
	description = "Shoot fire with flame thrower.";
}

void Weapon_torch::shoot() {
}

Weapon_torpedo::Weapon_torpedo() {
	description = "Like missile, but under water.";
}

void Weapon_torpedo::shoot() {
}

Weapon_tracer::Weapon_tracer() {
	description = "Draws a trajectory curve with no damage.";
}

void Weapon_tracer::shoot() {
}

Weapon_tractorbeam::Weapon_tractorbeam() {
	description = "Pull stuff or lock into relative position/location. For example, a rocket can move a ship with this. If the movable object is heavy, many rockets with tractor beams can co-operate to move it.";
}

void Weapon_tractorbeam::shoot() {
}

Weapon_trajectories::Weapon_trajectories() {
	description = "Show tracers and vectors of all projectiles.";
}

void Weapon_trajectories::shoot() {
}

Weapon_turbo::Weapon_turbo() {
	description = "Increased max speed and acceleration for a while.";
}

void Weapon_turbo::shoot() {
	this->owner->vehicle->acceleration += this->level;
}

Weapon_watergun::Weapon_watergun() {
	description = "Shoot water.";
}

void Weapon_watergun::shoot() {
	//this->gameplay->level->add_land();
}

Weapon_wormhole::Weapon_wormhole() {
	description = "Create a wormhole.";
}

void Weapon_wormhole::shoot() {
}

Weapon_zoom::Weapon_zoom() {
	description = "Zoom closer or further";
}

void Weapon_zoom::shoot() {
}
