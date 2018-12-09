#include <iostream>
#include <string>

#include "misc.hpp"
#include "display.hpp"
#include "program.hpp"

void Display::check_window_size() {
	// Check if video mode (resolution) has changed (window is resized or fullscreen mode toggled)
	SDL_DisplayMode displaymode;
	for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
		int should_be_zero = SDL_GetCurrentDisplayMode(i, &displaymode);
		if (should_be_zero != 0) {
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
		}
		else {
			//SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, displaymode.w, displaymode.h, displaymode.refresh_rate);
			int w, h;
			SDL_GetWindowSize(this->sdlwindow, &w, &h);
			//SDL_Log("Display window size: %d x %d", w, h);
			//SDL_Log("Grapher old size: %d x %d", this->width, this->height);
			if (this->width != w or this->height != h) {
				this->width = w;
				this->height = h;
				this->has_resized = true;
				//log("changed");
			} //else log("no change");
		//log("-------------------------------");
		}
	}
}

bool Display::is_resized() {
	bool result = false;
	if (this->has_resized) {
		result = true;
		this->has_resized = false;
	}
	return result;
}

Display::Display() {
	this->coordinategrid = new Coordinategrid();
}

Display::~Display() {
	// FREE RESOURCES:
		SDL_DestroyWindow(this->sdlwindow);
		//delete this->sdlwindow;   // NOTE: Segfaults in Linux
		SDL_DestroyRenderer(this->sdlrenderer);
		//delete this->sdlrenderer;
}

bool Display::setup() {
	// Call this when creating or altering a display window
	// TODO: delete/modify old when calling this again (currently opens up a secondary window)
	// Set up SDL video:
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			log("ERROR while initializing SDL video:");
			log(SDL_GetError());
			this->works = false;
		}

	// Set up SDL display window:
		// FIXME:
		// - SDL_WINDOW_FULLSCREEN_DESKTOP acts the same as SDL_WINDOW_FULLSCREEN
		// - SDL_RENDERER_PRESENTVSYNC does nothing (at least it doesn't limit fps to monitor Hz)

		Uint32 flags = 0;
		if (this->vsync) flags = flags || SDL_RENDERER_PRESENTVSYNC;
		if (this->fullscreen)
			if (this->fullscreenmode_desktop) flags = flags || SDL_WINDOW_FULLSCREEN_DESKTOP;
			else flags = flags || SDL_WINDOW_FULLSCREEN;
		if (SDL_CreateWindowAndRenderer(this->width, this->height, flags, &this->sdlwindow, &this->sdlrenderer) != 0) {
			log("ERROR while creating SDL Window with Renderer:");
				log(SDL_GetError());
				SDL_Quit();
				this->works = false;
			}

		if (this->resizable_window) SDL_SetWindowResizable(this->sdlwindow, SDL_TRUE);

	//this->zbuf->set_size(width, height);

	// Show or hide mouse cursor:
		if (this->mousecursor_visible) SDL_ShowCursor(SDL_ENABLE);	// Default in SDL
		else SDL_ShowCursor(SDL_DISABLE);

		this->refresh();	// Clear possible jerky frame at the beginning

	this->timestamp_initial = SDL_GetTicks();

	return true;	// TODO
}

void Display::set_title(std::string title) {
	this->title = title;
	if (this->sdlwindow != nullptr) SDL_SetWindowTitle(this->sdlwindow, title.c_str());
}

void Display::set_width(int width) {
	this->width = width;
}

void Display::set_height(int height) {
	this->height = height;
}

void Display::set_desiredfps(unsigned char fps) {
	this->fps_desired = fps;
}

