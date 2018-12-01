#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "options.hpp"
#include "program_rocketz.hpp"
#include "misc.hpp"
#include "geom.hpp"

void Gameplay::execute() {
	// MOVE STUFF:
		// Move vehicles:
			//if (this->keyboard->key_UP_down) this->rocket->y -= 1;
			//if (this->keyboard->key_DOWN_down) this->rocket->y += 1;
			//if (this->keyboard->key_LEFT_down) this->rocket->x -= 1;
			//if (this->keyboard->key_RIGHT_down) this->rocket->x += 1;
			//this->rocket->rotate(10);
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
				//this->display->draw_triangle(this->rocket);

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
}

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
		this->display->set_desiredfps(25);
		//this->display->vsync = true;
		//this->display->set_fullscreen(true);
		Program::init();

		// INIT FONT SYSTEM:
			if(TTF_Init() == -1) {
				log("Error in TTF_Init:");
				log(TTF_GetError());
				this->works = false;
				//exit(2);
			}

		this->init_titlescreen();
		this->scene = SCENE_TITLESCREEN;

		return this->works;
}

Rocketz::~Rocketz() {
	#ifdef WITH_DEBUGMSG
		debugmsg("Rocketz::~Rocketz()");
	#endif // WITH_DEBUGMSG
	// DEINIT FONT SYSTEM:
		TTF_Quit();
}

bool Rocketz::init_titlescreen() {
	// LOAD IMAGE FILES:
		this->pic_titlescreen = this->display->load_texture(FILENAME_PIC_TITLESCREEN);
		this->pic_titlescreen_with_text = this->display->load_texture(FILENAME_PIC_TITLESCREEN_WITH_TEXT);

	// INIT EFFUXES:
		this->effux_circles = new EffuxCircles(this->display);
		this->effux_textscroller_japesoft = new EffuxTextscroller(this->display, FILENAME_FONT_XENOSPHERE, 24, TEXTALIGN_CENTER, SCROLLSTYLE_FADEFLASH, {120, 230, 120}, this->multilinetext_japesoft);
		this->effux_textscroller_poem = new EffuxTextscroller(this->display, FILENAME_FONT_MODENINE, 18, TEXTALIGN_CENTER, SCROLLSTYLE_EQUAL, {255, 255, 128}, this->multilinetext_poem);
		this->effux_textscroller_credits = new EffuxTextscroller(this->display, FILENAME_FONT_XENOSPHERE, 24, TEXTALIGN_CENTER, SCROLLSTYLE_EQUAL, {120, 120, 230}, this->multilinetext_credits);

		/*
		this->rocket = new Triangle2D;
		Vertex2D v1;
		Vertex2D v2;
		Vertex2D v3;
		v1.x = 100;
		v1.y = 100;
		v2.x = 10;
		v2.y = 10;
		v3.x = 10;
		v3.y = 100;
		this->rocket->set_vertexes(v1, v2, v3);
		*/

	// LOAD AUDIO AND START MUSIC:
		if (this->with_sound) {
			this->music_title = new Audio;
			this->music_title->load_file(FILENAME_MUSIC_TITLE);
			this->music_title->play();
		}
		this->song_start_timestamp = SDL_GetTicks();	// used for syncing the text scroller with title music

	return true;	// TODO
}

bool Rocketz::deinit_titlescreen() {
	// FREE AUDIO AND STOP MUSIC:
		if (this->with_sound) delete this->music_title;
	// DEINIT EFFUXES:
		delete this->effux_circles;
		delete this->effux_textscroller_japesoft;
		delete this->effux_textscroller_poem;
		delete this->effux_textscroller_credits;
	// FREE TEXTURES:
		SDL_DestroyTexture(this->pic_titlescreen);
		SDL_DestroyTexture(this->pic_titlescreen_with_text);
	return true;	// TODO
}

bool Rocketz::init_gameplay() {
	// CREATE ROCKET:
		//this->rocket = new Rocket();
		/*
		this->rocket = new Triangle2D;
		Vertex2D v1;
		Vertex2D v2;
		Vertex2D v3;
		v1.x = 100;
		v1.y = 100;
		v2.x = 10;
		v2.y = 10;
		v3.x = 10;
		v3.y = 100;
		this->rocket->set_vertexes(v1, v2, v3);
		*/
	// LOAD AUDIO AND PLAY MUSIC:
		/*
		if (this->with_sound) {
			this->music_gameplay = new Audio;
			this->music_gameplay->load_file(FILENAME_MUSIC_GAMEPLAY);
			this->music_gameplay->play();
		}
		*/
	return true;	// TODO
}

bool Rocketz::deinit_gameplay() {
	// DELETE ROCKET:
		//delete this->rocket;
	// FREE AUDIO AND STOP MUSIC:
		//if (this->with_sound) delete this->music_gameplay;
	return true;	// TODO
}

