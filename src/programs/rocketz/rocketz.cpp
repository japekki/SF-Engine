#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "options.hpp"
#include "rocketz.hpp"
#include "misc.hpp"
#include "geom.hpp"

Rocketz::Rocketz() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "RocketZ";
		this->version = "0.0003";
		//this->with_sound = false;
}

bool Rocketz::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(800);
		this->display->set_height(600);
		this->display->set_desiredfps(50);
		//this->display->resizable_window = false;
		//this->display->vsync = true;
		//this->display->mousecursor_visible = false;
		//this->display->set_fullscreen(true);
		Program::init();

		// INIT FONT SYSTEM:
			if(TTF_Init() == -1) {
				log("Error in TTF_Init:");
				log(TTF_GetError());
				this->works = false;
				exit(EXIT_FAILURE);	// TODO: Exception handling
			}

		this->init_titlescreen();
		this->scene = SCENE_TITLESCREEN;

		return this->works;
}

Rocketz::~Rocketz() {
	// DEINIT FONT SYSTEM:
		TTF_Quit();
}

bool Rocketz::resize_titlescreen() {
	// LOAD FONTS:
			this->font_xenosphere_huge = TTF_OpenFont(FILENAME_FONT_XENOSPHERE, this->display->width / 10);
			if (this->font_xenosphere_huge == nullptr) {
				log("Error loading font.");
				this->works = false;
				exit(EXIT_FAILURE);	// TODO: Exception handling
			}
			/*
			this->font_xenosphere_big = TTF_OpenFont(FILENAME_FONT_XENOSPHERE, this->display->width / 20);
			if (this->font_xenosphere_big == nullptr) {
				log("Error loading font.");
				this->works = false;
				exit(EXIT_FAILURE);	// TODO: Exception handling
			}
			*/
			this->font_xenosphere_small = TTF_OpenFont(FILENAME_FONT_XENOSPHERE, this->display->width / 30);
			if (this->font_xenosphere_small == nullptr) {
				log("Error loading font.");
				this->works = false;
				exit(EXIT_FAILURE);	// TODO: Exception handling
			}
			this->font_modenine_small = TTF_OpenFont(FILENAME_FONT_MODENINE, this->display->width / 40);
			if (this->font_modenine_small == nullptr) {
				log("Error loading font.");
				this->works = false;
				exit(EXIT_FAILURE);	// TODO: Exception handling
			}

	// DEINIT EFFUXES:
		if (this->effux_circles != nullptr) delete this->effux_circles;
		if (this->effux_textscroller_japesoft != nullptr) delete this->effux_textscroller_japesoft;
		if (this->effux_textscroller_poem != nullptr) delete this->effux_textscroller_poem;
		if (this->effux_textscroller_credits != nullptr) delete this->effux_textscroller_credits;
	// FREE TEXTURES:
		if (this->texture_titlescreen != nullptr) SDL_DestroyTexture(this->texture_titlescreen);
		if (this->textbox_newgame.sdltexture != nullptr) SDL_DestroyTexture(this->textbox_newgame.sdltexture);
		if (this->textbox_title.sdltexture != nullptr) SDL_DestroyTexture(this->textbox_title.sdltexture);
	// CREATE STATIC TEXTURES:
		this->texture_titlescreen = create_alphacircle(this->display, 0);

		this->textbox_title.sdltexture = this->display->create_textline_texture("RocketZ", this->font_xenosphere_huge, {0x60, 0xd0, 0xa0});
		SDL_QueryTexture(this->textbox_title.sdltexture, NULL, NULL, &this->textbox_title.rect.w, &this->textbox_title.rect.h);
		this->textbox_title.rect.x = (this->display->width - this->textbox_title.rect.w) / 2;	// Centered
		this->textbox_title.rect.y = 0;

		this->textbox_newgame.sdltexture = this->display->create_textmultiline_texture("New game\n\nReplay\n\nSettings\n\nExit", this->font_xenosphere_small, {0x60, 0xd0, 0xa0});
		SDL_QueryTexture(this->textbox_newgame.sdltexture, NULL, NULL, &this->textbox_newgame.rect.w, &this->textbox_newgame.rect.h);
		this->textbox_newgame.rect.x = (this->display->width - this->textbox_newgame.rect.w) / 2;	// Centered
		this->textbox_newgame.rect.y = (this->display->height - this->textbox_newgame.rect.h) / 2;	// Centered

	// INIT EFFUXES:
		this->effux_circles = new EffuxCircles(this->display);	// TODO: optimize for visible center hole in titlescreen instead of drawing whole screen
		this->effux_textscroller_japesoft = new EffuxTextscroller(this->display, this->font_xenosphere_small, TEXTALIGN_CENTER, SCROLLSTYLE_FADEFLASH, {0x60, 0xd0, 0xa0}, this->multilinetext_japesoft);
		this->effux_textscroller_poem = new EffuxTextscroller(this->display, this->font_modenine_small, TEXTALIGN_CENTER, SCROLLSTYLE_EQUAL, {0xa8, 0xa8, 0x66}, this->multilinetext_poem);
		this->effux_textscroller_credits = new EffuxTextscroller(this->display, this->font_xenosphere_small, TEXTALIGN_CENTER, SCROLLSTYLE_EQUAL, {0x50, 0x50, 0xa0}, this->multilinetext_credits);

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
		return true;	// TODO
}

