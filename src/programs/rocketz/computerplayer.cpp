//#include "misc.hpp"
#include "computerplayer.hpp"
#include "gameplay.hpp"
#include "gameobject.hpp"
#include "human.hpp"
#include "vehicle.hpp"
#include "geom.hpp"

//ComputerPlayer::~AI() {
//}

void ComputerPlayer::attack(Gameobject* target) {
	// Shoot at enemy
}

Gameobject* ComputerPlayer::nearest_enemy() {
	// TODO:
	// - get information only from visible range (including spycam, radar etc.)
	// - get fooled like human player would (like if enemy is invisible or has disguised)
	unsigned int lowest_distance = 0xffffffff;
	Gameobject* nearest_object = nullptr;
	for (unsigned int i=0; i<this->gameplay->gameobjects.size(); i++)
		if (this->gameplay->gameobjects.at(i)->owner != this) {
			float distance = get_distance(this->gameplay->gameobjects.at(i)->get_location(), this->get_location());
			if (distance < lowest_distance) {
				lowest_distance = distance;
				nearest_object = this->gameplay->gameobjects.at(i);
			}
		}
	return nearest_object;
}

void ComputerPlayer::choose_objective() {
	// Check if one should flee:
		unsigned char health;
		if (this->human->inside_vehicle)
			health = this->human->health;
		else
			health = this->vehicle->health;
		if (health < 127)
			this->current_objective = OBJECTIVE_FLEE;

	// Check if one should abandon vehicle:
		if (this->human->inside_vehicle and (this->human->health > this->vehicle->health))
			this->human->get_out_from_vehicle();
}

void ComputerPlayer::maneuver(Point* target_location) {
	//if (this->human->inside_vehicle)
		// check vehicle type
		// Calculate rocket steering maneuvers to go forwards to a specific location:
			// TODO: note gravity and attract/repel
}

void ComputerPlayer::dodge(Gameobject* object) {
}

void ComputerPlayer::execute() {
/*
	TODO:
	- decision making balancer:
		- pursue game mode goal/objective
		- need for power-ups
		- need for money
		- need for items
		- flee or attack
		- use gadgets
		- select good weapons and shields (like if enemy has a laser, then use mirror)
	- if enemy building near, attack it instead of vehicles or humans
	- flee to safe distance if making a big explosion
	- calculate trajectories (makes tracer and Weapon_trajectories obsolete?)
	- get out of vehicle to sabotage unoccupied vehicles or gadgets and get back to vehicle
	- steal vehicle if own is destroyed
	- guess what enemy is doing (like pursuing a power-up and possibly give up pursuing the same item if it seems that the enemy will get it first)
*/
/*
	select nearest enemy
	calculate trajectories for weapon and target
	shoot at the enemy

	select nearest power-up
	go towards power-up

	if health below half:
		check if health power-up available
		go towards power-up
		shoot at nearby enemies

	calculate trajectories
	do extra maneuvers or use shield/weapon to avoid getting hit
*/
	this->choose_objective();
	switch (this->current_objective) {
		case OBJECTIVE_FLEE:
			//'Find nearest base:
				//this->nearest_base();
			// Find nearest health item:
				//this->nearest_health();
			// If base is closer than item, go towards base, else towards item
			break;
		case OBJECTIVE_ATTACK:
			// Attack nearest enemy object (vehicle, building...)
			this->attack(this->nearest_enemy());
			break;
		//case OBJECTIVE_CHASE:
		//	break;
	}
	// TESTS:
		this->vehicle->move();
		this->vehicle->rotate(rand());
		//this->attack();
}
