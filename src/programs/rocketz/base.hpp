#ifndef BASE_HPP
	#define BASE_HPP

	#include <vector>
	#include "building.hpp"

	// Forward declarations:
		//class Point;

	class Base : public Building {
		// Player's base
		public:
			Base();
			~Base();
		// TODO: Many bases or just one, should player select where to (re-)spawn?
	};

#endif // BASE_HPP
