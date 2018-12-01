#include "program_sfedemo.hpp"

SFEdemo::SFEdemo() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "SFE demo";
		this->version = "0.0001";
}

SFEdemo::~SFEdemo() {
}

bool SFEdemo::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(50);
		//this->display->vsync = true;
		//this->display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool SFEdemo::mainloop() {
	while (!this->mainloop_done and this->works) {
		handle_events();
		this->display->refresh();
	}
	return this->works;
}
