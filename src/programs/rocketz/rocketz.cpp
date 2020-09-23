#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#include "grapher.hpp"
#include "rocketz.hpp"
#include "misc.hpp"
#include "geometry.hpp"
#include "color.hpp"
#include "filenames.hpp"
#include "effux_circles.hpp"
#include "effux_textscroller.hpp"
#include "gameplay.hpp"
#include "display.hpp"
#include "audio.hpp"

Rocketz::Rocketz(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "RocketZ";
		version = "0.0025";
}

bool Rocketz::init() {
	// SET UP DISPLAY DEVICE:
		display->set_width(800);
		display->set_height(600);
		display->set_desiredfps(50);
		display->resizable_window = true;
		display->vsync = true;
		display->mousecursor_visible = false;
		display->set_fullscreen(false);
		Program::init();

		display->load_icon(FILENAME_ICON);
		grapher::init_fontsystem();

		// INIT AUDIO:
			audio = new Audio(true, MIX_INIT_MOD | MIX_INIT_MP3);	// TODO: WAV?

		// INIT JUKEBOX:
			jukebox = new Jukebox(audio);
			std::string filepath_music = get_cmdline_parameter_value(argc, argv, "musicpath");
			if (filepath_music.size() > 0) {
				log("Creating playlist from: " + filepath_music);
				jukebox->create_playlist(filepath_music);
				if (jukebox->playlist.size() < 1)
					log("No files found from: " + filepath_music);
			}
			// If error while fetching file list, use default music folder:
			else {
				log("Using default music from: " + this->filepath_music);
				jukebox->create_playlist(this->filepath_music);
			}

		// START FROM TITLESCREEN:
			this->init_titlescreen();
			scene = SCENE_TITLESCREEN;

		// START FROM GAMEPLAY:
			//gameplay = new Gameplay(display, audio, jukebox, keyboard, mouse, joystick);
			//gameplay->filepath_music = "";
			// Play:
				//gameplay->setup_gameplay();
				//scene = SCENE_GAMEPLAY;
			// Demoplay:
				//gameplay->setup_demoplay();
				//scene = SCENE_DEMOPLAY;

		return this->works;
}

// FIXME: Sometimes resets game/demoplay instead of going to title screen
void Rocketz::reset() {
	switch (scene) {
		case SCENE_NONE:
			break;
		case SCENE_PAUSE:
			break;
		case SCENE_TITLESCREEN:
			this->deinit_titlescreen();
			break;
		case SCENE_SETTINGS:
			break;
		case SCENE_GAMEPLAY:
		case SCENE_DEMOPLAY:
			delete gameplay;
			break;
		case SCENE_SHOP:
			break;
		case SCENE_REPLAY:
			break;
	}
	// START FROM TITLESCREEN:
		scene = SCENE_TITLESCREEN;
		this->init_titlescreen();
}

Rocketz::~Rocketz() {
	grapher::deinit_fontsystem();
	delete jukebox;
	delete audio;
}

