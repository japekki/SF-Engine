#include <math.h>
#include <SDL_image.h>
#include "pinball.hpp"
#include "misc.hpp"
#include "display.hpp"
#include "filenames.hpp"

Gameblob::Gameblob(Gameplay* gameplay) : Blob() {
	this->gameplay = gameplay;
}

Gameblob::~Gameblob() {
}

void Gameblob::draw() {
}

Ball::Ball(Gameplay* gameplay) : Gameblob(gameplay) {
	this->create_texture(20, 20);
}

Ball::~Ball() {
}

void Ball::create_texture(uint32_t width, uint32_t height) {
	sdltexture = grapher::create_solidcircle(gameplay->display->renderer, width, height, COLOR_GREY);
}

void Ball::draw() {
}

bool Highscore::load() {
	return true;	// TODO
}

bool Highscore::save() {
	return true;	// TODO
}

Level::Level(Gameplay* gameplay) {
	this->gameplay = gameplay;
	// Load background texture:
		background = grapher::load_texture(gameplay->display->renderer, FILENAME_TABLE_LEVEL1);
}

Level::~Level() {
	//
}

Gameplay::Gameplay(Display* display, Audio *audio) {
	this->display = display;
	this->audio = audio;

	level = new Level(this);

	// Create ball(s);
	balls_in_play.push_back(new Ball(this));

	font_lcd_huge = grapher::load_font(FILENAME_FONT_LCD, 20);

	// Create player(s):
		players.push_back(new Player());

	// Load and start music:
		music_gameplay = audio->load_music(FILENAME_MUSIC_LEVEL1);
		audio->play(music_gameplay, -1);
		//this->song_start_timestamp = SDL_GetTicks();	// used for syncing the text scroller with title music
}

void Gameplay::run() {
	// Check for gameover:
		//bool someone_has_balls = false;
		//for (unsigned char i=0; i<this->players.size(); i++)
		//	if (this->players[i)->balls_left > 0)
		//		this->someone_has_balls = true;
		//	if (!someone_has_balls)
		//		this->gameover = true;

	// move ball(s)
	// check where every ball is

	// if shift play_sound(sound_flipper)
	// if space play_sound(push)
	// if too many pushes too fast then tilt()

	// Draw LCD:
		grapher::draw_texture(display->renderer, grapher::create_textline_texture(display->renderer, "SCORE:", font_lcd_huge, SDLCOLOR_YELLOW), 10, 10);
		std::string score_str = std::to_string(this->players[0]->score++);
		//grapher::draw_texture(this->display->renderer, grapher::create_textline_texture(display->renderer, score_str.c_str() , font_lcd_huge, SDLCOLOR_YELLOW), 400, 10);
		balls_in_play[0]->draw();

	// Draw ball(s):
		for (unsigned char i=0; i<balls_in_play.size(); i++) {
			//balls_in_play[i)->draw();
			grapher::draw_texture(display->renderer, balls_in_play[i]->sdltexture, display->width/2 + int(display->width/2 * sin(0.001 * SDL_GetTicks())), 300);
		}

}

Gameplay::~Gameplay() {
	// STOP MUSIC AND FREE AUDIO:
		audio->free_music(music_gameplay);
		music_gameplay = nullptr;
		delete audio;	// FIXME: Segfault (or not?)
}

Pinball::Pinball(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "Pinball";
		version = "0.0002";
}

Pinball::~Pinball() {
	//if (with_audio) delete music_level1;
	grapher::deinit_fontsystem();
}

bool Pinball::init() {
	// SET UP DISPLAY DEVICE:
		display->set_width(640);
		display->set_height(480);
		display->set_desiredfps(50);
		//display->resizable_window = false;
		//display->vsync = true;
		//display->mousecursor_visible = false;
		//display->set_fullscreen(true);

	// INIT AUDIO:
		audio = new Audio(false, MIX_INIT_OGG);

	// LOAD IMAGE FILES:

	// INIT EFFUXES:
		//this->music_level1->play();
		Program::init();

		grapher::init_fontsystem();

		gameplay = new Gameplay(display, audio);

		return this->works;
}

bool Pinball::mainloop() {
	while (!mainloop_done and this->works) {
		get_events();
		display->clearscreen();
		gameplay->run();
		display->refresh();
	}
	return this->works;
}
