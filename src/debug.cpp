#ifdef DEBUG
	#include "debug.hpp"

	#include <SDL/SDL.h>

	void SDL_SurfaceInfo(char * name, SDL_Surface *sdlsurface) {
		printf("Surface %s: w:%d h:%d bpp:%d\n", name, sdlsurface->w, sdlsurface->h, sdlsurface->format->BitsPerPixel);
	}

#endif
