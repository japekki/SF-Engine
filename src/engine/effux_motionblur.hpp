// NOTE: Looks different on high and low fps

#ifndef EFFUX_MOTIONBLUR_HPP
	#define EFFUX_MOTIONBLUR_HPP

	#include <SDL.h>

	// Forward declarations:
		class Grapher;

	class EffuxMotionblur {
		Grapher* grapher = nullptr;
		SDL_Texture* previous_frame = nullptr;	// Blend with this
		EffuxMotionblur(Grapher* grapher);
		~EffuxMotionblur();
		void execute(SDL_Texture* texture);
	};

#endif // EFFUX_MOTIONBLUR_HPP
