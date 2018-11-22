/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a rocket game.
*/

/*

Once upon a time
there were V-shaped rockets.
While shooting fire
water drained into pockets.

Since then the time has passed,
no more keyboards are smashed.

Brave men's fingers
should never linger,
so that no lamer
could ever win them.

A new generation of the young has arrived to try the game,
and those brave men in their rockets shall fight again...

*/

/*
    for each bullets
		bullet->move
		bullet->check_hits
	for each rocket
			rocket->move
*/

#include <SDL_image.h>
#include <iostream>
#include <string>
#include "options.hpp"
#include "program_rocketz.hpp"
#include "misc.hpp"
#include "geom.hpp"

Rocketz::Rocketz() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Rocketz::Rocketz()");
	#endif // WITH_DEBUGMSG
	// SET PROGRAM ATTRIBUTES:
		this->name = "RocketZ";
		this->version = "0.0001";
		//this->with_sound = false;
}

bool Rocketz::init() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Rocketz::init()");
	#endif // WITH_DEBUGMSG
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(50);
		//this->display->set_fullscreen(true);
		Program::init();

	// LOAD AUDIO FILES:
		if (this->with_sound) {
			this->music_title = new Audio;
			this->music_title->load_file(FILENAME_MUSIC_TITLE);
		}

	// LOAD IMAGE FILES:
		SDL_RWops *rwop;
		rwop = SDL_RWFromFile(FILENAME_PIC_TITLESCREEN, "rb");
		pic_titlescreen = IMG_LoadPNG_RW(rwop);
		//pic_titlescreen = IMG_LoadPNM_RW(rwop);
		//pic_titlescreen = IMG_LoadBMP_RW(rwop);
		if(!pic_titlescreen) {
			log("ERROR loading image:");
			log(IMG_GetError());
		}

	//CREATE SCENES:

	// CREATE 2D POLYGONS:
		//rocket.a.x = -10;
		//rocket.a.y = -10;
		//rocket.b.x = 0;
		//rocket.b.y = 0;
		//rocket.c.x = 10;
		//rocket.c.y = -10;

	// Create rocket:
		this->rocket = new Rocket();

	// INIT EFFUXES:
		this->effux_circles = new EffuxCircles(this->display);
		this->scene = SCENE_TITLESCREEN;
		return this->works;
}

Rocketz::~Rocketz() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Rocketz::~Rocketz()");
	#endif // WITH_DEBUGMSG
	if (this->with_sound) delete this->music_title;
}

bool Rocketz::mainloop() {
	// Start title music:
		if (this->with_sound) this->music_title->play();

	//timeline.init();
	while (!this->mainloop_done and this->works) {
		//this->display->set_timestamp_start(SDL_GetTicks()); // TODO: Relocate
		handle_events();

		//this->display->clearscreen();

			switch (this->scene) {
				case SCENE_TITLESCREEN:
					this->effux_circles->draw(SDL_GetTicks()/3.0, true);
					SDL_BlitSurface(this->pic_titlescreen, NULL, this->display->sdlsurface, NULL);
					if (this->keyboard->key_ENTER_down) {
						if (this->with_sound) {
							delete this->music_title;
							this->music_gameplay = new Audio;
							this->music_gameplay->load_file(FILENAME_MUSIC_GAMEPLAY);
							this->music_gameplay->play();
						}
						this->scene = SCENE_GAMEPLAY;
					}
					if (this->keyboard->key_ESC_down) this->mainloop_done = true;
					break;
				case SCENE_GAMEPLAY:
					// CHECK USER INPUT:
						if (this->keyboard->key_ESC_down) {
							this->scene = SCENE_TITLESCREEN;
							if (this->with_sound) {
								delete this->music_gameplay;
								this->music_title = new Audio;
								this->music_title->load_file(FILENAME_MUSIC_TITLE);
								this->music_title->play();
							}
							this->keyboard->key_ESC_down = false;
						}
					// MOVE STUFF:
						// Move rockets:
							if (this->keyboard->key_UP_down) this->rocket->y -= 1;
							if (this->keyboard->key_DOWN_down) this->rocket->y += 1;
							if (this->keyboard->key_LEFT_down) this->rocket->x -= 1;
							if (this->keyboard->key_RIGHT_down) this->rocket->x += 1;
							#ifdef WITH_DEBUGMSG
								//debugmsg("Rocket X:" + std::to_string(this->rocket->x));
								//debugmsg("Rocket Y:" + std::to_string(this->rocket->y));
							#endif // WITH_DEBUGMSG
						// Move bullets:
							// TODO
						// Move enemies:
							// TODO
					// DRAW STUFF:
						// Draw level:
							// Draw parallax background:
								//for (unsigned int layernum = 0; layernum < this->gameplay->level->backgrounds.size(); layernum++) {
									// Calculate offset where to draw surface from
									// draw surface this->gameplay->level->backgrounds[layernum];
								//}
							// Draw player rockets:
								//this->display->draw_triangle(this->rocket);
								this->display->draw_polygon(this->rocket);
							// Draw bullets:
								//for (unsigned int playernum = 0; playernum < this->gameplay->players.size(); playernum++) {
								//		for (unsigned int bulletnum = 0; bulletnum < this->gameplay->bulletnum.size(); bulletnum++) {
								//			// TODO: Draw player bullet
								//		}
								//}
								//for (unsigned int layernum = 0; layernum < this->gameplay->level->backgrounds.size(); layernum++) {
								//}
							// Draw enemies:
								// TODO
					break;
			}
			this->display->refresh();
	}
	return this->works;
}
