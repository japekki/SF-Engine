/*
	SF-Engine

	This file has routines for user interaction, like reading input devices such as keyboard, mouse, joystick etc.
*/

#include "inputdevices.hpp"

/*
#include "options.hpp"
#include "sound.hpp"
*/

Keyboard::Keyboard() {
}

Keyboard::~Keyboard() {
}

/*
void Keyboard::push_event(SDL_KeyboardEvent sdl_keyboardevent) {
	// TODO: Binary array for keyboard key states (pressed or released)
}

SDL_KeyboardEvent Keyboard::pop_event() {
}
*/

Joystick::Joystick() {
		//SDL_Init(SDL_INIT_JOYSTICK); // TODO: SDL_Init should be called before all other SDL functions.
		//SDL_JoystickEventState(SDL_ENABLE);
		//joystick.sdl_joystick = SDL_JoystickOpen(0);
		//log("Joystick initialized.");
}

Joystick::~Joystick() {
}
