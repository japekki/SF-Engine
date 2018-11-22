#ifndef DISPLAY_HPP
	#define DISPLAY_HPP

	#include <SDL.h>
	#include <string>
	#include "geom.hpp"
	#include "grapher.hpp"

	class Display : public Grapher {
		private:
			std::string title;
			bool fullscreen = false;
			bool vsync = false;
			unsigned int timestamp_initial;	// when the display was initialized
			unsigned int timestamp_start = 0;   // timestamp at mainloop begin
			unsigned int timestamp_end;     // timestamp at mainloop end
			unsigned int framecounter = 0;
			unsigned char fps_desired = 1;	// Don't draw faster than this
			unsigned char fps_max;			// Highest FPS momentarily achieved
		public:
		// Variables:
			bool works = true;			// Change to false if something goes wrong
			SDL_Window *sdlwindow;
			SDL_Renderer *sdlrenderer;
			//SDL_Surface* sdlsurface;	// Inherited from class Grapher
			SDL_Texture *sdltexture;
			//int delay;
			//bool resizable;
			//unsigned int clearcolor;
		// Functions:
			Display();
			~Display();
			void set_timestamp_start(unsigned int timestamp);
			void set_timestamp_end(unsigned int timestamp);
			unsigned int get_timestamp_start();
			unsigned int get_timestamp_end();
			void set_title(std::string title);
			void set_width(int width);
			void set_height(int height);
			void set_desiredfps(unsigned char fps);
			int get_width();
			int get_height();
			bool set_fullscreen(bool fullscreen);
			bool toggle_fullscreen();
			bool set_vsync(bool vsync);
			void clearscreen();
			bool refresh();
			bool setup();
			float get_totalfps();		// Total average fps from init to deinit
			float get_lastfps();		// Fps during last frame refresh
			unsigned char get_desiredfps();
			unsigned int get_runtime();
			unsigned int get_framecount();
			Coordinate2D apply_coordinategrid(Coordinate2D coordinate);
			Coordinate3D apply_coordinategrid(Coordinate3D coordinate);
	};

#endif // DISPLAY_HPP
