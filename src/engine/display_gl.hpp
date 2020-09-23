#ifndef DISPLAYGL_HPP
	#define DISPLAYGL_HPP

	#include <SDL.h>
	#include "display.hpp"

	class Display_GL : public Display {
		public:
			Display_GL();
			~Display_GL();
			SDL_GLContext glcontext;
			bool setup();
			bool refresh();
	};

#endif // DISPLAYGL_HPP
