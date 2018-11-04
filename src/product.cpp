/*
	SF-Engine

	This file has demo/game specific routines.
*/

#include <math.h>

#include "product.hpp"
#include "control.hpp"
#include "globals.hpp"
#include "entity.hpp"
#include "scene.hpp"
#include "sound.hpp"
#include "graph.hpp"
#include "timeline.hpp"

// Include some old archived demo routines:
	#include "effux_archive.hpp"

	// Variables from the engine we want direct access from our demo code:
		Timeline timeline;
		extern Display monitor;
		extern Sound sound;
		extern bool with_sound;
		extern bool mainloopdone;
		extern bool demo_restarts;
		extern bool demo_paused;

	// Demo specifig variables:

bool demo_init() {
	// Returns true if everything went ok
	bool result = true;   // Change to false if something goes wrong

	// SET UP DISPLAY DEVICE:
		monitor.set_width(640);
		monitor.set_height(480);
		monitor.bpp = 32;
		monitor.fps_lockto = 40;
		monitor.centered = true;
		monitor.fullscreen = false;
		monitor.resizable = false;
		if (!monitor.setup()) result = false;
		monitor.set_name("DEMO");

	// SET UP AUDIO DEVICE:
		with_sound = true;

	// SET UP INPUT DEVICES:
		#ifdef WITH_JOYSTICK
			Joystick joystick(0);   // 0 for the first joystick available, 1 for the second etc..
		#endif
		#ifdef WITH_MIDI
			midi_init();
		#endif

	// SET UP DEMO OPTIONS:
		demo_restarts = false;
		// build options in "options.hpp"

	// LOAD AND PRECALCULATE STUFF:
		// Set up colors:
			generate_hsl_table(monitor.sdlsurface);
				colorRed = SDL_MapRGB(monitor.sdlsurface->format, 255, 0, 0);
				colorGreen = SDL_MapRGB(monitor.sdlsurface->format, 0, 255, 0);
				colorBlue = SDL_MapRGB(monitor.sdlsurface->format, 0, 0, 255);
				colorWhite = SDL_MapRGB(monitor.sdlsurface->format, 255, 255, 255);
				colorBlack = SDL_MapRGB(monitor.sdlsurface->format, 0, 0, 0);
				colorYellow = SDL_MapRGB(monitor.sdlsurface->format, 255, 255, 0);
				colorCyan = SDL_MapRGB(monitor.sdlsurface->format, 0, 255, 255);
				colorOrange = SDL_MapRGB(monitor.sdlsurface->format, 255, 127, 0);
				colorViolet = SDL_MapRGB(monitor.sdlsurface->format, 255, 0, 255);
				colorBrown = SDL_MapRGB(monitor.sdlsurface->format, 164, 101, 38);
				colorGrey = SDL_MapRGB(monitor.sdlsurface->format, 127, 127, 127);


		// Luo scene/obut:
			//Scene scene1();
			//extern Entity testiobjekti;
			//testiobjekti.loadfromfile("../data/cube.obj");
			//testiobjekti.surface = monitor.sdlsurface;
			//testiobjekti.polygonshadestyle = POLYGON_SHADESTYLE_WIREFRAME;
			//scene1.add_entity(olio1);

		// Init effuxes:
			extern EffuxRinkula effux_rinkula;
			effux_rinkula.init(monitor.get_width(), monitor.get_height());


		// LOAD IMAGE FILE:
				/*
				pic_tunapa = load_image("../data/img/tunapa_small.png");
				if (pic_tunapa == NULL) {
				  cout << MSG_QUITERROR;
				  result=false;
				}
				*/

	// LOAD MUSIC FILE:
		/*
		if (sound.load_audiofile(FILENAME_AUDIO)) {
			// START MUSIC:
			if (!sound.play_audio(0)) {
				result=false;
			}
		}
		*/

	//if (!sound.load_trackersong(FILENAME_TRACKERSONG)) with_sound = false;
	//if (demo_restarts) FMUSIC_SetLooping(tracker_song, FSOUND_LOOP_OFF);

	return result;
}

void demo_deinit()
{
	// FREE ALLOCATED RESOURCES:
		// delete testiobjekti;
}

bool demo_mainloop()
{
	bool result = true; // Muutetaan falseksi jos joku menee vikaan
	timeline.init();
	while (!mainloopdone and result) {
		monitor.timestamp_atstart = SDL_GetTicks(); // TODO: Relocate
		poll_events();
		if (!demo_paused) {
			timeline.sync(SYNC_CLOCK);
			monitor.clearscreen();

			// Draw graphics:

			extern Entity testiobjekti;
			#ifdef WITH_JOYSTICK
				extern Joystick joystick;
			#endif // WITH_JOYSTICK
			extern Timeline timeline;
			extern EffuxRinkula effux_rinkula;
			//effux2(timeline.get_position()/5.0, monitor.sdlsurface);
			//effux_chessplane(timeline.get_position(), monitor.sdlsurface);

			effux_rinkula.draw(timeline.get_position()/5.0, true, monitor.sdlsurface);
			//effux_geomelem(timeline.get_position()/5.0, monitor.sdlsurface);

			//testiobjekti.pushgeom();
			//testiobjekti.scale(joystick.axis3 / 100);
			//testiobjekti.rotatevertexarray(PI/32768*joystick.axis0, PI/32768*joystick.axis1, PI/32768*joystick.axis2);
			//testiobjekti.draw3d_polygon();
			//testiobjekti.popgeom();
			// Blit our image onto the monitor:
			if (!monitor.refresh()) result = false;
		}

	} // while (!mainloopdone and result)
	 return result;
}

/* TODO:
	- Lisää scene-olioihin obuja, tee kamera(t),
	- SDL_Surface GL-tekstuuriksi
*/
