#include <iostream>
#include <string>
#include "misc.hpp"
#include "display.hpp"
#include "program.hpp"

Display::Display() {
	//log("Display::Display()");
}

Display::~Display() {
	SDL_DestroyWindow(sdlwindow);
	//sdlwindow = nullptr;
	SDL_DestroyRenderer(renderer);
	//renderer = nullptr;
	//log("Display::~Display()");
}

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
			}
		}
	}
}

bool Display::is_resized() {
	if (this->has_resized) {
		this->has_resized = false;
		return true;
	}
	return false;
}

void Display::load_icon(const char* filename) {
	SDL_Surface *surface;
	surface = grapher::load_surface(filename);
	SDL_SetWindowIcon(sdlwindow, surface);
	SDL_FreeSurface(surface);
}

bool Display::setup() {
	// Call this when creating or altering a display window
	// TODO: delete/modify old when calling this again (currently opens up a secondary window)

		//SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, WinWidth, WinHeight, WindowFlags);
		//assert(Window);

	// SET UP SDL VIDEO:
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {			// FIXME: Don't initialize SDL here, other initialization flags may be needed (joystick etc.)
			log("ERROR while initializing SDL video:");
			log(SDL_GetError());
			this->works = false;
		}

	// SET UP SDL DISPLAY WINDOW:

		uint32_t flags = 0;

		// Set vsync:
			if (vsync) flags = SDL_RENDERER_PRESENTVSYNC;
			// FIXME:
			// - SDL_RENDERER_PRESENTVSYNC does nothing (at least it doesn't limit fps to monitor Hz)

		// Set fullscreen:
			if (fullscreen) {
				if (fullscreenmode_desktop)
					flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
				else
					flags = flags | SDL_WINDOW_FULLSCREEN;
			}

		// Create window:
			if (SDL_CreateWindowAndRenderer(width, height, flags, &sdlwindow, &renderer)) {
				log("ERROR while creating SDL Window with Renderer:");
				log(SDL_GetError());
				SDL_Quit();
				this->works = false;
			}

	// FIXME:
		// - SDL_WINDOW_FULLSCREEN_DESKTOP acts the same as SDL_WINDOW_FULLSCREEN when creating a window
		// - SDL_RENDERER_PRESENTVSYNC does nothing when creating a window
		if (fullscreen)
			set_fullscreen(true);
		//if (this->vsync) this->set_vsync(true);

	// CLEAR POSSIBLE CARBAGE:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		this->refresh();

		//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

	// SET OTHER WINDOW PROPERTIES:
		// Show or hide mouse cursor:
			if (mousecursor_visible)
				SDL_ShowCursor(SDL_ENABLE);	// Default in SDL
			else
				SDL_ShowCursor(SDL_DISABLE);

		// Set window resizable:
			// FIXME: Window cannot be resized
			if (this->resizable_window) SDL_SetWindowResizable(sdlwindow, SDL_TRUE);

	timestamp_initial = SDL_GetTicks();

	return true;	// TODO
}

void Display::set_title(std::string title) {
	this->title = title;
	if (sdlwindow != nullptr) SDL_SetWindowTitle(sdlwindow, title.c_str());
}

void Display::set_width(uint16_t width) {
	this->width = width;
	has_resized = true;
}

void Display::set_height(uint16_t height) {
	this->height = height;
	has_resized = true;
}

void Display::set_desiredfps(unsigned char fps) {
	this->fps_desired = fps;
}

bool Display::set_vsync(bool vsync) {
	//if (vsync) SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	this->vsync = vsync;
	return true;	// TODO
}

