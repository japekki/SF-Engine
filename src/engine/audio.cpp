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

Audio::Audio(bool state, int flags) {
	if (state) {
		if (SDL_Init(SDL_INIT_AUDIO) < 0) {
			log("Failed to init Audio.");
			this->works = false;
		}
		Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
		int flags = 0;
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
	this->enabled = state;
}

Audio::~Audio() {
	if (this->enabled) {
		while(Mix_Init(0))
		Mix_Quit();
	}
}

Mix_Music* Audio::load_music(const std::string filename) {
	if (this->enabled) {
		Mix_Music* music = nullptr;

		if (this->works) {
			music = Mix_LoadMUS(filename.c_str());
			if(!music) {
				log("Error loading music file: " + filename);
				log(Mix_GetError());
			}
		}
		return music;
	} else
		return nullptr;
}

void Audio::free_music(Mix_Music *music) {
	Mix_FreeMusic(music);	// FIXME: Segfaults if music not good
	music = nullptr;		// TODO: Test if the original pointer is changed
}

Mix_Chunk* Audio::load_sound(const std::string filename) {
	if (this->enabled) {
		Mix_Chunk* sound = nullptr;

		if (this->works) {
			sound = Mix_LoadWAV(filename.c_str());
			if(!sound) {
				log("Error loading music file:");
				log(Mix_GetError());
			}
		}
		return sound;
	} else
		return nullptr;
}

void Audio::play(Mix_Music* audio, int loops) {
	if (this->enabled)
		Mix_PlayMusic(audio, loops);
}

void Audio::play(Mix_Chunk* sound, int loops) {
	if (this->enabled)
		Mix_PlayChannel(-1, sound, loops);
}

Jukebox::Jukebox() {
}

Jukebox::Jukebox(Audio* audio) {
	this->audio = audio;
}

Jukebox::Jukebox(Audio* audio, const std::string music_folder) {
	this->audio = audio;
	this->create_playlist(music_folder);
}

Jukebox::~Jukebox() {
	playlist.clear();
	//delete playlist;
}

void Jukebox::create_playlist(const std::string music_folder) {
	playlist.clear();
	playlist = getAllFilesInDir(music_folder);
	current_index = 0;
}

bool Jukebox::start() {
	if (playlist.size() > 0) {
		current_tune = audio->load_music(playlist[current_index]);
		//log("Jukebox playing: " + playlist[current_index]);
		audio->play(current_tune, 0);
		songs_played++;
	}
	return true;	// TODO
}

bool Jukebox::stop() {
	if (current_tune != nullptr)
		audio->free_music(current_tune);
	current_tune = nullptr;
	return true;	// TODO
}

bool Jukebox::first_tune() {
	this->stop();
	current_index = 0;
	this->start();
	return true;	// TODO
}

bool Jukebox::last_tune() {
	this->stop();
	current_index = playlist.size()-1;
	this->start();
	return true;	// TODO
}

bool Jukebox::next_tune() {
	this->stop();
	current_index++;
	if (current_index > playlist.size()-1)
		current_index = 0;
	this->start();
	return true;	// TODO
}

bool Jukebox::previous_tune() {
	this->stop();
	current_index--;
	if (current_index < 0)
		current_index = playlist.size()-1;
	this->start();
	return true;	// TODO
}

bool Jukebox::random_tune() {
	this->stop();
	if (playlist.size() > 0) {
		current_index = rand() % playlist.size();
		this->start();
		return true;
	}
	return false;
}

bool Jukebox::restart_tune() {
	this->stop();
	this->start();
	return true;
}

bool Jukebox::this_tune(short index) {
	this->stop();
	current_index = index;
	this->start();
	return true;
}