bool Rocketz::init_titlescreen() {
	this->resize_titlescreen();
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
		if (this->effux_circles != nullptr) delete this->effux_circles;
		if (this->effux_textscroller_japesoft != nullptr) delete this->effux_textscroller_japesoft;
		if (this->effux_textscroller_poem != nullptr) delete this->effux_textscroller_poem;
		if (this->effux_textscroller_credits != nullptr) delete this->effux_textscroller_credits;
	// FREE TEXTURES:
		if (this->texture_titlescreen != nullptr) SDL_DestroyTexture(this->texture_titlescreen);
		if (this->textbox_newgame.sdltexture != nullptr) SDL_DestroyTexture(this->textbox_newgame.sdltexture);
		if (this->textbox_title.sdltexture != nullptr) SDL_DestroyTexture(this->textbox_title.sdltexture);
	return true;	// TODO
}

bool Rocketz::init_gameplay() {
	this->gameplay = new Gameplay();
	// CREATE LEVEL:
		//this->randomlevelgenerator = new Randomlevelgenerator(1000, 1000);
		//this->randomlevelgenerator->generate();

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
	delete this->gameplay;
	//delete this->randomlevelgenerator;
	// DELETE ROCKET:
		//delete this->rocket;
	// FREE AUDIO AND STOP MUSIC:
		//if (this->with_sound) delete this->music_gameplay;
	return true;	// TODO
}

void Rocketz::titlescreen_effux(unsigned int time) {
	// DRAW EFFUX CIRCLES:
		this->effux_circles->draw(time/3.0, 1);
		SDL_RenderCopy(this->display->sdlrenderer, this->effux_circles->sdltexture, NULL, NULL);
}

void Rocketz::titlescreen_textscroller_japesoft(unsigned int time) {
	int full_height;
	full_height = this->display->height + this->effux_textscroller_japesoft->get_height();
	int text_y;
	text_y = this->display->height - (full_height / 15000.0 * time);
	this->effux_textscroller_japesoft->draw(text_y);
}

void Rocketz::titlescreen_textscroller_poem(unsigned int time) {
	int full_height;
	full_height = this->display->height + this->effux_textscroller_poem->get_height();
	int text_y;
	text_y = this->display->height - (full_height / 15000.0 * time);
	this->effux_textscroller_poem->draw(text_y);
}

void Rocketz::titlescreen_textscroller_credits(unsigned int time) {
	int full_height;
	full_height = this->display->height + this->effux_textscroller_credits->get_height();
	int text_y;
	text_y = this->display->height - (full_height / 15500.0 * time);
	this->effux_textscroller_credits->draw(text_y);
}

