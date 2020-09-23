		// TEST:
			//SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
			//needs to happen before texture creation.
			//This is because interpolation mode is a property of created textures, not the rendering pipeline.

//#include <SDL_opengl.h>
#include <GL/gl.h>
#include <SDL_opengl.h>
#include "display_gl.hpp"
#include "misc.hpp"

Display_GL::Display_GL() {
}

Display_GL::~Display_GL() {
}

bool initGL() {
	//Initialize Projection Matrix:
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	//Initialize Modelview Matrix:
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	return true;	// TODO
}

bool Display_GL::setup() {
	// Call this when creating or altering a display window
	// TODO: delete/modify old when calling this again (currently opens up a secondary window)

		//SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, WinWidth, WinHeight, WindowFlags);
		//assert(Window);

	// SET UP SDL VIDEO:
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			log("ERROR while initializing SDL video:");
			log(SDL_GetError());
			this->works = false;
		}

	//Use OpenGL 1.1
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	//Use OpenGL 2.1
		//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

	// SET UP SDL DISPLAY WINDOW:

		uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		// Set vsync:
			if (this->vsync) flags = flags | SDL_RENDERER_PRESENTVSYNC;
			// FIXME:
			// - SDL_RENDERER_PRESENTVSYNC does nothing (at least it doesn't limit fps to monitor Hz)

		// Set fullscreen:
			if (this->fullscreen)
				if (this->fullscreenmode_desktop)
					flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
				else
					flags = flags | SDL_WINDOW_FULLSCREEN;

		// Create window:
			sdlwindow = SDL_CreateWindow("SDL2/OpenGL Demo", 0, 0, width, height, flags);
			glcontext = SDL_GL_CreateContext(sdlwindow);

			if(glcontext == NULL) {
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				//success = false;
			} else {
				//Use Vsync
				if(SDL_GL_SetSwapInterval(1) < 0) {
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}

				//Initialize OpenGL
				if(!initGL()) {
					log("Unable to initialize OpenGL!");
					//success = false;
				}
					glClearColor(0,0,0,1);
					glClear(GL_COLOR_BUFFER_BIT);

					/* Swap our buffer to display the current contents of buffer on screen */
					SDL_GL_SwapWindow(sdlwindow);
			}

	// FIXME:
		// - SDL_WINDOW_FULLSCREEN_DESKTOP acts the same as SDL_WINDOW_FULLSCREEN when creating a window
		// - SDL_RENDERER_PRESENTVSYNC does nothing when creating a window
		if (this->fullscreen)
			this->set_fullscreen(true);
		//if (this->vsync) this->set_vsync(true);

	// CLEAR POSSIBLE CARBAGE:
		//SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		//SDL_RenderClear(renderer);
		//this->refresh();

	// SET OTHER WINDOW PROPERTIES:
		// Show or hide mouse cursor:
			if (mousecursor_visible)
				SDL_ShowCursor(SDL_ENABLE);	// Default in SDL
			else
				SDL_ShowCursor(SDL_DISABLE);

		// Set window resizable:
			// FIXME: Window cannot be resized (XFCE)
			//if (this->resizable_window) SDL_SetWindowResizable(sdlwindow, SDL_TRUE);

	timestamp_initial = SDL_GetTicks();

	return true;	// TODO
}

bool Display_GL::refresh() {
	//glViewport(0, 0, this->width, this->height);
	//glClearColor(1.f, 0.f, 1.f, 0.f);
	//glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(sdlwindow);
	glFlush();

	framecounter++;

	// Sleep and sync to desired FPS:
		this->timestamp_end = SDL_GetTicks();

		if (fps_desired != 0) {	// 0 = unlimited fps
			int delay = (1000.0 / fps_desired) - (timestamp_end - timestamp_start);
			if (delay > 0) SDL_Delay(delay);
		}
		int current_timestamp = SDL_GetTicks();
		fps_last = 1000.0 / (current_timestamp - timestamp_start);	// NOTE: does not work if FPS >= 1000
		timestamp_start = current_timestamp;

	return true;	// TODO
}