bool Rocketz::resize_titlescreen() {
	// LOAD FONTS:
		font_xenosphere_huge = grapher::load_font(FILENAME_FONT_XENOSPHERE, display->width / 10);
		font_xenosphere_small = grapher::load_font(FILENAME_FONT_XENOSPHERE, display->width / 30);
		font_glasstty_big = grapher::load_font(FILENAME_FONT_GLASSTTY, display->width / 20);
		font_modenine_small = grapher::load_font(FILENAME_FONT_MODENINE, display->width / 40);
		//font_xenosphere_big = display->load_font(FILENAME_FONT_XENOSPHERE, display->width / 20);
		//font_modenine_tiny = display->load_font(FILENAME_FONT_MODENINE, display->width / 80);

	// SETUP EFFUXES:
		effux_circles->setup(display->renderer, display->width, display->height);
		effux_textscroller_japekslab->setup(display->renderer, display->width, display->height, font_glasstty_big, TEXTALIGN_CENTER, SCROLLSTYLE_FADEFLASH, SDLCOLOR_GREEN1, multilinetext_japekslab);
		effux_textscroller_poem->setup(display->renderer, display->width, display->height, font_modenine_small, TEXTALIGN_CENTER, SCROLLSTYLE_EQUAL, SDLCOLOR_GOLD, multilinetext_poem);
		effux_textscroller_credits->setup(display->renderer, display->width, display->height, font_glasstty_big, TEXTALIGN_CENTER, SCROLLSTYLE_EQUAL, SDLCOLOR_GREEN1, multilinetext_credits);

	// FREE TEXTURES:
		if (texture_alphacircle != nullptr) SDL_DestroyTexture(texture_alphacircle);
		if (textbox_newgame->texture != nullptr) SDL_DestroyTexture(textbox_newgame->texture);
		if (textbox_title->texture != nullptr) SDL_DestroyTexture(textbox_title->texture);

	// CREATE STATIC TEXTURES:

		// ALPHA CIRCLE MASK:
		texture_alphacircle = grapher::create_alphacircle(display->renderer, display->width, display->height, 0);

		// TITLE TEXT:
		textbox_title->texture = grapher::create_textline_texture(display->renderer, "RocketZ", font_xenosphere_huge, SDLCOLOR_GREEN1);
		SDL_QueryTexture(textbox_title->texture, NULL, NULL, &textbox_title->rect.w, &textbox_title->rect.h);
		textbox_title->rect.x = (display->width - textbox_title->rect.w) / 2;	// Centered
		textbox_title->rect.y = 0;

		// TITLESCREEN MENU://
		textbox_newgame->texture = grapher::create_textmultiline_texture(display->renderer, menutext, font_modenine_small, SDLCOLOR_CRTBLUE);
		SDL_QueryTexture(textbox_newgame->texture, NULL, NULL, &textbox_newgame->rect.w, &textbox_newgame->rect.h);
		textbox_newgame->rect.x = (display->width - textbox_newgame->rect.w) / 2;	// Centered
		textbox_newgame->rect.y = textbox_title->rect.h + (display->height - textbox_title->rect.h - textbox_newgame->rect.h) / 2;

	return true;	// TODO
}

bool Rocketz::init_titlescreen() {

	textbox_newgame = new Simplesprite();
	textbox_title = new Simplesprite();

		effux_circles = new EffuxCircles();
			// TODO: optimize for visible center hole in titlescreen instead of drawing whole screen
				effux_circles->viewport->x = 100;
				effux_circles->viewport->y = 100;
				effux_circles->viewport->w = 100;
				effux_circles->viewport->h = 100;
		effux_textscroller_japekslab = new EffuxTextscroller();
		effux_textscroller_poem = new EffuxTextscroller();
		effux_textscroller_credits = new EffuxTextscroller();

	this->resize_titlescreen();

	// LOAD AND START MUSIC:
		music_title = audio->load_music(FILENAME_MUSIC_TITLE);
		audio->play(music_title, 0);
		song_start_timestamp = SDL_GetTicks();	// used for syncing the text scroller with title music

	return true;	// TODO
}

bool Rocketz::deinit_titlescreen() {

	// STOP MUSIC AND FREE AUDIO:
		audio->free_music(music_title);
		music_title = nullptr;

	// DEINIT EFFUXES:
		if (effux_circles != nullptr) {
			delete effux_circles;
			effux_circles = nullptr;
		}
		if (effux_textscroller_japekslab != nullptr) {
			delete effux_textscroller_japekslab;
			effux_textscroller_japekslab = nullptr;
		}
		if (effux_textscroller_poem != nullptr) {
			delete effux_textscroller_poem;
			effux_textscroller_poem = nullptr;
		}
		if (effux_textscroller_credits != nullptr) {
			delete effux_textscroller_credits;
			effux_textscroller_credits = nullptr;
		}

	// FREE TEXTURES:
		if (texture_alphacircle != nullptr) {
			SDL_DestroyTexture(texture_alphacircle);
			texture_alphacircle = nullptr;
		}
		if (textbox_newgame != nullptr) {
			if (textbox_newgame->texture != nullptr) {
				//SDL_DestroyTexture(textbox_newgame->texture);
				delete textbox_newgame;
				textbox_newgame = nullptr;
			}
		}
		if (textbox_title != nullptr) {
			//if (textbox_title->texture != nullptr) SDL_DestroyTexture(textbox_title->texture);
			delete textbox_title;
			textbox_title = nullptr;
		}

	return true;	// TODO
}

void Rocketz::titlescreen_textscroller_japekslab(uint32_t time) {
	int full_height = display->height + effux_textscroller_japekslab->get_height();
	effux_textscroller_japekslab->execute(display->height - (full_height / 15500.0 * time));
}

