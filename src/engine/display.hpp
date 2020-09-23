/*
	SF-Engine

	This file has routines for handling the display/monitor.
*/

/*
TODO:
- Set monitor Hz
- Multiple monitors
*/

#ifndef DISPLAY_HPP
	#define DISPLAY_HPP

	#include <SDL.h>
	#include <string>
	#include "grapher.hpp"

	class Display : public Grapher {
		private:
			bool has_resized = false;
		public:
		// VARIABLES:
			bool works = true;					// Change to false if something goes wrong
			std::string title;
			bool fullscreen = false;
			bool fullscreenmode_desktop = true;	// if true, keep desktop resolution, if false change resolution
			bool mousecursor_visible = true;
			bool vsync = false;
			bool resizable_window = true;
			bool minimized = false;				// True if window gets minimized
			bool with_fade = false;
			uint8_t fade_amount = 0;
			SDL_Color fade_color = SDLCOLOR_BLACK;
			uint32_t timestamp_initial = 0;		// when the display was initialized
			uint32_t timestamp_start = 0;		// timestamp at mainloop begin
			uint32_t timestamp_end = 0;			// timestamp at mainloop end
			float fps_last = 0;
			uint32_t framecounter = 0;
			unsigned char fps_desired = 10;		// Don't draw faster than this, 0 = unlimited
			//unsigned char fps_max = 0;		// Highest FPS momentarily achieved
			SDL_Window *sdlwindow = nullptr;
		// FUNCTIONS:
			Display();
			~Display();
			void check_window_size();			// get information of current display mode
			bool is_resized();					// Check if size has changed after last check
			void set_timestamp_start(uint32_t timestamp);
			void set_timestamp_end(uint32_t timestamp);
			uint32_t get_timestamp_start();
			uint32_t get_timestamp_end();
			void set_title(std::string title);
			void set_width(uint16_t width);
			void set_height(uint16_t height);
			void set_desiredfps(unsigned char fps);
			uint16_t get_width();
			uint16_t get_height();
			bool set_fullscreen(bool state);
			bool toggle_fullscreen();
			void show_mousecursor(bool state);
			void toggle_mousecursor();
			bool set_vsync(bool vsync);
			void clearscreen();
			virtual bool refresh();
			void load_icon(const char* filename);
			virtual bool setup();
			float get_totalfps();				// Total average fps from init to deinit
			float get_fps_last();				// Fps during last frame refresh
			unsigned char get_desiredfps();
			uint32_t get_runtime();
			uint32_t get_framecount();
			bool save_screenshot(std::string filename);
			//bool record_video();
			//bool render_video(uint8_t fps);
			void set_fade(uint8_t alpha);
	};

#endif // DISPLAY_HPP
