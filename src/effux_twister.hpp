/*
TODO:
- Shadow
*/

#ifndef EFFUX_TWISTER_HPP
	#define EFFUX_TWISTER_HPP

	#include <SDL.h>

	class EffuxTwister {
		Uint8 horizontal_twist = 0;
		Uint8 vertical_twist = 0;
		void execute(SDL_Texture* sdltexture);
	};

#endif // EFFUX_TWISTER_HPP
