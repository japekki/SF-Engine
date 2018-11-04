#ifndef GLOBALS_HPP
	#define GLOBALS_HPP
	#include <SDL/SDL.h>

	/*
	// INCLUDE FMOD:
	#if defined(WIN32) || defined(__WATCOMC__)
		#include <windows.h>
		#include <conio.h>
	#else
		#include "include/fmod/wincompat.h"
	#endif
		#include "include/fmod/fmod.h"
		#include "include/fmod/fmod_errors.h"
	*/

	void init_globals();
	void deinit_globals();
	void generate_hsl_table(SDL_Surface *sdlsurface);
	//void generate_sin_table();

#endif // GLOBALS_HPP