void Rocketz::titlescreen_textscroller_poem(uint32_t time) {
	int full_height = display->height + effux_textscroller_poem->get_height();
	effux_textscroller_poem->execute(display->height - (full_height / 15500.0 * time));
}

void Rocketz::titlescreen_textscroller_credits(uint32_t time) {
	int full_height = display->height + effux_textscroller_credits->get_height();
	effux_textscroller_credits->execute(display->height - (full_height / 15500.0 * time));
}

bool Rocketz::mainloop() {
	while (!mainloop_done and this->works) {

		uint32_t time_elapsed;
		time_elapsed = SDL_GetTicks() - song_start_timestamp;	// TODO
		//time_elapsed = TIMESTAMP_CIRCLES1;
		//time_elapsed = SDL_GetTicks() - song_start_timestamp + TIMESTAMP_CREDITS;
		//time_elapsed = (SDL_GetTicks() - song_start_timestamp) % TIMESTAMP_END;
		//time_elapsed = (SDL_GetTicks() - song_start_timestamp) * 40;
		//time_elapsed = SDL_GetTicks() - song_start_timestamp + TIMESTAMP_END - 1000;
		//time_elapsed = SDL_GetTicks() % TIMESTAMP_END - 1000;
		//time_elapsed = SDL_GetTicks() - song_start_timestamp + TIMESTAMP_FADEOUT - 200;

		get_events();

		// CHECK USER INPUT:
			// TODO: if or else if ?
			if (keyboard->get_presscount(SDL_SCANCODE_PRINTSCREEN)) {
				display->save_screenshot(name + "-" + version + "_screenshot_" + get_current_timestamp() + "_" + std::to_string(display->framecounter) + ".bmp");
			}
			else if (keyboard->get_presscount(SDL_SCANCODE_F1)) {
				paused = false;
				scene = SCENE_GAMEPLAY;
				this->deinit_titlescreen();
				gameplay = new Gameplay(display, audio, jukebox, keyboard, mouse, joystick);
				gameplay->setup_gameplay();
			}
			else if (keyboard->get_presscount(SDL_SCANCODE_F2)) {
				paused = false;
				scene = SCENE_DEMOPLAY;
				deinit_titlescreen();
				gameplay = new Gameplay(display, audio, jukebox, keyboard, mouse, joystick);
				gameplay->setup_demoplay();
			}
			else if (keyboard->get_presscount(SDL_SCANCODE_F5)) {
				paused = false;
				this->reset();
			}
			if (keyboard->get_presscount(SDL_SCANCODE_F11)) {
				display->fullscreenmode_desktop = false;
				display->toggle_fullscreen();
			}
			if (keyboard->get_presscount(SDL_SCANCODE_F12)) {
				display->fullscreenmode_desktop = true;
				display->toggle_fullscreen();
			}
			if (keyboard->get_presscount(SDL_SCANCODE_PAUSE) or keyboard->get_presscount(SDL_SCANCODE_P)) {
				paused = !this->paused;
				if (this->paused) {
					previous_scene = this->scene;
					scene = SCENE_PAUSE;
				}
				else
					scene = previous_scene;
			}

			switch (scene) {
				case SCENE_PAUSE:
					//SDL_WaitEvent(SDL_Event* event);	// TODO
					break;
				case SCENE_TITLESCREEN:
					if (keyboard->get_presscount(SDL_SCANCODE_ESCAPE))
						mainloop_done = true;
					if (display->is_resized()) this->resize_titlescreen();

					if (time_elapsed >= TIMESTAMP_JAPEKSLAB and time_elapsed < TIMESTAMP_CIRCLES1) {
						display->clearscreen();
						titlescreen_textscroller_japekslab(time_elapsed);
					}

					else if (time_elapsed >= TIMESTAMP_CIRCLES1 and time_elapsed < TIMESTAMP_TEXT) {
						effux_circles->execute_OLD(time_elapsed/3);
						SDL_RenderCopy(display->renderer, effux_circles->texture, NULL, NULL);
						//titlescreen_effux(SDL_GetTicks());
						// DRAW TITLESCREEN PICTURE:
                            // TODO:
                            // - Get max from width or height and don't calculate/draw circle effect if pixels not visible
							SDL_RenderCopy(display->renderer, texture_alphacircle, NULL, NULL);
							//SDL_SetRenderTarget(display->renderer, texture_alphacircle);
							//SDL_SetRenderTarget(display->renderer, NULL);
							grapher::draw_texture(display->renderer, textbox_title);
							grapher::draw_texture(display->renderer, textbox_newgame);
					}

					else if (time_elapsed >= TIMESTAMP_TEXT and time_elapsed < TIMESTAMP_CIRCLES2) {
						effux_circles->execute_OLD(time_elapsed/3);
						SDL_RenderCopy(display->renderer, effux_circles->texture, NULL, NULL);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(display->renderer, texture_alphacircle, NULL, NULL);

						titlescreen_textscroller_poem(time_elapsed - TIMESTAMP_TEXT);
					}

					else if (time_elapsed >= TIMESTAMP_CIRCLES2 and time_elapsed < TIMESTAMP_CREDITS) {
						effux_circles->execute_OLD(time_elapsed/3);
						SDL_RenderCopy(display->renderer, effux_circles->texture, NULL, NULL);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(display->renderer, texture_alphacircle, NULL, NULL);
							grapher::draw_texture(display->renderer, textbox_title);
							grapher::draw_texture(display->renderer, textbox_newgame);
					}

					else if (time_elapsed >= TIMESTAMP_CREDITS and time_elapsed < TIMESTAMP_CIRCLES3) {
						effux_circles->execute_OLD(time_elapsed/3);
						SDL_RenderCopy(display->renderer, effux_circles->texture, NULL, NULL);
						// DRAW TITLESCREEN PICTURE:
							SDL_RenderCopy(display->renderer, texture_alphacircle, NULL, NULL);
						titlescreen_textscroller_credits(time_elapsed - TIMESTAMP_CREDITS);
					}

					else if (time_elapsed >= TIMESTAMP_CIRCLES3 and time_elapsed < TIMESTAMP_FADEOUT) {
						effux_circles->execute_OLD(time_elapsed/3);
						SDL_RenderCopy(display->renderer, effux_circles->texture, NULL, NULL);
						// DRAW TITLESCREEN TEXT:
							SDL_RenderCopy(display->renderer, texture_alphacircle, NULL, NULL);
							grapher::draw_texture(display->renderer, textbox_title);
							grapher::draw_texture(display->renderer, textbox_newgame);
					}

					else if (time_elapsed >= TIMESTAMP_FADEOUT and time_elapsed < TIMESTAMP_END) {
						// DRAW CIRCLES:
							effux_circles->execute_OLD(time_elapsed/3);
							SDL_RenderCopy(display->renderer, effux_circles->texture, NULL, NULL);
						// DRAW TEXTS:
							SDL_RenderCopy(display->renderer, texture_alphacircle, NULL, NULL);
							grapher::draw_texture(display->renderer, textbox_title);
							grapher::draw_texture(display->renderer, textbox_newgame);
						// FADE:
							//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);	// Enable alpha
							SDL_SetRenderDrawBlendMode(display->renderer, SDL_BLENDMODE_BLEND);
							display->with_fade = true;
							display->set_fade(255.0 / (TIMESTAMP_END - TIMESTAMP_FADEOUT) * (time_elapsed - TIMESTAMP_FADEOUT));
					}

					else if (time_elapsed >= TIMESTAMP_END) {
						// when background music has played, start arcade self play demo:
						scene = SCENE_DEMOPLAY;
						deinit_titlescreen();
						gameplay = new Gameplay(display, audio, jukebox, keyboard, mouse, joystick);
						gameplay->play_sound = false;
						gameplay->play_music = false;
						gameplay->setup_demoplay();
						gameplay->expiretime = TIMESTAMP_DEMOPLAY_END;
					}
					break;

				case SCENE_DEMOPLAY:
				case SCENE_GAMEPLAY:
					// Check if gameplay has finished:
					if ((gameplay->expiretime != 0 and time_elapsed >= gameplay->expiretime)
					or gameplay->execute()) {
						delete gameplay;
						// Jump to title screen:
							scene = SCENE_TITLESCREEN;
							this->init_titlescreen();
						// Restart gameplay:
							//gameplay = new Gameplay(display, audio, jukebox, keyboard, mouse, joystick);
							//if (scene == SCENE_DEMOPLAY)
							//	gameplay->setup_demoplay();
							//if (scene == SCENE_GAMEPLAY)
							//	gameplay->setup_gameplay();
					}
					break;

				case SCENE_SHOP:
					// shop->execute();
					break;
			}
			display->refresh();

	}
	return this->works;
}
