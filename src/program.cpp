/*
	SF-Engine

	Derive game/demo specific code from here.
*/

#include <iostream>
#include "options.hpp"
#include "program.hpp"
#include "audio.hpp"
#include "misc.hpp"

Program::Program() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Program::Program()");
	#endif // WITH_DEBUGMSG

	// CREATE DISPLAY DEVICE:
		this->display = new Display();

	// CREATE INPUT DEVICES:
		this->keyboard = new Keyboard();
		this->mouse = new Mouse();
		this->joystick = new Joystick();

	// CREATE AUDIO DEVICE:
		this->audio_works = audio_init();

	// SET UP MIDI:

	// SET UP DISPLAY DEVICE:	(overwritten by sub class init())
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(40);
		//this->display->set_fullscreen(true);
}

bool Program::init() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Program::init()");
	#endif // WITH_DEBUGMSG
	// SET UP DISPLAY DEVICE:
		if (!this->display->setup()) this->works = false;
		if (this->works) this->display->set_title(this->name + " - " + this->version);
		return this->works;
}

Program::~Program() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Program::~Program()");
	#endif // WITH_DEBUGMSG
	// FREE RESOURCES:
		delete this->display;
		delete this->keyboard;
		delete this->mouse;
		delete this->joystick;
}

bool Program::mainloop() {
	while (!this->mainloop_done and this->works) {
		handle_events();
		this->display->refresh();
	}
	return this->works;
}

void Program::handle_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				this->mainloop_done = true;
				break;
			case SDL_KEYDOWN:
				//keyboard.push_event(event.key);
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						this->keyboard->key_ESC_down = true;
						break;
					case SDLK_RETURN:
						this->keyboard->key_ENTER_down = true;
						break;
					case SDLK_UP:
						this->keyboard->key_UP_down = true;
						break;
					case SDLK_DOWN:
						this->keyboard->key_DOWN_down = true;
						break;
					case SDLK_LEFT:
						this->keyboard->key_LEFT_down = true;
						break;
					case SDLK_RIGHT:
						this->keyboard->key_RIGHT_down = true;
						break;
					case SDLK_SPACE:
						this->paused = !this->paused;
						break;
					case SDLK_s:
						// Save screenshot:
						unsigned int rmask, gmask, bmask, amask;
						#if SDL_BYTEORDER == SDL_BIG_ENDIAN
							rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
						#else
							rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
						#endif
							//if(SDL_SaveBMP(this->dispaly->sdlsurface, "screenshot.bmp") != 0)
								//log("ERROR: Cannot save screenshot image");
						break;
					case SDLK_F11:
						this->display->toggle_fullscreen();
						break;
				}
				break;
			case SDL_KEYUP:
				//keyboard.push_event(event.key);
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						this->keyboard->key_ESC_down = false;
						break;
					case SDLK_RETURN:
						this->keyboard->key_ENTER_down = false;
						break;
					case SDLK_UP:
						this->keyboard->key_UP_down = false;
						break;
					case SDLK_DOWN:
						this->keyboard->key_DOWN_down = false;
						break;
					case SDLK_LEFT:
						this->keyboard->key_LEFT_down = false;
						break;
					case SDLK_RIGHT:
						this->keyboard->key_RIGHT_down = false;
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				//mouse.change_x = event.motion.xrel;
				//mouse.change_y = event.motion.yrel;
				//mouse.pos_x = event.motion.x;
				//mouse.pos_y = event.motion.y;
				//if (this->display->coordinategrid->centered) {
				//	mouse.pos_x -= this->display->get_width()/2;
				//	mouse.pos_y -= this->display->get_height()/2;
				//}
				break;
			case SDL_MOUSEBUTTONDOWN:
				//printf("Mouse button %d pressed at (%d,%d)\n", event.button.button, event.button.x, event.button.y);
				switch (event.button.button) {
					case 1: {
						this->mouse->button1down = true;
						break;
					}
					case 2: {
						this->mouse->button2down = true;
						break;
					}
					case 3: {
						this->mouse->button3down = true;
						break;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				// TODO
				switch (event.button.button) {
					case 1:
						this->mouse->button1down = false;
						break;
					case 2:
						this->mouse->button2down = false;
						break;
					case 3:
						this->mouse->button3down = false;
						break;
				}
				break;
			case SDL_JOYBUTTONDOWN:
				break;
			case SDL_JOYBUTTONUP:
				break;
			case SDL_JOYAXISMOTION:
				//cout << ("Joystick: %i\n", event.jaxis.value) << endl;
				/*
				if (event.jaxis.axis == 0) {
					joystick.axis0 = event.jaxis.value;
				} else if (event.jaxis.axis == 1) {
					joystick.axis1 = event.jaxis.value;
				} else if (event.jaxis.axis == 2) {
					joystick.axis2 = event.jaxis.value;
				} else if (event.jaxis.axis == 3) {
					joystick.axis3 = event.jaxis.value;
				}
				//joystick_x = event.jaxis.value;
				*/
				break;
		}
	}
}