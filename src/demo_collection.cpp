#include "demo_collection.hpp"
#include <vector>
#include <SDL/SDL.h>
#include "globals.hpp"
//#include "display.hpp"
//#include "timeline.hpp"
#include "graph.hpp"
#include "product.hpp"

extern Display monitor;

void effux_rainbow(Uint32 time, SDL_Surface *sdlsurface) {
// Koordinaatisto = false
	extern Uint32 hsltable[16][16][16];
	ColorHSL colorhsl;
		colorhsl.l = 0.5;
		//colorhsl.s = sin(time/1000.0);
		//colorhsl.h = 1.0/res_x*x;
		colorhsl.s = 1.0;
	ColorRGB colorrgb;
	Uint32 color;
	int x, y;
	for (y=0; y<sdlsurface->h; y++) {
		for (x=0; x<sdlsurface->w; x++) {
			color = hsltable [int(16.0/sdlsurface->w*x)] [int(16.0/sdlsurface->h*y)] [time & 15] ;
			draw_pixel_noclip(x, y, color, sdlsurface);
		}
	}
}





	bool image_to_cubearray(SDL_Surface *sdlsurface, float scale, float ratio) {
	// Create an array of 3d cubes colored by the pixels of an image/sdl_surface
	// scale is the length of cubes width, height or depth
	// if ratio is 0, cubes are 0 in size
	// if ratio is 1, no space is left between the cubes
		float r,g,b;
		for (int x=0; x<sdlsurface->w; x++) {
			for (int y=0; y<sdlsurface->h; y++) {
				Uint32 color = get_pixel_clip(x, y, sdlsurface);
				r = 1.0/256*(color >> 16);
				g = 1.0/256*(color >> 8);
				b = 1.0/256*(color >> 0);
				generate_cube(scale*x, scale*y, 0, ratio, r, g, b);
			}
		}
	}



