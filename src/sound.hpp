#ifndef SOUND_HPP
	#define SOUND_HPP

	#ifdef __cplusplus
		#include <cstdlib>
	#else
		#include <stdlib.h>
	#endif

	#include <vector>
	#include <string>


	// INCLUDE FMOD:
	#if defined(WIN32) || defined(__WATCOMC__)
		#include <windows.h>
		#include <conio.h>
	#else
		#include "include/fmod/wincompat.h"
	#endif
		#include "include/fmod/fmod.h"
		#include "include/fmod/fmod_errors.h"

	using namespace std;

	class Sound {
		private:
			FSOUND_SAMPLE *audio;
			FMUSIC_MODULE *tracker_song;
			std::vector<int> channels;
		public:
			//bool with_sound;
			Sound();
			~Sound();
			bool init();
			void deinit();
			bool load_audiofile(char *filename);
			bool load_trackersong(char *filename);
			bool play_trackersong();
			bool play_audio(int channel);
			bool play_hz(int channel, int hz);
	};

#endif // SOUND_HPP