bool Rocketz::mainloop() {
	unsigned int time_elapsed;
	while (!this->mainloop_done and this->works) {
		get_events();
		if (this->keyboard->key_F11_down) {
			this->display->fullscreenmode_desktop = false;
			this->display->toggle_fullscreen();
			this->keyboard->key_F11_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_F12_down) {
			this->display->fullscreenmode_desktop = true;
			this->display->toggle_fullscreen();
			this->keyboard->key_F12_down = false;	// FIXME: keydown event keeps looping
		}

		switch (this->scene) {
			case SCENE_TITLESCREEN:
				if (this->display->is_resized()) this->resize_titlescreen();

				#define TIMESTAMP_JAPESOFT 0		// ~0:00
				#define TIMESTAMP_BALL1 15400		// ~0:15
				#define TIMESTAMP_TEXT 46000		// ~0:46
				#define TIMESTAMP_BALL2 61400		// ~1:01
				#define TIMESTAMP_CREDITS 92000		// ~1:32
				#define TIMESTAMP_BALL3 107500		// ~1:47
				#define TIMESTAMP_END 167400		// ~2:47

				time_elapsed = (SDL_GetTicks() - this->song_start_timestamp) % TIMESTAMP_END;
				//time_elapsed = (SDL_GetTicks() - this->song_start_timestamp + TIMESTAMP_BALL1) % TIMESTAMP_END;
				//time_elapsed = SDL_GetTicks() % TIMESTAMP_END;

				if (time_elapsed >= TIMESTAMP_JAPESOFT and time_elapsed < TIMESTAMP_BALL1) {
					this->display->clearscreen();
					this->titlescreen_textscroller_japesoft(time_elapsed);
				}
				else if (time_elapsed >= TIMESTAMP_BALL1 and time_elapsed < TIMESTAMP_TEXT) {
					this->titlescreen_effux(time_elapsed);
					// DRAW TITLESCREEN PICTURE:
						SDL_RenderCopy(this->display->sdlrenderer, this->texture_titlescreen, NULL, NULL);
						this->display->draw_texture(this->textbox_title);
						this->display->draw_texture(this->textbox_newgame);
				}
				else if (time_elapsed >= TIMESTAMP_TEXT and time_elapsed < TIMESTAMP_BALL2) {
					this->titlescreen_effux(time_elapsed);
					// DRAW TITLESCREEN PICTURE:
						SDL_RenderCopy(this->display->sdlrenderer, this->texture_titlescreen, NULL, NULL);
					this->titlescreen_textscroller_poem(time_elapsed - TIMESTAMP_TEXT);
				}
				else if (time_elapsed >= TIMESTAMP_BALL2 and time_elapsed < TIMESTAMP_CREDITS) {
					this->titlescreen_effux(time_elapsed);
					// DRAW TITLESCREEN PICTURE:
						SDL_RenderCopy(this->display->sdlrenderer, this->texture_titlescreen, NULL, NULL);
						this->display->draw_texture(this->textbox_title);
						this->display->draw_texture(this->textbox_newgame);
				}
				else if (time_elapsed >= TIMESTAMP_CREDITS and time_elapsed < TIMESTAMP_BALL3) {
					this->titlescreen_effux(time_elapsed);
					// DRAW TITLESCREEN PICTURE:
						SDL_RenderCopy(this->display->sdlrenderer, this->texture_titlescreen, NULL, NULL);
					this->titlescreen_textscroller_credits(time_elapsed - TIMESTAMP_CREDITS);
				}
				else if (time_elapsed >= TIMESTAMP_BALL3 and time_elapsed < TIMESTAMP_END) {
					this->titlescreen_effux(time_elapsed);
					// DRAW TITLESCREEN PICTURE:
						SDL_RenderCopy(this->display->sdlrenderer, this->texture_titlescreen, NULL, NULL);
						this->display->draw_texture(this->textbox_title);
						this->display->draw_texture(this->textbox_newgame);
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
				this->gameplay->execute();
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
