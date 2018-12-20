/*
	SF-Engine

	Derive game/demo specific code from here.
*/

/*
TODO:
- Options for program:
- uses fonts
- uses sound
*/

#ifndef PROGRAM_HPP
	#define PROGRAM_HPP

	#include <string>
	#include "inputdevices.hpp"

	// Forward declarations:
		class Audio;
		class Display;
		class Timeline;
		class Keyboard;
		class Mouse;
		class Joystick;


	class Program {
		protected:
			bool works = true;		// Change to false if something goes wrong
			//bool audio_works;
		public:
			std::string name = "SFE PROGRAM";
			std::string version = "0.0000";	// Never changes, just a default value indicating to engine user that no program has been made
			//TODO: icon
			bool with_sound = true;
			Audio *audio;
			bool mainloop_done = false;
			bool paused = false;
			Display *display;
			Keyboard *keyboard;
			Mouse *mouse;
			Joystick *joystick;
			Timeline *timeline;
			void get_events();
			Program();
			virtual ~Program();
			virtual bool init();
			virtual bool mainloop();
	};
	// TODO: parameters to enable/disable stuff (devices)

#endif // PROGRAM_HPP
