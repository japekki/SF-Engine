#include "control.hpp"

	// INCLUDE FMOD:
	#if defined(WIN32) || defined(__WATCOMC__)
		#include <windows.h>
		#include <conio.h>
	#else
		#include "include/fmod/wincompat.h"
	#endif
		#include "include/fmod/fmod.h"
		#include "include/fmod/fmod_errors.h"


#include <SDL/SDL.h>
#include "options.hpp"
#include "sound.hpp"
#include <iostream>

using namespace std;

	void poll_events() {
		extern Keyboard keyboard;
		extern bool mainloopdone;
		extern bool demo_paused;
		extern Sound sound;
		// TODO: MIDI
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					mainloopdone = true;
					break;
				}
				#ifdef INTERACTIVE
					case SDL_KEYDOWN: {
						keyboard.push_event(event.key);
						switch (event.key.keysym.sym) {
							case SDLK_ESCAPE:
							{
								mainloopdone = true;
							}
							case SDLK_LEFT: {
								//FMUSIC_SetOrder(tracker_musa, FMUSIC_GetOrder(tracker_musa)-1);
								//phase -= 1;
								break;
							}
							case SDLK_RIGHT: {
								//FMUSIC_SetOrder(tracker_musa, FMUSIC_GetOrder(tracker_musa)+1);
								//phase += 1;
								break;
							}
							case SDLK_SPACE: {
								demo_paused = !demo_paused;
								//FMUSIC_SetPaused(tracker_musa, demo_paused);
								break;
							}
							case SDLK_s: {
								// Save screenshot:
								Uint32 rmask, gmask, bmask, amask;
								#if SDL_BYTEORDER == SDL_BIG_ENDIAN
									rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
								#else
									rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
								#endif
								// TODO: Jos Windows - jos linux:
									//if(SDL_SaveBMP(monitor.sdlsurface, "d:\\temp\\demopohja_screenshot.bmp") != 0)
										//cout << "Cannot save screenshot image...\n" << endl;
								break;
							}
						}
					}
					case SDL_KEYUP: {
						keyboard.push_event(event.key);
					}
					#ifdef WITH_MOUSE
						case SDL_MOUSEMOTION: {
							mouse.change_x = event.motion.xrel;
							mouse.change_y = event.motion.yrel;
							mouse.pos_x = event.motion.x;
							mouse.pos_y = event.motion.y;
							if (monitor.koordinaatisto.centered)
							{
								mouse.pos_x -= monitor.get_width()/2;
								mouse.pos_y -= monitor.get_height()/2;
							}
							break;
						}
						case SDL_MOUSEBUTTONDOWN: {
							//printf("Mouse button %d pressed at (%d,%d)\n", event.button.button, event.button.x, event.button.y);
							switch (event.button.button) {
								case 1:
								{
									mouse.button1state= true;
									break;
								}
								case 2:
								{
									mouse.button2state = true;
									break;
								}
								case 3:
								{
									mouse.button3state = true;
									break;
								}
							}
							break;
						}
						case SDL_MOUSEBUTTONUP: {
							// TODO
							switch (event.button.button) {
								case 1: {
									mouse.button1state = true;
									break;
								}
								case 2: {
									mouse.button2state = true;
									break;
								}
								case 3: {
									mouse.button3state = true;
									break;
								}
							}
						}
					#endif // #ifdef WITH_MOUSE
					#ifdef WITH_JOYSTICK
						case SDL_JOYBUTTONDOWN: {
							#ifdef DEBUGMSG
								cout << "Peliohjaimen nappi painettu pohjaan." << endl;
							#endif
							break;
						}
						case SDL_JOYBUTTONUP: {
							#ifdef DEBUGMSG
								cout << "Peliohjaimen nappi irrotettu." << endl;
							#endif
							break;
						}
						case SDL_JOYAXISMOTION: {
							#ifdef DEBUGMSG
								cout << ("Joystick: %i\n", event.jaxis.value) << endl;
							#endif
							extern Joystick joystick;
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
							break;
						}
					#endif // #ifdef WITH_JOYSTICK
				#endif // #ifdef INTERACTIVE
				//default: break;
			}   // switch (event.type)
		}   // while SDL_PollEvent(&event)
	}

#ifdef INTERACTIVE
	Keyboard::Keyboard() {
	}

	Keyboard::~Keyboard() {
	}

	void Keyboard::push_event(SDL_KeyboardEvent sdl_keyboardevent) {
		// TODO: Binary array for keyboard key states (pressed or released)
	}

	SDL_KeyboardEvent Keyboard::pop_event() {
	}

	#ifdef WITH_JOYSTICK
		Joystick::Joystick(Uint8 id) {
				extern Joystick joystick;
				SDL_Init(SDL_INIT_JOYSTICK); // TODO: SDL_Init should be called before all other SDL functions.
				SDL_JoystickEventState(SDL_ENABLE);
				joystick.sdl_joystick = SDL_JoystickOpen(0);
				cout << "Joystick initialized." << endl;
		}

		Joystick::~Joystick() {
		}
	#endif
#endif
