/*
	SF-Engine

	This file has routines for user interaction, like reading input devices such as keyboard, mouse, joystick etc.
*/

// TODO:
// - User defined button bindings
// - Lower level keyboard handling (polling states may miss key presses when running slow) ?
// - Emulate input device with other input device (use joystick as mouse etc.)

#ifndef INPUTDEVICES_HPP
	#define INPUTDEVICES_HPP

	#include <SDL.h>

	class Keyboard {
		public:
			bool enabled = false;	// TODO
			const unsigned char *buttonstates = SDL_GetKeyboardState(NULL);
			uint8_t presscount[256] = {0};
			Keyboard();
			~Keyboard();
			uint8_t get_presscount(unsigned char scancode);
			//void poll();
	};

	#define MOUSE_BUTTON_COUNT 3

	class Mouse {
		private:
			//bool cursor = true;	// Mouse pointer visible or not
		public:
			bool enabled = false;	// TODO;
			int pos_x = 0;
			int pos_y = 0;
			int change_x = 0;
			int change_y = 0;
			uint8_t presscount[MOUSE_BUTTON_COUNT] = {0};
			bool buttonstates[MOUSE_BUTTON_COUNT] = {false};
			uint8_t wheel_up_count = 0;
			uint8_t wheel_down_count = 0;
			uint8_t wheel_right_count = 0;
			uint8_t wheel_left_count = 0;
			bool get_cursor();	// TODO
			void set_cursor(bool state);		// TODO
			uint8_t get_presscount(uint8_t button);
			// TODO: Wheel count
			// TODO: set different mouse cursors
	};

	//#define JOYSTICK_BUTTON_COUNT 8
	#define JOYSTICK_AXIS_MARGIN 4000

	class Joystick {
		private:
			bool* buttonstates;
		public:
			bool enabled = false;	// TODO
			SDL_Joystick* sdl_joystick = nullptr;
			uint8_t button_amount = 0;
			unsigned char id = 0;
			uint8_t* presscount;
			//uint8_t presscount[JOYSTICK_BUTTON_COUNT] = {0};
			bool get_buttonstate(uint8_t button);
			Joystick();
			~Joystick();
			uint8_t get_presscount(unsigned char button);
	};

#endif // INPUTDEVICES_HPP
