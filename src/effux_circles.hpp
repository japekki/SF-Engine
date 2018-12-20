/*
	SF-Engine
*/

// FIXME:
// - Even and odd circles are different width
// - Twitching motion (probably because of using integers)

#ifndef EFFUX_CIRCLES_HPP
	#define EFFUX_CIRCLES_HPP

	#include <vector>
	#include "types.hpp"
	#include "grapher.hpp"

	class EffuxCircles {
		private:
			Grapher *grapher;
		public:
			SDL_Texture *sdltexture;
			Uint32 *pixels = nullptr;
			unsigned short width;
			unsigned short height;
			std::vector<bool> circles;
			EffuxCircles(Grapher *grapher);
			~EffuxCircles();
			void execute(Uint32 time, Uint8 style);	// Draw to this->sdltexture
	};

#endif // EFFUX_CIRCLES_HPP
