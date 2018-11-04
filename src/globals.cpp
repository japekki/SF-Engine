/*
	SF-Engine

	This file has global variables and routines to calculate them, generate lookup tables etc.
*/

#include <vector>
#include <SDL/SDL.h>
#include <math.h>

#include "globals.hpp"
#include "options.hpp"
#include "control.hpp"
#include "math.hpp"
#include "graph.hpp"
#include "graph3d.hpp"
#include "display.hpp"
#include "scene.hpp"
#include "control.hpp"
#include "sound.hpp"
#include "effux_archive.hpp"


// GLOBAALIT MUUTTUJAT:
	Uint32 timestamp_demostart;
	Display monitor;
	Sound sound;
	bool with_sound = true;
	Keyboard keyboard;
	bool demo_restarts;
	bool mainloopdone;
	bool demo_paused;
	FMUSIC_MODULE *tracker_song;
	Entity testiobjekti;
	#ifdef WITH_JOYSTICK
		Joystick joystick(0);
	#endif
	#ifdef WITH_MOUSE
		Mouse mouse;
	#endif

// Effux-kohtaiset:
	EffuxRinkula effux_rinkula;

// Index: 6 bit for hue, 1 bit for saturation, 1 bit for lightness
Uint32 hsltable[16][16][16]; // 16*16*16 for hsl

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
	//Uint8 Param1; // Knob position tjsp.
	//Uint8 Param2;
	//Uint8 Param3;
#endif

//#ifdef WITH_OPENGL
//    bool gpuvertexbuffer;
//#else
	Zbuf zbuf;
//#endif

// Color constants for bpp in use:
	Uint32 colorRed;
	Uint32 colorGreen;
	Uint32 colorBlue;
	Uint32 colorWhite;
	Uint32 colorBlack;
	Uint32 colorYellow;
	Uint32 colorCyan;
	Uint32 colorOrange;
	Uint32 colorViolet;
	Uint32 colorBrown;
	Uint32 colorGrey;

void init_globals() {
	//#ifdef WITH_OPENGL
		//gpuvertexbuffer = false;    // TODO: Auto detect
	//#else
	//#endif
}

void deinit_globals() {
}

