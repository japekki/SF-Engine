/*
	SF-Engine

	This file has routines for sound / music.
*/

#include "options.hpp"
#include "audio.hpp"
#include "misc.hpp"

bool audio_init() {
	bool works = true;
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		log("Failed to init Audio.");
		works = false;
	}
	return works;
}

Audio::Audio() {
}

Audio::~Audio() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Audio::~Audio()");
	#endif // WITH_DEBUGMSG
	Mix_FreeMusic(this->audio);
}

bool Audio::load_file(char *filename) {
	#ifdef WITH_DEBUGMSG
		debugmsg("Audio::load_mp3()");
		//debugmsg(filename);
	#endif // WITH_DEBUGMSG
	int result = 0;
	int flags = MIX_INIT_MP3;
	if (flags != (result = Mix_Init(flags))) {
		this->works = false;
		printf("Could not initialize mixer (result: %d).\n", result);
		log("ERROR: Mix_Init:");
		log(Mix_GetError());
		//exit(1);
	} else {
		Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 640);
		this->audio = Mix_LoadMUS(filename);
		if(!this->audio) {
			this->works = false;
			log("Error loading music file:");
			log(Mix_GetError());
		}
	}
	return this->works;
}

void Audio::play() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Audio::play()");
	#endif // WITH_DEBUGMSG
	Mix_PlayMusic(this->audio, -1);
}

