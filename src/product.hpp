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
			//#define FILENAME_PIC1 DATAPATH "picture.png"

		// 3D models:
			//#define FILENAME_OBJECT1 DATAPATH "model.obj"

		// Sounds:
			#define FILENAME_TRACKERSONG1 DATAPATH "tracker.mod"
			#define FILENAME_AUDIO1 "../data/snd/audio.ogg"

		// Entities:
			//#define FILENAME_ENTITY1 DATAPATH "entity.ent"

#endif // DEMO_HPP
