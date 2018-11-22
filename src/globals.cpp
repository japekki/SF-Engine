/*
	SF-Engine

	This file has global variables and routines to calculate them, generate lookup tables etc.
*/

/*
#include <vector>
#include <SDL.h>
#include <math>

// GLOBALS:

// Index: 6 bit for hue, 1 bit for saturation, 1 bit for lightness
unsigned int hsltable[16][16][16]; // 16*16*16 for hsl

void generate_hsl_table(SDL_Surface *sdlsurface) {
	ColorHSL tmp_hsl;
	ColorRGB tmp_rgb;
	for (int l = 0; l<16; l++)
	{
		for (int s = 0; s<16; s++)
		{
			for (int h=0; h<16; h++)
			{
				tmp_hsl.h = 1.0/16*h;
				tmp_hsl.s = 1.0/16*s;
				tmp_hsl.l = 1.0/16*l;
				tmp_rgb = HSLtoRGB(tmp_hsl);
				hsltable[h][s][l] = SDL_MapRGB(sdlsurface->format, 255*tmp_rgb.r, 255*tmp_rgb.g, 255*tmp_rgb.b);
			}
		}
	}
}

void generate_hsl_table() {
		//generate_hsl_table(SDL_Surface *sdlsurface);
}

#ifdef WITH_MIDI
	//unsigned char Param1; // Knob position tjsp.
	//unsigned char Param2;
	//unsigned char Param3;
#endif

void init_globals() {
}

void deinit_globals() {
}

*/
