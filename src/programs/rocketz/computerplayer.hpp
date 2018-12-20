#ifndef AI_HPP
	#define AI_HPP

	#include "player.hpp"

	#define OBJECTIVE_NONE 0
	#define OBJECTIVE_FLEE 1
	#define OBJECTIVE_ATTACK 2
	//#define OBJECTIVE_CHASE 3

	// Forward declarations:
		class Gameobject;
		class Gameplay;
		class Level;

	class ComputerPlayer : public Player {
		private:
			Point* current_destination;
			unsigned char current_objective = OBJECTIVE_NONE;
			void choose_objective();
			void attack(Gameobject* target);
			// TODO: fuel
		public:
			//unsigned short difficulty = 0;	// How good the computer player is
				// Difficulty affects:
				// - length of arrays
				// - latency for reacting
				// - accuracy variable for shooting, maneuvering, trajectory calculations etc.
				// - enable/disable some routines
			Level* level;
			ComputerPlayer(Gameplay* gameplay) : Player(gameplay) {};
			Gameobject* nearest_enemy();
			Gameobject* nearest_enemy_building();
			Gameobject* nearest_enemy_vehicle();
			Gameobject* nearest_item();
			float damage_balance(float radius);	// Check if explosion covers more enemies or allies, minus = more damage to allies, positive = more damage to enemies
			void maneuver(Point* target_location);
			void dodge(Gameobject* object);
			void execute() override;
	};

#endif // AI_HPP
