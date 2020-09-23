#ifndef EFFUX_HPP
	#define EFFUX_HPP

	#include <SDL.h>

	// Forward declarations:
		//class Grapher;

	class Effux {
		public:
			SDL_Renderer* renderer = nullptr;
			SDL_Texture *texture = nullptr;
			uint16_t width = 0;
			uint16_t height = 0;
			//virtual void setup(Grapher *grapher) = 0;
			Effux();
			virtual ~Effux() = 0;
			//virtual void set_size(uint16_t width, uint16_t height);
			//virtual void execute(uint32_t time) = 0;	// Draw in full size to this->texture
			//virtual SDL_Texture* execute_rect(uint32_t time, SDL_Rect area);	// Return a partial drawing as texture
	};

#endif // EFFUX_HPP
