#ifndef EFFUX_CIRCLES_HPP
	#define EFFUX_CIRCLES_HPP

	#include <vector>
	#include "types.hpp"
	#include "display.hpp"

		class EffuxCircles {
			public:
				Grapher *grapher;
				SDL_Texture *sdltexture;
				Uint32 *pixels;
				unsigned short width;
				unsigned short height;
				std::vector<bool> circles;
				EffuxCircles(Grapher *grapher);
				~EffuxCircles();
				void execute(Uint32 time, bool both);
		};

#endif // EFFUX_CIRCLES_HPP
