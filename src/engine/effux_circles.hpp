/*
	SF-Engine
*/

// FIXME:
// - Even and odd circles are different width
// - Twitching motion (probably because of using integers)

#ifndef EFFUX_CIRCLES_HPP
	#define EFFUX_CIRCLES_HPP

	#include <vector>
	#include "effux.hpp"

	class EffuxCircles : public Effux {
		private:
			std::vector<bool> circles;	// Pixel map
			//Grapher *grapher;
		public:
			//SDL_Texture *texture = nullptr;
			uint32_t *pixels = nullptr;
			uint16_t width = 0;
			uint16_t height = 0;
			SDL_Rect *viewport = nullptr;  // Execute this area only
			unsigned char style = 1;
			EffuxCircles();
			void setup(SDL_Renderer* renderer, uint16_t width, uint16_t height);
			~EffuxCircles() override;
			void execute_OLD(uint32_t time);      // Delete after viewport implemented and performance benchmarked
			void execute(uint32_t time);
			//SDL_Texture* execute_rect(uint32_t time, SDL_Rect area) override;
	};

#endif // EFFUX_CIRCLES_HPP
