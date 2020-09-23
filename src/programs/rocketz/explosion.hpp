#ifndef EXPLOSION_HPP
	#define EXPLOSION_HPP

	#include <vector>
	#include <stdint.h>

	// Forward declarations:
		class Gameplay;
		class Point;
		class Vector;

	class Explosion {
		public:
			Gameplay* gameplay;
			Explosion(Gameplay* gameplay);
			void create_sparks(Point location, Vector heading, uint16_t bullet_amount, float total_mass);
			//void execute();
	};

#endif // EXPLOSION_HPP
