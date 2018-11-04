#ifndef CONTROL_HPP
	#define CONTROL_HPP
	#include <vector>
	#include <SDL/SDL.h>

	#include "options.hpp"

	// TODO:
	// - Lower level keyboard handling (polling states may miss key presses when running slow)

	void poll_events();

	class IOBox {
		IOBox();
		std::vector<Uint8> channels;
		bool connect(IOBox io_box, Uint8 channel, void *methodcall);
		void disconnect(IOBox io_box);
		Uint8 read8bit(Uint8 channel);
		Uint16 read16bit(Uint8 channel);
		Uint32 read32bit(Uint8 channel);
		bool write8bit(Uint8 channel, Uint8 data);
		bool write16bit(Uint8 channel, Uint16 data);
		bool write32bit(Uint8 channel, Uint32 data);
	};

	/*
	class Input {
	}

	class Output {
	}
	*/

	#ifdef INTERACTIVE
		class Keyboard {
			public:
				bool enabled;
				Keyboard();
				~Keyboard();
				SDL_KeyboardEvent eventqueue;
				void push_event(SDL_KeyboardEvent sdl_keyboardevent);
				SDL_KeyboardEvent pop_event();
				bool key_F1_pressed;
				bool key_F2_pressed;
				bool key_F3_pressed;
				bool key_F4_pressed;
				bool key_F5_pressed;
				bool key_F6_pressed;
				bool key_F7_pressed;
				bool key_F8_pressed;
				bool key_F9_pressed;
				bool key_F10_pressed;
				bool key_11_pressed;
				bool key_12_pressed;

				bool key_1_pressed;
				bool key_2_pressed;
				bool key_3_pressed;
				bool key_4_pressed;
				bool key_5_pressed;
				bool key_6_pressed;
				bool key_7_pressed;
				bool key_8_pressed;
				bool key_9_pressed;
				bool key_0_pressed;

				bool key_A_pressed;
				bool key_B_pressed;
				bool key_C_pressed;
				bool key_D_pressed;
				bool key_F_pressed;
				bool key_G_pressed;
				bool key_H_pressed;
				bool key_I_pressed;
				bool key_J_pressed;
				bool key_K_pressed;
				bool key_L_pressed;
				bool key_M_pressed;
				bool key_O_pressed;
				bool key_P_pressed;
				bool key_Q_pressed;
				bool key_R_pressed;
				bool key_S_pressed;
				bool key_T_pressed;
				bool key_U_pressed;
				bool key_V_pressed;
				bool key_W_pressed;
				bool key_X_pressed;
				bool key_Y_pressed;
				bool key_Z_pressed;
		};
		#ifdef WITH_JOYSTICK
			class Joystick {
				private:
					SDL_Joystick *sdl_joystick;
					Uint8 id;
				public:
					Joystick(Uint8 id);
					~Joystick();
					bool enabled;
					int axis0, axis1, axis2, axis3;
					bool button1down, button2down;
			};
		#endif
		#ifdef WITH_MOUSE
			class Mouse {
				public:
				bool enabled;
				int pos_x, pos_y;
				int change_x, change_y;
				bool button1down, button2down, button3down;
			};
		#endif
	#endif

#endif // CONTROL_HPP
