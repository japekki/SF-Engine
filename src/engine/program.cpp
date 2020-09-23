#include <iostream>
#include "options.hpp"
#include "program.hpp"
#include "audio.hpp"
#include "misc.hpp"
#include "display.hpp"

Program::Program(int argc, char** argv) {
	log("Program started.");
	this->argc = argc;
	this->argv = argv;

	// Clean up SDL when program quits:
		atexit(SDL_Quit);

	// CREATE DISPLAY DEVICE:
		display = new Display();

	// CREATE INPUT DEVICES:
		keyboard = new Keyboard();
		mouse = new Mouse();
		joystick = new Joystick();

	// CREATE AUDIO DEVICE:
		//this->audio_works = audio_init();

	// SET UP MIDI:

	// SET UP DISPLAY DEVICE:	(overwritten by sub class init())
		display->set_width(640);
		display->set_height(480);
		display->set_desiredfps(1);
		//display->vsync = true;
		//display->mousecursor_visible = false;
		//display->set_fullscreen(true);
}

bool Program::init() {
	// SET UP DISPLAY DEVICE:
		if (!display->setup()) this->works = false;
		if (this->works) display->set_title(name + " - " + version);
		return this->works;
}

Program::~Program() {
	log("Program finished.");
	printf("TIME: %i ms -- FRAMES: %i -- FPS: %f / %i\n",
		display->get_runtime(),
		display->get_framecount(),
		display->get_totalfps(),
		display->get_desiredfps());

	delete display;
	delete keyboard;
	delete mouse;
	delete joystick;
}

bool Program::mainloop() {
	while (!mainloop_done and this->works) {
		get_events();
		display->refresh();
	}
	return this->works;
}

void Program::get_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				mainloop_done = true;	// TODO: quit (and free resources) immediately - in case something went wrong, or super slow fps (< 0.1)
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED or event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					display->check_window_size();
				else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
					display->minimized = true;
				else if (event.window.event == SDL_WINDOWEVENT_RESTORED)
					display->minimized = false;
				//else if (event.window.event == SDL_WINDOWEVENT_HIDDEN)
				//else if (event.window.event == SDL_WINDOWEVENT_EXPOSED:
				break;
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					//keyboard.push_event(event.key);
					keyboard->presscount[event.key.keysym.scancode]++;
					/*
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							break;
					}
					*/
				}
				break;
			case SDL_KEYUP:
				//keyboard.push_event(event.key);
				/*
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						break;
				}
				*/
				break;

			//case SDL_MOUSEMOTION:
				//mouse.change_x = event.motion.xrel;
				//mouse.change_y = event.motion.yrel;
				//mouse.pos_x = event.motion.x;
				//mouse.pos_y = event.motion.y;
				//if (display->grid->centered) {
				//	mouse.pos_x -= display->get_width()/2;
				//	mouse.pos_y -= display->get_height()/2;
				//}
				//break;

			case SDL_MOUSEWHEEL:
				if(event.wheel.y > 0) // scroll up
					mouse->wheel_up_count++;
				else if(event.wheel.y < 0) // scroll down
					mouse->wheel_down_count++;
				else if(event.wheel.x > 0) // scroll right
					mouse->wheel_right_count++;
				else if(event.wheel.x < 0) // scroll left
					mouse->wheel_left_count++;
				break;

			case SDL_MOUSEBUTTONDOWN:
				//printf("Mouse button %d pressed at (%d,%d)\n", event.button.button, event.button.x, event.button.y);
				if (event.button.button <= MOUSE_BUTTON_COUNT) {
					mouse->buttonstates[event.button.button] = true;
					mouse->presscount[event.button.button]++;
					break;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				//printf("Mouse button %d released at (%d,%d)\n", event.button.button, event.button.x, event.button.y);
				if (event.button.button <= MOUSE_BUTTON_COUNT) {
					mouse->buttonstates[event.button.button] = false;
					break;
				}
				break;

			case SDL_JOYBUTTONDOWN:
				log("Joystick button down.");
				break;

			case SDL_JOYBUTTONUP:
				log("Joystick button up.");
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
