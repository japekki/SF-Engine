// NOTE: Looks different on high and low fps

#ifndef EFFUX_MOTIONBLUR_HPP
	#define EFFUX_MOTIONBLUR_HPP

	#include <SDL.h>

	// Forward declarations:
		class Grapher;

	class EffuxMotionblur {
		Grapher* grapher;
		SDL_Texture* lastframe;	// Blend with this
		EffuxMotionblur(Grapher* grapher);
		~EffuxMotionblur();
		void execute(SDL_Texture* sdltexture);
	};

#endif // EFFUX_MOTIONBLUR_HPP
