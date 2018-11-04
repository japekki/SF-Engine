#ifndef DISPLAY_HPP
	#define DISPLAY_HPP

	#include "graph3d.hpp"
	#include <SDL/SDL.h>

	// TODO:
	// - Support for multiple displays (like, demo running on big screen and settings panel on monitor)
	// - Polar coordinate system (angle and distance)

	class Display {
		private:
			int x_min;
			int x_max;
			int y_min;
			int y_max;
			int width;
			int height;
		public:
			unsigned int framecounter;
			int delay;
			Uint32 timestamp_atstart;   // mainloop
			Uint32 timestamp_atend;     // mainloop
			bool resizable;
			Uint16 fps_lockto;
			Uint8 fps_max;
			Uint8 bpp;  // Bits per pixel: 8, 16, 24, 32
			bool fullscreen;
			SDL_Surface *sdlsurface;  // turha jos sama ku screen?
			Zbuf z_buf;
			Uint32 clearcolor;
			bool centered;
			Display();
			~Display();
			void set_name(char* name);
			int get_x_min();
			int get_x_max();
			int get_y_min();
			int get_y_max();
			int get_width();
			int get_height();
			void set_x_min(int new_x_min);
			void set_x_max(int new_x_max);
			void set_y_min(int new_y_min);
			void set_y_max(int new_y_max);
			void set_width(int new_width);
			void set_height(int new_height);
			void clearscreen();
			bool refresh();
			bool setup();
			//#ifdef WITH_OPENGL
				// bool load_GLSL(string filename); // Load and compile a shader file
			//#endif
	};

#endif // DISPLAY_HPP
