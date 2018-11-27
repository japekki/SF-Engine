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
			bool load_file(char *filename);
			void play();
			//void stop();
	};

#endif // AUDIO_HPP
