/*
	SF-Engine

	This file has routines for sound / music.
*/

// TODO:
// - Why changing the init flags does not affect anything
// - What is the difference between SDL_Init(SDL_INIT_AUDIO) and Mix_Init(flags)
// - When to call Mix_Quit()
// - Should a new Audio object be created for every sound file, for every sound instance, or just one Audio object for everything

#ifndef AUDIO_HPP
	#define AUDIO_HPP

	#include <SDL.h>
	#include <SDL_mixer.h>

	bool audio_init();

	class Audio {
		private:
			Mix_Music *audio = nullptr;
		public:
			Audio();
			~Audio();
			bool works = true;	// Set to false if something goes wrong
			bool load_file(const char *filename);
			void play();
			unsigned int get_timestamp();	// Timestamp of playing tune
			//unsigned short get_tracker_order()
			//unsigned short get_tracker_pattern()
			//unsigned short get_tracker_row()
			//void stop();	// pause
			//void jumpto(unsigned int timestamp);
	};

#endif // AUDIO_HPP
