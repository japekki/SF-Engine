#include <stdio.h>
#include <iostream>

#include "sound.hpp"

using namespace std;

Sound::Sound() {
	init();
}

Sound::~Sound() {
}

bool Sound::init() {
	channels.resize(1);
	extern bool with_sound;
	if (with_sound){
		if (FSOUND_GetVersion() < FMOD_VERSION){
			printf("FMOD: Error: You are using the wrong DLL version! You should be using FMOD %.02f\n", FMOD_VERSION);
			with_sound = false;
		}
		printf("INIT");
		//FSOUND_SetOutput(FSOUND_OUTPUT_ALSA);
		if (!FSOUND_Init(44100, 64, 0)){
			printf("FMOD: %s\n", FMOD_ErrorString(FSOUND_GetError()));
			with_sound = false;
		}

	}
}

void Sound::deinit() {
}

bool Sound::load_audiofile(char *filename) {
	bool result;

	audio = FSOUND_Sample_Load(FSOUND_FREE, filename, FSOUND_NORMAL, 0, 0);
	if (audio==NULL) {
		cout << "FMOD: Error loading audio file " << filename << endl;
		result=false;
	}
	else {
		cout << "FMOD: Loaded audio file " << filename << endl;
		result=true;
	}

	return result;
}

bool Sound::load_trackersong(char *filename) {
	tracker_song = FMUSIC_LoadSong(filename);
	if (!tracker_song){
		printf("FMOD: %s\n", FMOD_ErrorString(FSOUND_GetError()));
		return false;
	}
}

bool Sound::play_trackersong() {

	printf("FMOD: Playing tracker song called: %s\n", FMUSIC_GetName(tracker_song));
	FMUSIC_PlaySong(tracker_song);
	// TODO: return
	return true;

}

bool Sound::play_audio(int channel) {
	bool result;
	channels.at(channel) = FSOUND_PlaySound(FSOUND_FREE, audio);
	if (channels.at(channel) == -1) {
		cerr << "FMOD: Unable to play sound." << endl;
		result=false;
	}
	else {
		cout << "FMOD: Playing audio file." << endl;
		result=true;
	}
	return result;

}

	//if (loopdemo) FSOUND_Sample_SetMode(musa, FSOUND_LOOP_OFF);
	//else FSOUND_Sample_SetMode(musa, FSOUND_);

	//FMUSIC_SetZxxCallback(tracker_musa, music_zxx_callback);    // Returns: false/0, true/1
	//FMUSIC_SetInstCallback(tracker_musa, music_instr10_callback, 10);

bool Sound::play_hz(int channel, int hz) {
/*
	bool result;
	result = FSOUND_SetFrequency(FSOUND_FREE, hz);
	return result;
*/
}
