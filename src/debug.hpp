#ifndef DEBUG_HPP
	#define DEBUG_HPP

	#include <SDL/SDL.h>

	// Debugging messages:
		//#define debug_errormsg_something "Something went wrong. Here's the debugging information:\n"

	void SDL_SurfaceInfo(char * name, SDL_Surface *sdlsurface);

#endif // DEBUG_HPP
