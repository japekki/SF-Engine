/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a demo.
*/

#include "program_foobar.hpp"

Foobardemo::Foobardemo() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "Foobar demo";
		this->version = "0.0001";
}

Foobardemo::~Foobardemo() {
}

bool Foobardemo::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(40);
		//this->display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool Foobardemo::mainloop() {
	while (!this->mainloop_done and this->works) {
		handle_events();
		this->display->refresh();
	}
	return this->works;
}

