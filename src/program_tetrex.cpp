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
		// If space, drop block immediately
		// If down, drop block faster
		// If left, move block left
		// If right, move block right
		// If V, rotate block right
		// If F, rotate block left
		// If Esc, quit/pause
		this->display->refresh();
	}
	return this->works;
}
