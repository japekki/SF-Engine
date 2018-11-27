#ifndef SPRITE_HPP
	#define SPRITE_HPP

	#include <vector>
	#include <SDL.h>

	// TODO: center/pivot point

	class Frame {
		//SDL_Surface *frame;		// TODO: SDL_Texture
		unsigned int duration;
		//unsigned int get_width();
		//unsigned int get_height();
		//void scale(float x, float y);
		//void scale(float multiplier);
		//void rotate(float angle);
	};

	class Sprite {
		public:
			std::vector<Frame> frames;
			unsigned short activeframe = 0;
			unsigned int playtimes;	// 0 = infinite
			bool backwards = false;
			//void start();
			//void stop();
			//void goto();
			//void scale(float x, float y);
			//void scale(float multiplier);
			//void rotate(float angle);
	};

	class Spritegroup {
		std::vector<Sprite> sprites;
	};

#endif // SPRITE_HPP
