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

	#include <vector>
	#include <string>
	#include <SDL.h>
	#include <SDL_mixer.h>

	class Audio {
		public:
			Audio(bool state, int flags);
			~Audio();
			bool enabled = true;
			bool works = true;	// Set to false if something goes wrong
			Mix_Music* load_music(const std::string filename);
			void free_music(Mix_Music *music);
			Mix_Chunk* load_sound(const std::string filename);
			void play(Mix_Music* music, int loops);
			void play(Mix_Chunk* sound, int loops);
			//void stop();	// pause
	};

	//struct Tune {
	//	Mix_Music* music;
	//	const char* filename;
	//};

	class Jukebox {
		// Playlist of music files
		public:
			Audio* audio = nullptr;
			std::vector<std::string> playlist;
			uint16_t songs_played = 0;
			Mix_Music* current_tune = nullptr;
			short current_index = 0;
			Jukebox();
			Jukebox(Audio* audio);
			Jukebox(Audio* audio, const std::string music_folder);
			~Jukebox();
			void create_playlist(const std::string music_folder);
			bool start();
			bool stop();
			bool next_tune();
			bool previous_tune();
			bool random_tune();
			bool first_tune();
			bool last_tune();
			bool restart_tune();
			bool this_tune(short index);
	};

#endif // AUDIO_HPP
