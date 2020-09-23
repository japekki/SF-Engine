#include "misc.hpp"
#include "computerplayer.hpp"
#include "gameplay.hpp"
#include "gamespace.hpp"
#include "human.hpp"
#include "vehicle.hpp"
#include "geometry.hpp"
#include "base.hpp"

void ComputerPlayer::attack() {
	// Shoot at enemy
	// TODO:
	// - Avoid making big blasts if at risk of getting hit by self
	// - How to attack? Which weapon?
	//calculate heading (and power?)
	//if (objective == OBJECTIVE_AIM)
		// if good to shoot now:
			// shoot at target
			// objective = OBJECTIVE_NONE
		// else
			// keep aiming (rotating, accelerating, braking, walking/jumping/swimming/falling/waiting)
}

Base* ComputerPlayer::nearest_homebase() {
	Base* nearest_base = nullptr;
	float nearest_distance = 0;

	if (team->bases.size() > 1) {
		nearest_base =  team->bases[0];
		nearest_distance = get_distance(this->get_location(), team->bases[0]->location);
	}
	if (team->bases.size() > 2) {
		for (uint32_t b = 1; b < team->bases.size(); b++) {
			float distance = get_distance(team->bases[b]->location, this->get_location());
			if ( distance < nearest_distance) {
				nearest_base = team->bases[b];
				nearest_distance = distance;
			}
		}
	}
	return nearest_base;
}

Gameblob* ComputerPlayer::nearest_friend() {
	return nullptr;
}

Gameblob* ComputerPlayer::nearest_enemy() {
	// TODO:
	// - get information only from visible range (including spycam, radar etc.)
	// - get fooled like human player would (like if enemy is invisible or has disguised)
	// - Not all blobs have owner. Use some other way to check if blob belongs to enemy or not.
	// - Search only for particular type of blobs (like don't try to shoot towards enemy bullet etc.)
	// - Rogues

	Gameblob* nearest_enemy = nullptr;
	float nearest_distance = gameplay->gamespace->width/2 + 1;	// blob cannot be outside space

	for (uint32_t t=0; t<gameplay->teams.size(); t++) {
		if (gameplay->teams[t] != this->team) {
			for (uint32_t p=0; p<gameplay->teams[t]->players.size(); p++) {
				Player* player = gameplay->teams[t]->players[p];
				float distance = get_distance(player->get_location(), this->get_location());
				if (distance < nearest_distance) {
					nearest_enemy = player->human;
					nearest_distance = distance;
				}
			}
		}
	}
	return nearest_enemy;
}

//void ComputerPlayer::choose_objective() {
//}

void ComputerPlayer::maneuver(Point target_location) {
	// calculate angle and throttle to reach location
	//if (human->inside_vehicle)
		// check vehicle type
		// Calculate rocket steering maneuvers to go forwards to a specific location:
			// TODO: note gravity and attract/repel
}

void ComputerPlayer::dodge(Gameblob* object) {
}

void ComputerPlayer::execute() {
	if (human->health > 0 and vehicle->health > 0) {
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
		- flee to safe distance if making a big explosion (or if it seems something nearby is about to explode)
		- calculate trajectories (makes tracer and Weapon_trajectories obsolete?)
		- get out of vehicle to sabotage unoccupied vehicles or gadgets and get back to vehicle
		- steal vehicle if own is destroyed
		- guess what enemy is doing (like pursuing a power-up and possibly give up pursuing the same item if it seems that the enemy will get it first)
		- human and vehicle routines
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

	// Choose objective:

	//#define DISTANCE_LIMIT	20		// longest distance considered as nearby
	//Blob *nearest_enemy = this->nearest_enemy();
	//Blob *nearest_friend = this->nearest_friend();

	// TODO: Get also distance of nearest enemy

	// if (distance of nearest enemy < DISTANCE_LIMIT)
		// if high health:
			//objective = OBJECTIVE_ATTACK;
			//target = nearest_enemy;
		// if low health:
			//objective = OBJECTIVE_FLEE;
			//target = nearest_homebase;
	// else
		// fool around

	// TODO
	// chase

		objective = OBJECTIVE_TEST1;

		float angle;
		switch (objective) {
			case OBJECTIVE_FLEE:
				// Find nearest base:
					//this->nearest_base();
				// Find nearest health item:
					//this->nearest_health();
				// If base is closer than item, go towards base, else towards item
				break;

			case OBJECTIVE_ATTACK:
				// Attack nearest enemy object (vehicle, building...)
				this->attack();
				break;

			case OBJECTIVE_CHASE:
				//this->goto(this->target_object->location);
				//this->attack(this->target_object);
				break;

			case OBJECTIVE_TEST1:
			{

				// Try to face upwards:
					/*
					angle = vehicle->angle;
					if (angle <= 0.8*PI)
						angle = 0.1;
					else if (angle > 0.8*PI and angle < 1.2*PI)
						angle = 0.1 * ((rand() % 3) - 1);
					else if (angle >= 1.2*PI)
						angle = -0.1;
					vehicle->rotate(angle);
					*/

					float angle;
					Gameblob* target_blob = nearest_enemy();	// FIXME
					Point target_point;
					if (target_blob != nullptr)
						target_point = target_blob->location;
					else
						target_point = Point(0, 0);

					angle = geom::angle(this->get_location(), target_point);

					if (vehicle->location.x > target_point.x)
						angle += PIPER2;
					else
						angle -= PIPER2;

					if (vehicle->angle < angle)
						vehicle->rotate_cw();
					else
						vehicle->rotate_ccw();

				// Try to maintain center in space:
					//if ((vehicle->angle >= PIPER2 and vehicle->angle >= -PI)) {
						// Vehicle is facing up
						if (vehicle->location.y < 0) {
							// Vehicle is above center
							if (rand() % 4 == 0)
								vehicle->accelerate();
						} else {
							// Vehicle is below center
							if (rand() % 3)
								vehicle->accelerate();
						}
						//else if (vehicle->location.y > 0)
					//} else {
						// Vehicle is facing down
					//}

				// Shoot at random times:
					//for (uint32_t i=0; i<vehicle->weapons.size(); i++)
					//	if (rand() % 100 == 0)
					//		this->shoot(i);
					if (rand() % 10 == 0) this->shoot(rand() % vehicle->weapons.size());

					// Abandon vehicle if it has less health than human:
						//if (human->inside_vehicle and (human->health > vehicle->health))
						//human->get_out_from_vehicle();
				break;
			}

			case OBJECTIVE_TEST2:
				break;
		}
	}
}
