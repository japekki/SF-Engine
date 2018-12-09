#include "ai.hpp"

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
