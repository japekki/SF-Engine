/*
	SF-Engine

	This file has routines for sound / music.
*/

// TODO:
// - Why changing the init flags does not affect anything
// - What is the difference between SDL_Init(SDL_INIT_AUDIO) and Mix_Init(flags)
// - When to call Mix_Quit()
// - Should a new Audio object be created for every sound file, every sound instance, or just one Audio object

/*
FLAGS:
	MIX_INIT_FLAC
	MIX_INIT_MOD
	MIX_INIT_MP3
	MIX_INIT_OGG
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
	int flags = 0;
	//int flags = MIX_INIT_MP3;
	int result = 0;
	if (flags != (result = Mix_Init(flags))) {
		this->works = false;
		printf("Could not initialize mixer (result: %d).\n", result);
		log("ERROR: Mix_Init:");
		log(Mix_GetError());
		//exit(1);
	}
}

Audio::~Audio() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Audio::~Audio()");
	#endif // WITH_DEBUGMSG
	Mix_FreeMusic(this->audio);
	//while(Mix_Init(0))
		//Mix_Quit();
}

bool Audio::load_file(char *filename) {
	#ifdef WITH_DEBUGMSG
		debugmsg("Audio::load_mp3()");
		//debugmsg(filename);
	#endif // WITH_DEBUGMSG

	if (this->works) {
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
