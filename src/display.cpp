/*
	SF-Engine

	This file has routines for handling the display/monitor.
*/

#include "display.hpp"
#include "globals.hpp"

Display::Display() {
	framecounter = 0;
}

Display::~Display() {
}

int Display::get_x_min() {
	return x_min;
}

int Display::get_x_max() {
	return x_max;
}

int Display::get_y_min() {
	return y_min;
}

int Display::get_y_max() {
	return y_max;
}

int Display::get_width() {
	return width;
}

int Display::get_height() {
	return height;
}

void Display::set_x_min(int new_x_min) {
	x_min = new_x_min;
	width = abs(x_max - x_min);
}

void Display::set_x_max(int new_x_max) {
	x_max = new_x_max;
	width = abs(x_max - x_min);
}

void Display::set_y_min(int new_y_min) {
	y_min = new_y_min;
	height = abs(y_max - y_min);
}

void Display::set_y_max(int new_y_max) {
	y_max = new_y_max;
	height = abs(y_max - y_min);
}

void Display::set_width(int new_width) {
	width = new_width;
}

void Display::set_height(int new_height) {
	height = new_height;
}

void Display::set_name(char* name) {
	SDL_WM_SetCaption(name, NULL);
}

bool Display::setup() {
	bool result = true; // Muutetaan falseksi jos jokin meni vikaan
	// TODO:
	// - S‰‰d‰ monitorin hertzej‰
	// - Runtime fullscreen toggling
	/* OPENGL
			//const SDL_VideoInfo* info = NULL;   // Information about the current video settings.
			if (fullscreen) {
				sdlsurface = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL | SDL_FULLSCREEN);
			}
			else {
				sdlsurface = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL );
			}
			if (!sdlsurface) {
				printf("OPENGL: Unable to set video mode: %s\n", SDL_GetError());
				result=false;
			}
			else {
				printf("OPENGL: Set up video mode %ix%i %i bpp.\n", get_width(), get_height(), bpp);
			}

			glViewport(0, 0, get_width(), get_height());		// Reset The Current Viewport

			glMatrixMode(GL_PROJECTION);		// Select The Projection Matrix
			glLoadIdentity();					// Reset The Projection Matrix

			// TODO: Aspect Ratio

			glMatrixMode(GL_MODELVIEW);			// Select The Modelview Matrix
			glLoadIdentity();					// Reset The Modelview Matrix

			glShadeModel(GL_SMOOTH);				// Enable Smooth Shading
			glClearColor(0.5f, 0.5f, 0.5f, 0.5f);	// Background
			glClearDepth(1.0f);						// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
			glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

			SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
			SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

			//glEnableClientState(GL_VERTEX_ARRAY);
			//glEnableClientState(GL_COLOR_ARRAY);
	*/

	if ( SDL_Init(SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL: Unable to init: %s\n", SDL_GetError() );
		result=false;
	}
	if (fullscreen) {
		sdlsurface = SDL_SetVideoMode(get_width(), get_height(), bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	}
	else {
		sdlsurface = SDL_SetVideoMode(get_width(), get_height(), bpp, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT);
	}
	if (!sdlsurface) {
		printf("SDL: Unable to set video mode: %s\n", SDL_GetError());
		result=false;
	}
	else {
		set_width(sdlsurface->w);
		set_height(sdlsurface->h);
		bpp = sdlsurface->format->BitsPerPixel;
		printf("SDL: Set up video mode %ix%i %i bpp.\n", get_width(), get_height(), bpp);
		// Lock the screen for direct access to the pixels:
		if ( SDL_MUSTLOCK(sdlsurface) )
		{
			if ( SDL_LockSurface(sdlsurface) < 0 )
			{
				fprintf(stderr, "SDL: Can't lock screen: %s\n", SDL_GetError());
				result=false;
			}
		}
	}
	//z_buf.resize(get_width()*get_height());

	SDL_ShowCursor(SDL_DISABLE);
	return result;
}

void Display::clearscreen() {
	// Clear screen:

	// Opengl:
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear screen/Z-buffer

	SDL_FillRect(sdlsurface, 0, clearcolor);

}

bool Display::refresh() {
	bool result=true; // Change to false if something goes wrong
	// Opengl:
	//SDL_GL_SwapBuffers();

	if ( SDL_MUSTLOCK(sdlsurface) ) {
		SDL_UnlockSurface(sdlsurface);
	}
	if( SDL_Flip( sdlsurface ) == -1 ) {
	//SDL_UpdateRect(monitor.sdlsurface, 0, 0, 0, 0);
		cerr << "SDL: Error while blitting to screen surface." << endl;
		result=false;
	}
	//z_buf.reset();
	// Lock the screen for direct access to the pixels:
	if (result and SDL_MUSTLOCK(sdlsurface))
		if ( SDL_LockSurface(sdlsurface) < 0 ) {
			fprintf(stderr, "SDL: Can't lock screen: %s\n", SDL_GetError());
			result=false;
		}


	framecounter++;

	// Sleep and sync to desired FPS:
	if (result) {
		timestamp_atend = SDL_GetTicks();
		//SDL_WM_SetCaption("DEMO | FPS: " << framecounter/((timestamp_atend - timestamp_atstart)/1000.0), NULL)
		delay = (1000.0/fps_lockto) - (timestamp_atend - timestamp_atstart);
		if (delay > 0)
			SDL_Delay(delay);
	}

	return result;
}
