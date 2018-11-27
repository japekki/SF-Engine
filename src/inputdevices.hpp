#ifndef INPUTDEVICES_HPP
	#define INPUTDEVICES_HPP

	#include "types.hpp"
	//#include <vector>
	//#include <SDL.h>

	//#include "options.hpp"

	// TODO:
	// - Lower level keyboard handling (polling states may miss key presses when running slow)
	// - Indicator / counter that a button has previously been pressed and released
	// - Array for keyboard button states instead of separate named boolean variables

	class Keyboard {
		public:
			bool enabled;
			Keyboard();
			~Keyboard();
			/*
			SDL_KeyboardEvent eventqueue;
			void push_event(SDL_KeyboardEvent sdl_keyboardevent);
			SDL_KeyboardEvent pop_event();
			*/
			bool key_ESC_down = false;
			bool key_ENTER_down = false;
			bool key_UP_down = false;
			bool key_DOWN_down = false;
			bool key_LEFT_down = false;
			bool key_RIGHT_down = false;

			bool key_F1_down = false;
			bool key_F2_down = false;
			bool key_F3_down = false;
			bool key_F4_down = false;
			bool key_F5_down = false;
			bool key_F6_down = false;
			bool key_F7_down = false;
			bool key_F8_down = false;
			bool key_F9_down = false;
			bool key_F10_down = false;
			bool key_11_down = false;
			bool key_12_down = false;

			bool key_1_down = false;
			bool key_2_down = false;
			bool key_3_down = false;
			bool key_4_down = false;
			bool key_5_down = false;
			bool key_6_down = false;
			bool key_7_down = false;
			bool key_8_down = false;
			bool key_9_down = false;
			bool key_0_down = false;

			bool key_A_down = false;
			bool key_B_down = false;
			bool key_C_down = false;
			bool key_D_down = false;
			bool key_F_down = false;
			bool key_G_down = false;
			bool key_H_down = false;
			bool key_I_down = false;
			bool key_J_down = false;
			bool key_K_down = false;
			bool key_L_down = false;
			bool key_M_down = false;
			bool key_O_down = false;
			bool key_P_down = false;
			bool key_Q_down = false;
			bool key_R_down = false;
			bool key_S_down = false;
			bool key_T_down = false;
			bool key_U_down = false;
			bool key_V_down = false;
			bool key_W_down = false;
			bool key_X_down = false;
			bool key_Y_down = false;
			bool key_Z_down = false;
	};

	class Mouse {
		public:
		//bool cursor = true;	// Mouse pointer visible or not
		int pos_x, pos_y;
		int change_x, change_y;
		bool button1down = false;
		bool button2down = false;
		bool button3down = false;
	};

	class Joystick {
		private:
			//SDL_Joystick *sdl_joystick;
			unsigned char id;
		public:
			Joystick();
			~Joystick();
			//bool enabled;
			int axis0, axis1, axis2, axis3;
			bool button1down = false;
			bool button2down = false;
	};

#endif // INPUTDEVICES_HPP
