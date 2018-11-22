/*
	SF-Engine

	This file has demo/game specific routines.

	This one is supposed to be a Tetris style game.
*/

#include "program_tetrex.hpp"

Tetrex::Tetrex() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "Tetrex";
		this->version = "0.0001";
}

Tetrex::~Tetrex() {
}

bool Tetrex::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(40);
		//this->display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool Tetrex::mainloop() {
	while (!this->mainloop_done and this->works) {
		handle_events();
		this->display->refresh();
	}
	return this->works;
}
