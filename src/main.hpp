#ifndef MAIN_HPP
	#define MAIN_HPP


	// INCLUDE FMOD:
	#if defined(WIN32) || defined(__WATCOMC__)
		#include <windows.h>
		#include <conio.h>
	#else
		#include "include/fmod/wincompat.h"
	#endif
		#include "include/fmod/fmod.h"
		#include "include/fmod/fmod_errors.h"


	#ifdef WITH_SDL
		#include <SDL/SDL.h>
	#endif

	#include "options.hpp"
	#include "graph.hpp"
	#include "graph3d.hpp"
	#include "control.hpp"

	// CONSTANTS:
		#define MSG_QUITERROR "Program aborted due to an error."

	// FUNCTIONS:
		//void setup_opengl();
		bool start_tracker_music(char *filename);
		bool read_configfile ();

#endif // MAIN_HPP
