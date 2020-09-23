#include <iostream>
#include "inputdevices.hpp"
#include "misc.hpp"

Keyboard::Keyboard() {
}

Keyboard::~Keyboard() {
}

uint8_t Keyboard::get_presscount(uint8_t scancode) {
	// NOTE: resets the queue to zero count
	uint8_t result = presscount[scancode];
	presscount[scancode] = 0;
	return result;
}

//void Keyboard::poll() {
//	SDL_PumpEvents();
//}

uint8_t Mouse::get_presscount(uint8_t button) {
	// NOTE: resets the queue to zero count
	uint8_t result = presscount[button];
	presscount[button] = 0;
	return result;
}

Joystick::Joystick() {
	int joysticks = 0;
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);	// FIXME: If multiple joysticks, init only once
	joysticks = SDL_NumJoysticks();

	// List all joysticks:
		if (joysticks)
			printf("Found %d joystick(s):\n", joysticks);
		else
			log("No joysticks found.");
		for (int i = 0; i < joysticks; i++) {
			printf("\t#%d - %s\n", i, SDL_JoystickNameForIndex(i));
		}

	if (joysticks) {
		sdl_joystick = SDL_JoystickOpen(0);
		if (sdl_joystick) {
			button_amount = SDL_JoystickNumButtons(sdl_joystick);
			presscount = new uint8_t[button_amount] {0};
			buttonstates = new bool[button_amount] {0};
			printf("Using joystick #0:\n");
			printf("\tName: %s\n", SDL_JoystickNameForIndex(0));
			printf("\tAxises: %d\n", SDL_JoystickNumAxes(sdl_joystick));
			printf("\tButtons: %d\n", button_amount);
			printf("\tBalls: %d\n", SDL_JoystickNumBalls(sdl_joystick));
			SDL_JoystickEventState(SDL_ENABLE);
		} else {
			printf("Couldn't open Joystick 0\n");
		}
    }

}

Joystick::~Joystick() {
	if (SDL_JoystickGetAttached(sdl_joystick))
		SDL_JoystickClose(sdl_joystick);
}

//if (SDL_JoystickGetButton(gameplay->joystick->sdl_joystick, 1)

bool Joystick::get_buttonstate(uint8_t button) {
	bool result = false;
	if ((button_amount > 0) and (button < button_amount))		// button 0 is first
		//result = buttonstates[button];
	// FIXME: sdl event for joystick
		result = SDL_JoystickGetButton(sdl_joystick, button);
	return result;
}

uint8_t Joystick::get_presscount(unsigned char button) {
	// NOTE: resets the queue to zero count
	uint8_t result;
	if ((button_amount > 0) and (button < button_amount)) {
		result = presscount[button];
		presscount[button] = 0;
	} else {
		result = 0;
	}
	return result;
}
