#ifndef BASE_HPP
	#define BASE_HPP

	#include <vector>
	#include "building.hpp"

	// Forward declarations:
		class Player;
		class Team;

	class Base : public Building {
		// Team's base
		public:
			Team* owner_team = nullptr;
			Base(Gameplay* gameplay);
			Base(Gameplay* gameplay, Team* owner_team);
			~Base();
			void draw();
			void get_invaded(Team* new_team);
	};

#endif // BASE_HPP
