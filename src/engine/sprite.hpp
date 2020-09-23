#ifndef SPRITE_HPP
	#define SPRITE_HPP

	#include <vector>
	#include <SDL.h>

	class Frame {
		public:
			//SDL_Texture *texture;
			uint32_t duration;
			//uint32_t get_width();
			//uint32_t get_height();
			//void scale(float x, float y);
			//void scale(float multiplier);
			//void rotate(float angle);
	};

	class Sprite {
		public:
			std::vector<Frame*> frames;
			uint16_t activeframe = 0;
			uint32_t playtimes;	// 0 = infinite
			bool backwards = false;
			//void start();
			//void stop();
			//void goto();
			//void scale(float x, float y);
			//void scale(float multiplier);
			//void rotate(float angle);		// TODO: center/pivot point
	};

	class Spritegroup {
		public:
			std::vector<Sprite*> sprites;
	};

	class Voxel {	// 3D bitmap sprite
	};

#endif // SPRITE_HPP
