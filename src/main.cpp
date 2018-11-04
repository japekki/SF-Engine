/*
	SF-Engine

	This is the main file where the program starts.
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <math.h>

#ifdef __cplusplus
	#include <cstdlib>
#else
	#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//#ifdef WITH_OPENGL
//    #include <GL/gl.h>
//#endif

#include "main.hpp"
#include "misc.hpp"
#include "control.hpp"
#include "globals.hpp"
#include "graph.hpp"

#include "entity.hpp"
#include "scene.hpp"
#include "display.hpp"
#include "timeline.hpp"
#include "product.hpp"

#include "sound.hpp"
using namespace std;

// GLOBAALIT MUUTTUJAT (m‰‰ritelty muualla):
	extern bool mainloopdone;
	extern Display monitor;
	extern Uint32 hsltable[256];
	extern Sound sound;
	extern FMUSIC_MODULE *tracker_song;
		// FMOD CALLBACKS:
			extern bool time_to_act;
		// CONTROL:
			#ifdef WITH_MOUSE
				extern Mouse mouse;
			#endif
			#ifdef WITH_JOYSTICK
				extern Joystick Joystick;
			#endif

int main ( int argc, char** argv ) {
	extern bool with_sound;
	bool demo_paused;
	/*
	#ifdef WITH_OPENGL
		extern bool gpuvertexbuffer;
		gpuvertexbuffer = false; // TODO
	#endif
	*/
	cout << "Program started." << endl;
	atexit(SDL_Quit);   // Free resources

	// INITIALIZATIONS
		init_globals();
		mainloopdone = false;
		//int phase = 0;

	if (!demo_init()) {
		cout << MSG_QUITERROR << endl;
		exit (EXIT_FAILURE);
	}
	extern Uint32 timestamp_demostart;
	timestamp_demostart = SDL_GetTicks();
	if (!demo_mainloop()) {
		cout << MSG_QUITERROR << endl;
	}

	// EXIT PROGRAM:
		// FREE RESOURCES:
		demo_deinit();
		if (with_sound){
			FMUSIC_FreeSong(tracker_song);
			FSOUND_Close();
		}
			//delete Testiscene;
		//#ifndef WITH_OPENGL
		// TODO: vapauta kaikki surfacet
			//SDL_FreeSurface(pic...);
		//#endif
		deinit_globals();

	printf("Program finished.\nRun time: %i ms, Frames drawn: %i, Overall fps: %f, Desired fps: %i\n", monitor.timestamp_atend - timestamp_demostart, monitor.framecounter, monitor.framecounter/((monitor.timestamp_atend - timestamp_demostart)/1000.0), monitor.fps_lockto);
	return EXIT_SUCCESS;
}

bool read_configfile () {
	bool result = true; // Change to false if something goes wrong
	string filename = "demo.cfg";
	string parameter, value;

	cout << "Loading parameters from file " << filename << ": ";

	string line;
	ifstream conf_file(filename.c_str(), ios::binary);   // Default?
	if (conf_file.is_open()) {
		while (!conf_file.eof()) {
			getline (conf_file, line);
			if (line.length() > 3) {
				// delete spaces and tabs
				// split string with '=' as delimiter
				/*
				switch (parameter) {
					case "res_x":
						//monitor.set_width(value);
						break;
					case "res_y":
						//monitor.set_height(value);
						break;
					case "bpp":
						//monitor.bpp=value;
						break;
					case "fps":
						//monitor.fps=value;
						break;
					case "fullscreen":
						//monitor.fullscreen=value;
						break;
					case "looping":
						//
						break;
					case "sound":
						//sound.with_sound=value;
						break;
					}
				*/
			}
		}
		result = conf_file.is_open();
		conf_file.close();
	} //if (conf_file.is_open())
	else {
		cerr << "ERROR reading config file " << filename << endl;
		result = false;
	}
	/*
	vector<string> testi;
	string testi2;
	testi = split("moi heii jeejee jaajaa", ' ');
	cout << testi[1] << endl;

	monitor.resizable = ;
	monitor.fps_lockto = ;
	*/
	return result;
}
