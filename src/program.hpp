#ifndef PROGRAM_HPP
	#define PROGRAM_HPP

	#include <SDL_mixer.h>
	#include "audio.hpp"
	#include "display.hpp"
	#include "inputdevices.hpp"
	#include "timeline.hpp"

	// FILE NAMES:
		#define DATAPATH "../data/"
		// Pictures:
			//#define FILENAME_PIC1 DATAPATH "picture.png"

		// 3D models:
			//#define FILENAME_OBJECT1 DATAPATH "model.obj"

		// Sounds:
			//#define FILENAME_AUDIO1 DATAPATH "audio.ogg"

	class Program {
		protected:
			bool works = true;		// Change to false if something goes wrong
			bool audio_works;
		public:
			std::string name = "SFE TEMPLATE PROGRAM";
			std::string version = "0.0000";
			bool with_sound = true;
			bool mainloop_done = false;
			bool paused = false;
			Display *display;
			Keyboard *keyboard;
			Mouse *mouse;
			Joystick *joystick;
			Timeline *timeline;
			void handle_events();
			Program();
			virtual ~Program();
			virtual bool init();
			virtual bool mainloop();
	};
	// TODO: parameters to enable/disable stuff (devices)

#endif // PROGRAM_HPP
