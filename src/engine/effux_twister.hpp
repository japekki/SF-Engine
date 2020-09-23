#ifndef EFFUX_TWISTER_HPP
	#define EFFUX_TWISTER_HPP

	#include <SDL.h>

	class EffuxTwister {
		short horizontal_twist = 0;
		short vertical_twist = 0;
		void execute(SDL_Texture* texture);
	};

#endif // EFFUX_TWISTER_HPP
