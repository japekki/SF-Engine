#ifndef DEMO_HPP
	#define DEMO_HPP


	// INCLUDE FMOD:
	#if defined(WIN32) || defined(__WATCOMC__)
		#include <windows.h>
		#include <conio.h>
	#else
		#include "include/fmod/wincompat.h"
	#endif
		#include "include/fmod/fmod.h"
		#include "include/fmod/fmod_errors.h"


	#include "entity.hpp"
	#include "display.hpp"
	#include "sound.hpp"
	#include "timeline.hpp"

	bool demo_init();
	void demo_deinit();
	bool demo_mainloop();

	// FILE NAMES:
		//#define DATAPATH "../data/"
		#define DATAPATH ""
		// Pictures:
		//#define FILENAME_PIC DATAPATH "tunapa_small.png"

		// 3D models:
		#define FILENAME_OLIO1 DATAPATH "cube.obj"

		// Sounds:
		#define FILENAME_TRACKERSONG DATAPATH "megashwe.mod"
		#define FILENAME_AUDIO "../data/snd/kummitustalo.ogg"

		// Entitys:
		#define FILENAME_ENTITEETTI1 DATAPATH "ukko1.ent"

#endif // DEMO_HPP
