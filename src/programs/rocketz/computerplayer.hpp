// TODO:
// - Autopilot for human player, drones etc.

#ifndef COMPUTERPLAYER_HPP
	#define COMPUTERPLAYER_HPP

	#include "player.hpp"
	#include "gamespace.hpp"

	#define OBJECTIVE_NONE		0
	#define OBJECTIVE_FLEE		0b1
	#define OBJECTIVE_ATTACK	0b10
	#define OBJECTIVE_CHASE		0b100
	#define OBJECTIVE_AIM		0b1000
	#define OBJECTIVE_MANOUVER	0b10000
	#define OBJECTIVE_DODGE		0b100000
	#define OBJECTIVE_SHIELD	0b1000000

	#define OBJECTIVE_TEST1		0b100000000000000
	#define OBJECTIVE_TEST2		0b1000000000000000

	// Forward declarations:
		class Gameplay;
		class Level;

	class ComputerPlayer : public Player {
		private:
			uint16_t objective = OBJECTIVE_NONE;
			Point current_destination;
			Gameblob* target = nullptr;
			Point destination;		// Where to go to, if destination == location (human or vehicle) then no target destination
			//void choose_objective();
			void attack();
		public:
			//uint16_t difficulty = 0;	// How good the computer player is
				// Difficulty affects:
				// - length of arrays
				// - latency for reacting
				// - accuracy variable for shooting, maneuvering, trajectory calculations etc.
				// - enable/disable some routines
			Level* level = nullptr;
			ComputerPlayer(Gameplay* gameplay) : Player(gameplay) {};
			//~Computerplayer();
			Gameblob* nearest_enemy();
			Gameblob* nearest_friend();
			Base* nearest_homebase();
			Gameblob* nearest_enemy_building();
			Gameblob* nearest_enemy_vehicle();
			Gameblob* nearest_item();
			float damage_balance(float radius);	// Check if explosion covers more enemies or allies, minus = more damage to allies, positive = more damage to enemies
			void maneuver(Point target_location);
			void dodge(Gameblob* object);
			void execute() override;
	};

#endif // COMPUTERPLAYER_HPP
