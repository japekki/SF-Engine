/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a pinball game.
*/

#include "program_pinball.hpp"

void Gameplay::run() {
	// move ball(s)
	// check where every ball is
	// update score
	// update lcd
	// if all player->balls_left == 0 this->gameover = true;
}

Pinball::Pinball() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "Pinball";
		this->version = "0.0001";
}

Pinball::~Pinball() {
}

bool Pinball::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(40);
		//this->display->set_fullscreen(true);

	// LOAD AUDIO FILES:
		//this->music_title = this->audio->load_mp3(FILENAME_MUSIC_TITLE);

	// LOAD IMAGE FILES:
		//pic_titlescreen = load_image(FILENAME_PIC_TITLESCREEN);
		//if (pic1 == NULL) {
		//  log(MSG_QUITERROR);
		//  this->works = false;
		//}
		//SDL_Surface *pic_titlescreen;
		//SDL_RWops *rwop;
		//rwop = SDL_RWFromFile(FILENAME_PIC_TITLESCREEN, "rb");
		//pic_titlescreen = IMG_LoadPNG_RW(rwop);
		//pic_titlescreen = IMG_LoadPNM_RW(rwop);
		//if(!pic_titlescreen) {
		//	log("ERROR loading image:");
		//	log(IMG_GetError());
		//}

	//CREATE SCENES:
		//Scene scene1();
		//extern Entity testiobjekti;
		//testiobjekti.loadfromfile("../data/cube.obj");
		//testiobjekti.surface = monitor.sdlsurface;
		//testiobjekti.polygonshadestyle = POLYGON_SHADESTYLE_WIREFRAME;
		//scene1.add_entity(olio1);

	// CREATE 3D MODELS:

	// INIT EFFUXES:

	Program::init();
	return this->works;
}

bool Pinball::mainloop() {
	while (!this->mainloop_done and this->works) {
		handle_events();
		//gameplay->run();
		// if shift play_sound(sound_flipper)
		// if space play_sound(push)
		this->display->refresh();
	}
	return this->works;
}
