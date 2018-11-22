/*
	SF-Engine

	This file has routines for handling the display/monitor.
*/

#include <iostream>
#include <string>

#include "misc.hpp"
#include "display.hpp"
#include "program.hpp"

// TODO:
	// - Set monitor Hz

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
			/*
			this->sdlwindow = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
				// TODO: Native desktop resolution:
				// this->sdlwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
			if (this->sdlwindow == nullptr) {
				log("ERROR while creating SDL surface:");
				log(SDL_GetError());
				SDL_Quit();
				this->works = false;
			}
			*/
			Uint32 flags = 0;
			if (this->fullscreen) flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
			if (SDL_CreateWindowAndRenderer(this->width, this->height, flags, &this->sdlwindow, &this->sdlrenderer) != 0) {
                log("ERROR while creating SDL Window with Renderer:");
                    log(SDL_GetError());
                    SDL_Quit();
                    this->works = false;
                }

			this->sdlsurface = SDL_GetWindowSurface(this->sdlwindow);

			// Set up SDL renderer:
			/*
				this->sdlrenderer = SDL_CreateRenderer(this->sdlwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (this->sdlrenderer == nullptr){
					SDL_DestroyWindow(this->sdlwindow);
					log("ERROR while creating SDL renderer:");
					log(SDL_GetError());
					SDL_Quit();
					this->works = false;
				}
				*/
			this->sdltexture = SDL_CreateTexture(this->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, this->width, this->height);

		//this->zbuf->set_size(width, height);
		this->timestamp_initial = SDL_GetTicks();

		//if (this->fullscreen) SDL_SetWindowFullscreen(this->sdlwindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		//SDL_ShowCursor(SDL_DISABLE);
		return true;	// TODO
	}

	void Display::set_title(std::string title) {
		this->title = title;
		// TODO:
		// If window already exists:
		SDL_SetWindowTitle(this->sdlwindow, title.c_str());
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

	bool Display::set_fullscreen(bool fullscreen) {
		this->fullscreen = fullscreen;
		if (fullscreen)
			SDL_SetWindowFullscreen(this->sdlwindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			SDL_SetWindowFullscreen(this->sdlwindow, 0);
		return true;	// TODO
	}

	bool Display::toggle_fullscreen() {
		if (this->fullscreen)
			SDL_SetWindowFullscreen(this->sdlwindow, 0);
		else
			SDL_SetWindowFullscreen(this->sdlwindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		this->fullscreen =! this->fullscreen;
		return true;	// TODO
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

void Display::clearscreen() {	// FIXME: Does not clear the screen
	SDL_RenderClear(this->sdlrenderer);
}

bool Display::refresh() {
	bool works = true; // Change to false if something goes wrong
	SDL_UpdateTexture(this->sdltexture, NULL, this->sdlsurface->pixels, this->sdlsurface->pitch);
	SDL_RenderCopy(this->sdlrenderer, this->sdltexture, NULL, NULL);
	SDL_RenderPresent(this->sdlrenderer);
	this->framecounter++;

	//z_buf.reset();

	// Sleep and sync to desired FPS:
	if (works) {
		this->timestamp_end = SDL_GetTicks();
		//SDL_WM_SetCaption("DEMO | FPS: " << framecounter/((timestamp_atend - timestamp_atstart)/1000.0), NULL)
		//SDL_SetWindowTitle(this->sdlwindow, 1000.0/(this->timestamp_end - this->timestamp_start)));
		int delay = (1000.0/this->fps_desired) - (this->timestamp_end - this->timestamp_start);
		if (delay > 0)
			SDL_Delay(delay);
		this->timestamp_start = SDL_GetTicks();
	}

	return works;
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
