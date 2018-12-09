/*
	SF-Engine

	This file has routines for handling the display/monitor.
*/

/*
TODO:
- Set monitor Hz
- Check if desktop fullscreen mode scales 1:1 / is it slower than just a windows of that size
*/

#ifndef DISPLAY_HPP
	#define DISPLAY_HPP

	#include <SDL.h>
	#include <string>
	#include "geom.hpp"
	#include "grapher.hpp"

	class Display : public Grapher {
		private:
			bool has_resized = false;
		public:
		// VARIABLES:
			std::string title;
			bool fullscreen = false;
			bool mousecursor_visible = true;
			bool vsync = false;
			bool resizable_window = true;
			unsigned int timestamp_initial;		// when the display was initialized
			unsigned int timestamp_start = 0;   // timestamp at mainloop begin
			unsigned int timestamp_end;     	// timestamp at mainloop end
			unsigned int framecounter = 0;
			unsigned char fps_desired = 1;		// Don't draw faster than this, 0 = unlimited
			unsigned char fps_max;				// Highest FPS momentarily achieved
			bool fullscreenmode_desktop = true;	// if true, keep desktop resolution, if false change resolution
			SDL_Window *sdlwindow = nullptr;
			void check_window_size();			// get information of current display mode
			bool is_resized();					// Check if size has changed after last check
			//SDL_Renderer *sdlrenderer;		// Inherited from class Grapher (?)
			//SDL_Texture *sdltexture;			// Inherited from class Grapher (?)
			//bool resizable;
			//Color clearcolor;
		// FUNCTIONS:
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
			bool set_fullscreen(bool state);
			bool toggle_fullscreen();
			void show_mousecursor(bool state);
			void toggle_mousecursor();
			bool set_vsync(bool vsync);
			void clearscreen();
			bool refresh();
			bool setup();
			float get_totalfps();				// Total average fps from init to deinit
			float get_lastfps();				// Fps during last frame refresh
			unsigned char get_desiredfps();
			unsigned int get_runtime();
			unsigned int get_framecount();
			bool save_screenshot();
			Coordinate2D apply_coordinategrid(Coordinate2D coordinate);
			Coordinate3D apply_coordinategrid(Coordinate3D coordinate);
	};

#endif // DISPLAY_HPP
