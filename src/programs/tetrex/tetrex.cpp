#include "tetrex.hpp"
#include "display.hpp"

void Bucket::generate_shapes() {
	// TODO: no duplicates
}

void Bucket::check_fills() {
}

Tetrex::Tetrex() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "Tetrex";
		this->version = "0.0002";
}

Tetrex::~Tetrex() {
}

bool Tetrex::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(50);
		//this->display->resizable_window = false;
		//this->display->vsync = true;
		//this->display->mousecursor_visible = false;
		//this->display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool Tetrex::init_titlescreen() {
}

bool Tetrex::deinit_titlescreen() {
}

bool Tetrex::init_gameplay() {
}

bool Tetrex::deinit_gameplay() {
}

bool Tetrex::mainloop() {
	while (!this->mainloop_done and this->works) {
		get_events();
		// If space, drop block immediately
		// bucket.check_fills();
		// If down, drop block faster
		// If left, move block left
		// If right, move block right
		// If V, rotate block right
		// If F, rotate block left
		// If Esc, quit/pause
		//this->display->clearscreen();
		this->display->refresh();
	}
	return this->works;
}
