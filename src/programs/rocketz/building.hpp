#ifndef BUILDING_HPP
	#define BUILDING_HPP

	#include <vector>
	#include "gameobject.hpp"

	// Forward declarations:
		class Item;
		class Human;

	class Building : public Gameobject {
		// Stationary, does not move
		public:
			short health;
			std::vector<Item*> items_inside;
			std::vector<Human*> humans_inside;
			void explode();
	};

	class Shelter : public Building {
	};

#endif // BUILDING_HPP