void Rocketz::titlescreen_effux(unsigned int time) {
	// DRAW EFFUX CIRCLES:
		this->effux_circles->calculate(time/3.0, true);
		SDL_RenderCopy(this->display->sdlrenderer, this->effux_circles->sdltexture, NULL, NULL);
}

void Rocketz::titlescreen_textscroller_japesoft(unsigned int time) {
	// DRAW EFFUX TEXTSCROLLER:
		// When scroll starts, y needs to be display height
		// When y is 0, text touches screen top edge
		// When scroll ends, y needs to be: - text_height
		int full_height;
		full_height = this->display->height + this->effux_textscroller_japesoft->get_height();
		int text_y;
		text_y = this->display->height - (full_height / 15000.0 * time);
		this->display->clearscreen();
		this->effux_textscroller_japesoft->draw(text_y);
}

void Rocketz::titlescreen_textscroller_poem(unsigned int time) {
	// DRAW EFFUX TEXTSCROLLER:
		// When scroll starts, y needs to be display height
		// When y is 0, text touches screen top edge
		// When scroll ends, y needs to be: - text_height
		int full_height;
		full_height = this->display->height + this->effux_textscroller_poem->get_height();
		int text_y;
		text_y = this->display->height - (full_height / 15000.0 * time);
		this->effux_textscroller_poem->draw(text_y);
}

void Rocketz::titlescreen_textscroller_credits(unsigned int time) {
	// DRAW EFFUX TEXTSCROLLER:
		// When scroll starts, y needs to be display height
		// When y is 0, text touches screen top edge
		// When scroll ends, y needs to be: - text_height
		int full_height;
		full_height = this->display->height + this->effux_textscroller_credits->get_height();
		int text_y;
		text_y = this->display->height - (full_height / 15500.0 * time);
		this->effux_textscroller_credits->draw(text_y);
}

bool Rocketz::mainloop() {
	while (!this->mainloop_done and this->works) {
		handle_events();
			switch (this->scene) {
				case SCENE_TITLESCREEN:

					#define TIMESTAMP_JAPESOFT 0		// ~0:00
					#define TIMESTAMP_BALL1 15300		// ~0:15
					#define TIMESTAMP_TEXT 46000		// ~0:46
					#define TIMESTAMP_BALL2 61300		// ~1:01
					#define TIMESTAMP_CREDITS 92000		// ~1:32
					#define TIMESTAMP_BALL3 107500		// ~1:47
					#define TIMESTAMP_END 167000		// ~2:47

					unsigned int time_elapsed;
					time_elapsed = SDL_GetTicks() - this->song_start_timestamp;

					if (time_elapsed >= TIMESTAMP_JAPESOFT and time_elapsed < TIMESTAMP_BALL1) {
						this->titlescreen_textscroller_japesoft(time_elapsed);
					}
					else if (time_elapsed >= TIMESTAMP_BALL1 and time_elapsed < TIMESTAMP_TEXT) {
						this->titlescreen_effux(time_elapsed);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(this->display->sdlrenderer, this->pic_titlescreen_with_text, NULL, NULL);
					}
					else if (time_elapsed >= TIMESTAMP_TEXT and time_elapsed < TIMESTAMP_BALL2) {
						this->titlescreen_effux(time_elapsed);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(this->display->sdlrenderer, this->pic_titlescreen, NULL, NULL);
						this->titlescreen_textscroller_poem(time_elapsed - TIMESTAMP_TEXT);
					}
					else if (time_elapsed >= TIMESTAMP_BALL2 and time_elapsed < TIMESTAMP_CREDITS) {
						this->titlescreen_effux(time_elapsed);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(this->display->sdlrenderer, this->pic_titlescreen_with_text, NULL, NULL);
					}
					else if (time_elapsed >= TIMESTAMP_CREDITS and time_elapsed < TIMESTAMP_BALL3) {
						this->titlescreen_effux(time_elapsed);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(this->display->sdlrenderer, this->pic_titlescreen, NULL, NULL);
						this->titlescreen_textscroller_credits(time_elapsed - TIMESTAMP_CREDITS);
					}
					else if (time_elapsed >= TIMESTAMP_BALL3 and time_elapsed < TIMESTAMP_END) {
						this->titlescreen_effux(time_elapsed);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(this->display->sdlrenderer, this->pic_titlescreen_with_text, NULL, NULL);
							//Coordinategrid grid = new Coordinategrid(-100, 100, -100, 100);
							//this->rocket->rotate(50);
							//this->display->draw_triangle(this->rocket);
					}
					else if (time_elapsed >= TIMESTAMP_END) {
						// when background music has played, start arcade self play demo:
						//this->scene = SCENE_SELFPLAY;
					}

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
					//this->gameplay->execute();
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
