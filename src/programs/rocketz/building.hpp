#ifndef BUILDING_HPP
	#define BUILDING_HPP

	#include "item.hpp"
	#include "human.hpp"

	class Building {
		// Stationary, does not move
		public:
			short lifeforce;
			std::vector<Item*> items_inside;
			std::vector<Human*> humans_inside;
			void explode();
	};

	class Shelter : public Building {
	};

#endif // BUILDING_HPP
