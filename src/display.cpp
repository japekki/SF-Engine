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
	// TODO: better way to do this:
		this->set_grid(this->grid.x_min, this->grid.y_min, this->grid.x_max, this->grid.x_max);
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
}

Display::~Display() {
	// FREE RESOURCES:
		SDL_DestroyWindow(this->sdlwindow);
		//delete this->sdlwindow;	// FIXME: Segfaults in Linux
		SDL_DestroyRenderer(this->sdlrenderer);
		//delete this->sdlrenderer;
}

void Display::load_icon(const char* filename) {
	SDL_Surface *surface;
	surface = this->load_surface(filename);
	SDL_SetWindowIcon(this->sdlwindow, surface);
	SDL_FreeSurface(surface);
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
		// Clear possible garbage:
			SDL_SetRenderDrawColor(this->sdlrenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(this->sdlrenderer);

		if (this->resizable_window) SDL_SetWindowResizable(this->sdlwindow, SDL_TRUE);

	// Show or hide mouse cursor:
		if (this->mousecursor_visible) SDL_ShowCursor(SDL_ENABLE);	// Default in SDL
		else SDL_ShowCursor(SDL_DISABLE);

		this->refresh();	// Clear possible garbage at the beginning

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
	SDL_RenderClear(this->sdlrenderer);
}

bool Display::refresh() {
	// TODO: Find out if this is done by default in OS / SDL:
		//if (!this->minimized) SDL_RenderPresent(this->sdlrenderer);	// Don't draw if window is minimized
		SDL_RenderPresent(this->sdlrenderer);

	this->framecounter++;

	// Sleep and sync to desired FPS:
	if (this->works) {
		this->timestamp_end = SDL_GetTicks();
		//SDL_WM_SetCaption("FPS: " << framecounter/((timestamp_atend - timestamp_atstart)/1000.0), NULL)
		//SDL_SetWindowTitle(this->sdlwindow, 1000.0/(this->timestamp_end - this->timestamp_start)));
		if (this->fps_desired != 0) {	// 0 = unlimited fps
			int delay = (1000.0/this->fps_desired) - (this->timestamp_end - this->timestamp_start);
			if (delay > 0) SDL_Delay(delay);
		}
		int current_timestamp = SDL_GetTicks();
		//this->lastfps = 1000.0/(current_timestamp - this->timestamp_start);	// NOTE: does not work if FPS >= 1000
		this->timestamp_start = current_timestamp;
	}

	return this->works;
}

float Display::get_totalfps() {
	return this->framecounter/((this->timestamp_start - this->timestamp_initial)/1000.0);
}

float Display::get_lastfps(){
	return this->lastfps;
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
		// TODO: Generate filename: program_version_timestamp_framecounter.png
		unsigned int rmask, gmask, bmask, amask;
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
		#else
			rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
		#endif
			//if(SDL_SaveBMP(this->dispaly->sdlsurface, "filename.png") != 0)
				//log("ERROR: Cannot save screenshot image");
	*/
	return false;	// TODO
}

/*
// Show FPS:
	SDL_Rect rect_fps;
	SDL_Texture* text_fps;
	std::ostringstream ss;
	ss << int(this->display->get_lastfps());
	//printf("%f\n", this->display->get_lastfps());
	std::string fps(ss.str());
	text_fps = this->display->create_textline_texture("FPS: " + fps, this->font_modenine_tiny, {0xff, 0xff, 0xff});
	SDL_QueryTexture(text_fps, NULL, NULL, &rect_fps.w, &rect_fps.h);
	rect_fps.x = 0;	//this->display->width - rect_fps.w;
	rect_fps.y = 0;	//this->display->height - rect_fps.h;
	this->display->draw_texture(text_fps, rect_fps);
	SDL_DestroyTexture(text_fps);
*/
