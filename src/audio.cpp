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

Audio::Audio() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		log("Failed to init Audio.");
		this->works = false;
	}
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
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
	Mix_AllocateChannels(16);
}

Audio::~Audio() {
	//while(Mix_Init(0))
		Mix_Quit();
}

Mix_Music* Audio::load_music(const char *filename) {
	Mix_Music* music;

	if (this->works) {
		music = Mix_LoadMUS(filename);
		if(!music) {
			this->works = false;
			log("Error loading music file:");
			log(Mix_GetError());
		}
	}
	return music;
}

Mix_Chunk* Audio::load_sound(const char *filename) {
	Mix_Chunk* sound;

	if (this->works) {
		sound = Mix_LoadWAV(filename);
		if(!sound) {
			this->works = false;
			log("Error loading music file:");
			log(Mix_GetError());
		}
	}
	return sound;
}

void Audio::play(Mix_Music* audio, int loops) {
	Mix_PlayMusic(audio, loops);
}

void Audio::play(Mix_Chunk* sound, int loops) {
	Mix_PlayChannel(-1, sound, 0);
}