bool Display::set_fullscreen(bool state) {
	this->fullscreen = state;
	if (state)
		if (this->fullscreenmode_desktop)
			SDL_SetWindowFullscreen(sdlwindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			SDL_SetWindowFullscreen(sdlwindow, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(sdlwindow, 0);
	//check_window_size();
	has_resized = true;		//
	return true;	// TODO
}

bool Display::toggle_fullscreen() {
	if (this->fullscreen)
		SDL_SetWindowFullscreen(sdlwindow, 0);
	else {
		if (this->fullscreenmode_desktop)
			SDL_SetWindowFullscreen(sdlwindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			SDL_SetWindowFullscreen(sdlwindow, SDL_WINDOW_FULLSCREEN);
	}
	this->fullscreen =! this->fullscreen;
	//check_window_size();
	has_resized = true;		//
	return true;	// TODO
}

void Display::show_mousecursor(bool state) {
	SDL_ShowCursor(state);
	mousecursor_visible = state;
}

void Display::toggle_mousecursor() {
	if (mousecursor_visible) {
		SDL_ShowCursor(SDL_DISABLE);
		mousecursor_visible = false;
	} else {
		SDL_ShowCursor(SDL_ENABLE);
		mousecursor_visible = true;
	}
}

uint16_t Display::get_width() {
	return this->width;
}

uint16_t Display::get_height() {
	return this->height;
}

void Display::set_timestamp_start(uint32_t timestamp) {
	this->timestamp_start = timestamp;
}

void Display::set_timestamp_end(uint32_t timestamp) {
	this->timestamp_end = timestamp;
}

uint32_t Display::get_timestamp_start() {
	return this->timestamp_start;
}

uint32_t Display::get_timestamp_end() {
	return this->timestamp_end;
}

void Display::clearscreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

bool Display::refresh() {
	// TODO: Find out if this is done by default in OS / SDL:
		//if (!this->minimized) SDL_RenderPresent(renderer);	// Don't draw if window is minimized
			//SDL_SetTextureAlphaMod(this->texture_fade, fade_alpha);

	// Fade:
		if (with_fade) {
			SDL_Rect rectangle;
			rectangle.x = 0;
			rectangle.y = 0;
			rectangle.w = this->get_width();
			rectangle.h = this->get_height();
			SDL_SetRenderDrawColor(renderer, fade_color.r, fade_color.g, fade_color.b, fade_amount);
			//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(renderer, &rectangle);
			//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		}

	SDL_RenderPresent(renderer);

	framecounter++;

	// Sleep and sync to desired FPS:
	if (this->works) {
		this->timestamp_end = SDL_GetTicks();
		//SDL_WM_SetCaption("FPS: " << framecounter/((timestamp_atend - timestamp_atstart)/1000.0), NULL)
		//SDL_SetWindowTitle(sdlwindow, 1000.0/(timestamp_end - timestamp_start)));
		if (fps_desired != 0) {	// 0 = unlimited fps
			int delay = (1000.0 / fps_desired) - (timestamp_end - timestamp_start);
			if (delay > 0) SDL_Delay(delay);
		}
		int current_timestamp = SDL_GetTicks();
		fps_last = 1000.0 / (current_timestamp - timestamp_start);	// NOTE: does not work if FPS >= 1000
		timestamp_start = current_timestamp;
	}

	return this->works;
}

float Display::get_totalfps() {
	return framecounter / ((timestamp_start - timestamp_initial) / 1000.0);
}

float Display::get_fps_last(){
	return this->fps_last;
}

unsigned char Display::get_desiredfps() {
	return this->fps_desired;
}

uint32_t Display::get_runtime() {
	// FIXME: This is not the same as total time program has been running
	return timestamp_end - timestamp_initial;
}

uint32_t Display::get_framecount() {
	return this->framecounter;
}

bool Display::save_screenshot(std::string filename) {
	// FIXME: Colors are wrong in saved image
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		#define rmask 0xff000000
		#define gmask 0x00ff0000
		#define bmask 0x0000ff00
		#define amask 0x000000ff
	#else
		#define rmask 0x000000ff
		#define gmask 0x0000ff00
		#define bmask 0x00ff0000
		#define amask 0xff000000
	#endif
	SDL_Surface *screenshot = SDL_CreateRGBSurface(0, this->width, this->height, 32, rmask, gmask, bmask, amask);	// TODO: 24 bpp?
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);
	if (SDL_SaveBMP(screenshot, filename.c_str()))
		log("ERROR: Cannot save screenshot image");
	SDL_FreeSurface(screenshot);
	return false;	// TODO
}

void Display::set_fade(uint8_t alpha) {
	this->fade_amount = alpha;
}