bool Display::set_fullscreen(bool state) {
	this->fullscreen = state;
	if (state)
		if (this->fullscreenmode_desktop) SDL_SetWindowFullscreen(this->sdlwindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else SDL_SetWindowFullscreen(this->sdlwindow, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(this->sdlwindow, 0);
	check_window_size();
	return true;	// TODO
}

bool Display::toggle_fullscreen() {
	if (this->fullscreen)
		SDL_SetWindowFullscreen(this->sdlwindow, 0);
	else
		if (this->fullscreenmode_desktop) SDL_SetWindowFullscreen(this->sdlwindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else SDL_SetWindowFullscreen(this->sdlwindow, SDL_WINDOW_FULLSCREEN);
	this->fullscreen =! this->fullscreen;
	check_window_size();
	return true;	// TODO
}

void Display::show_mousecursor(bool state) {
	SDL_ShowCursor(state);
	this->mousecursor_visible = state;
}

void Display::toggle_mousecursor() {
	if (this->mousecursor_visible) {
		SDL_ShowCursor(SDL_DISABLE);
		this->mousecursor_visible = false;
	} else {
		SDL_ShowCursor(SDL_ENABLE);
		this->mousecursor_visible = true;
	}
}

int Display::get_width() {
	return this->width;
}

int Display::get_height() {
	return this->height;
}

void Display::set_timestamp_start(unsigned int timestamp) {
	this->timestamp_start = timestamp;
}

void Display::set_timestamp_end(unsigned int timestamp) {
	this->timestamp_end = timestamp;
}

unsigned int Display::get_timestamp_start() {
	return this->timestamp_start;
}

unsigned int Display::get_timestamp_end() {
	return this->timestamp_end;
}

void Display::clearscreen() {
	// FIXME: Does not clear the screen
	// TODO: Move to grapher?
	SDL_RenderClear(this->sdlrenderer);
}

bool Display::refresh() {
	SDL_RenderPresent(this->sdlrenderer);
	this->framecounter++;

	//z_buf.reset();

	// Sleep and sync to desired FPS:
	if (this->works) {
		this->timestamp_end = SDL_GetTicks();
		//SDL_WM_SetCaption("DEMO | FPS: " << framecounter/((timestamp_atend - timestamp_atstart)/1000.0), NULL)
		//SDL_SetWindowTitle(this->sdlwindow, 1000.0/(this->timestamp_end - this->timestamp_start)));
		if (this->fps_desired != 0) {	// 0 = unlimited fps
			int delay = (1000.0/this->fps_desired) - (this->timestamp_end - this->timestamp_start);
			if (delay > 0) SDL_Delay(delay);
		}
		this->timestamp_start = SDL_GetTicks();
	}

	return this->works;
}

float Display::get_totalfps(){
	return this->framecounter/((this->timestamp_end - this->timestamp_initial)/1000.0);
}

float Display::get_lastfps(){
	return 1/((this->timestamp_end - this->timestamp_start)/1000.0);
}

unsigned char Display::get_desiredfps() {
	return this->fps_desired;
}

unsigned int Display::get_runtime() {
	// FIXME: This is not the same as total time program has been running
	return this->timestamp_end - this->timestamp_initial;
}

unsigned int Display::get_framecount() {
	return this->framecounter;
}

bool Display::save_screenshot() {
	/*
		// TODO: Generate filename: programname_programversion_timestamp.png
		unsigned int rmask, gmask, bmask, amask;
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
		#else
			rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
		#endif
			//if(SDL_SaveBMP(this->dispaly->sdlsurface, "filename.png") != 0)
				//log("ERROR: Cannot save screenshot image");
	*/
}

Coordinate2D Display::apply_coordinategrid(Coordinate2D coordinate) {
	Coordinate2D result;
	result.x = this->width / (this->coordinategrid->x_max - this->coordinategrid->x_min) * coordinate.x;
	result.y = this->height / (this->coordinategrid->y_max - this->coordinategrid->y_min) * coordinate.y;
	if (this->coordinategrid->centered) {
		result.x += this->width/2;
		result.y += this->height/2;
	}
	return result;
}

Coordinate3D Display::apply_coordinategrid(Coordinate3D coordinate) {
	Coordinate3D result;
	// TODO
	return result;
}
