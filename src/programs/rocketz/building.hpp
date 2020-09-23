#ifndef BUILDING_HPP
	#define BUILDING_HPP

	#include <vector>
	#include "gamespace.hpp"

	// Forward declarations:
		class Item;
		class Human;

	class Building : public Gameblob {
		// Stationary, does not move
		public:
			std::vector<Item*> items_inside;
			std::vector<Human*> humans_inside;
			//Building();
			Building(Gameplay* gameplay);
			void explode();
	};

	//class Shelter : public Building {
	//};

#endif // BUILDING_HPP
