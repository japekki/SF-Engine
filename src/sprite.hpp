// TODO: center/pivot point

#ifndef SPRITE_HPP
	#define SPRITE_HPP

	#include <vector>
	#include <SDL.h>

	class Frame {
		public:
			//SDL_Texture *texture;
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
		public:
			std::vector<Sprite> sprites;
	};

	class Voxel {	// 3D bitmap sprite
	};

#endif // SPRITE_HPP
