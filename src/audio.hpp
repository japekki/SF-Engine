/*
	SF-Engine

	This file has routines for sound / music.
*/

/*
TODO:
- Why changing the init flags does not affect anything
- What is the difference between SDL_Init(SDL_INIT_AUDIO) and Mix_Init(flags)
- When to call Mix_Quit()
*/

#ifndef AUDIO_HPP
	#define AUDIO_HPP

	#include <SDL.h>
	#include <SDL_mixer.h>

	class Audio {
		public:
			Audio();
			~Audio();
			bool works = true;	// Set to false if something goes wrong
			Mix_Music* load_music(const char *filename);
			Mix_Chunk* load_sound(const char *filename);
			void play(Mix_Music* music, int loops);
			void play(Mix_Chunk* sound, int loops);
			unsigned int get_timestamp();	// Timestamp of playing tune
			//unsigned short get_tracker_order()
			//unsigned short get_tracker_pattern()
			//unsigned short get_tracker_row()
			//void stop();	// pause
			//void jumpto(unsigned int timestamp);
	};

#endif // AUDIO_HPP
