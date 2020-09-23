#ifndef GAUGE_HPP
	#define GAUGE_HPP

	// Progress bar style graphical line meter

	#include <stdint.h>

	// Forward declarations:
		class Gameplay;

	#define ORIENTATION_HORIZONTAL 0
	#define ORIENTATION_VERTICAL 1

	// TEST:
	class Container {
		public:
			uint32_t width;
			uint32_t height;
	};

	class Gauge : public Container {
		public:
			Gameplay* gameplay;
			unsigned char orientation = ORIENTATION_HORIZONTAL;
			uint16_t maximum = 0;
			uint16_t value;
			Gauge(Gameplay* gameplay);
			void draw(int x, int y);
	};

#endif // GAUGE_HPP
