#ifndef LAND_HPP
	#define LAND_HPP

	#include <SDL.h>

	class Land {
		public:
			// bool flammable, meltable, steamable/vaporable, smokable (???)
			bool soft;
			bool sticky;
			bool slippery;
			bool burning;
			bool freezing;
			// If land is hard, it makes damage on impact and leaves a hole when blasted
			// If land is soft, it doesn't make damage on impact and falls straight down without leaving a hole when blasted
			short temperature;	// minus if cold, plus if hot
			SDL_Color color;
	};

	class Bubblegum : public Land {
		Bubblegum();
	};

	class Ice : public Land {
		Ice();
	};

	class Lava : public Land {
		Lava();
	};

	class Napalm : public Land {
		Napalm();
	};

	class Oil : public Land {
		Oil();
	};

	class Snow : public Land {
		Snow();
	};

	class Water : public Land {
		Water();
	};

#endif // LAND_HPP
