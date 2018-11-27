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
		this->version = "0.0002";
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

	// LOAD IMAGE FILES:
		SDL_RWops *rwop;
		rwop = SDL_RWFromFile(FILENAME_PIC_TITLESCREEN, "rb");
		if (rwop != NULL) {
			SDL_Surface *temp = IMG_LoadPNG_RW(rwop);
			SDL_RWclose(rwop);
			pic_titlescreen = SDL_CreateTextureFromSurface(this->display->sdlrenderer, temp);
			SDL_FreeSurface(temp);
			if(!pic_titlescreen) {
				log("ERROR loading image file:");
				log(IMG_GetError());
			}
		} else {
			log("ERROR opening image file.");
		}

		this->scene = SCENE_TITLESCREEN;
		this->init_titlescreen();

		return this->works;
}

Rocketz::~Rocketz() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Rocketz::~Rocketz()");
	#endif // WITH_DEBUGMSG
	if (this->with_sound) delete this->music_title;
}

bool Rocketz::init_titlescreen() {
	// INIT EFFUXES:
		this->effux_circles = new EffuxCircles(this->display);
	// LOAD AUDIO AND START MUSIC:
		if (this->with_sound) {
			this->music_title = new Audio;
			this->music_title->load_file(FILENAME_MUSIC_TITLE);
			this->music_title->play();
		}
	return true;	// TODO
}

bool Rocketz::deinit_titlescreen() {
	// FREE AUDIO AND STOP MUSIC:
		if (this->with_sound) delete this->music_title;
	// DEINIT EFFUXES:
		delete this->effux_circles;
	return true;	// TODO
}

bool Rocketz::init_gameplay() {
	// CREATE ROCKET:
		//this->rocket = new Rocket();
		this->rocket = new Triangle2D;
		Vertex2D *v1 = new Vertex2D;
		Vertex2D *v2 = new Vertex2D;
		Vertex2D *v3 = new Vertex2D;
		v1->x = 100;
		v1->y = 100;
		v2->x = 10;
		v2->y = 10;
		v3->x = 10;
		v3->y = 100;
		this->rocket->set_vertexes(v1, v2, v3);
	// LOAD AUDIO AND PLAY MUSIC:
		if (this->with_sound) {
			this->music_gameplay = new Audio;
			this->music_gameplay->load_file(FILENAME_MUSIC_GAMEPLAY);
			this->music_gameplay->play();
		}
	return true;	// TODO
}

bool Rocketz::deinit_gameplay() {
	// DELETE ROCKET:
		delete this->rocket;
	// FREE AUDIO AND STOP MUSIC:
		if (this->with_sound) delete this->music_gameplay;
	return true;	// TODO
}

bool Rocketz::mainloop() {
	//timeline.init();
	while (!this->mainloop_done and this->works) {
		handle_events();
			switch (this->scene) {
				case SCENE_TITLESCREEN:
					// DRAW EFFUX:
						this->effux_circles->execute(SDL_GetTicks()/3.0, true);
						SDL_RenderCopy(this->display->sdlrenderer, this->effux_circles->sdltexture, NULL, NULL);
					// DRAW TITLESCREEN PICTURE:
						SDL_RenderCopy(this->display->sdlrenderer, this->pic_titlescreen, NULL, NULL);
					// CHECK USER INPUT:
						if (this->keyboard->key_ENTER_down) {
							this->scene = SCENE_GAMEPLAY;
							this->deinit_titlescreen();
							this->init_gameplay();
						}
						if (this->keyboard->key_ESC_down)
							this->mainloop_done = true;
					break;
				case SCENE_GAMEPLAY:
					// MOVE STUFF:
						// Move rockets:
							//if (this->keyboard->key_UP_down) this->rocket->y -= 1;
							//if (this->keyboard->key_DOWN_down) this->rocket->y += 1;
							//if (this->keyboard->key_LEFT_down) this->rocket->x -= 1;
							//if (this->keyboard->key_RIGHT_down) this->rocket->x += 1;
							this->rocket->rotate(50);
							#ifdef WITH_DEBUGMSG
								//debugmsg("Rocket X:" + std::to_string(this->rocket->x));
								//debugmsg("Rocket Y:" + std::to_string(this->rocket->y));
							#endif // WITH_DEBUGMSG
						// Move bullets:
							// TODO
						// Move rogues:
							// TODO
					// DRAW STUFF:
						// Draw level:
							// Draw parallax background:
								//for (unsigned int layernum = 0; layernum < this->gameplay->level->backgrounds.size(); layernum++) {
									// Calculate offset where to draw surface from
									// draw surface this->gameplay->level->backgrounds[layernum];
								//}
							// Draw player rockets:
								//this->display->draw_polygon(this->rocket);
								this->display->draw_triangle(this->rocket);

							// Draw bullets:
								//for (unsigned int playernum = 0; playernum < this->gameplay->players.size(); playernum++) {
								//		for (unsigned int bulletnum = 0; bulletnum < this->gameplay->bulletnum.size(); bulletnum++) {
								//			// TODO: Draw player bullet
								//		}
								//}
								//for (unsigned int layernum = 0; layernum < this->gameplay->level->backgrounds.size(); layernum++) {
								//}
							// Draw rogues:
								// TODO
					// CHECK USER INPUT:
						if (this->keyboard->key_ESC_down) {
							this->scene = SCENE_TITLESCREEN;
							this->deinit_gameplay();
							this->init_titlescreen();
							this->keyboard->key_ESC_down = false;	// FIXME: keydown event keeps looping
						}
					break;
				case SCENE_SHOP:
					// Show mouse pointer
					break;
			}
			this->display->refresh();
	}
	return this->works;
}
