#ifndef EFFUX_CIRCLES_HPP
	#define EFFUX_CIRCLES_HPP

	#include <vector>
	#include <math.h>
	#include "types.hpp"
	#include "display.hpp"

		class EffuxCircles {
			public:
				Grapher *grapher;
				SDL_Surface *sdlsurface;
				unsigned short width;
				unsigned short height;
				std::vector<bool> circles;
				EffuxCircles(Grapher *grapher);
				void draw(Uint32 time, bool both);
		};

#endif // EFFUX_CIRCLES_HPP
