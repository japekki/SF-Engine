#ifndef RAIN_HPP
	#define RAIN_HPP

	#include <stdint.h>

	// Forward declarations:
		class Gameplay;

	#define RAIN_NONE 0
	#define RAIN_WATER 1
	#define RAIN_SNOW 2
	#define RAIN_LAND 3
	#define RAIN_LAVA 4
	#define RAIN_BOMB 5
	#define RAIN_ITEM 6
	#define RAIN_HUMAN 7

	class Rain {
		public:
			Rain(Gameplay* gameplay);
			~Rain();
			Gameplay* gameplay = nullptr;		// Or Level* or something...
			unsigned char type = RAIN_WATER;
			uint32_t intensity;
			void makerain();
			virtual void execute();
	};

#endif // RAIN_HPP
