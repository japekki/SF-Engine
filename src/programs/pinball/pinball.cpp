#include <SDL_image.h>
#include <math.h>
#include "pinball.hpp"
#include "misc.hpp"
#include "display.hpp"

void Gameplay::run() {
	// move ball(s)
	// check where every ball is
	// update score
	// update LCD
	// if all player->balls_left == 0 this->gameover = true;
	// if shift play_sound(sound_flipper)
	// if space play_sound(push)
	// if too many pushes too fast then tilt()
}

Pinball::Pinball() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "Pinball";
		this->version = "0.0002";
}

Pinball::~Pinball() {
	//if (this->with_sound) delete this->music_level1;
}

bool Pinball::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(50);
		//this->display->resizable_window = false;
		//this->display->vsync = true;
		//this->display->mousecursor_visible = false;
		//this->display->set_fullscreen(true);

	// LOAD IMAGE FILES:

	// LOAD AUDIO FILES:

	// INIT EFFUXES:
		//this->music_level1->play();
		Program::init();
		return this->works;
}

bool Pinball::mainloop() {
	while (!this->mainloop_done and this->works) {
		get_events();
		//gameplay->run();

		this->display->refresh();
	}
	return this->works;
}
