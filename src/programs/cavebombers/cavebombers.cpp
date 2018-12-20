#include "cavebombers.hpp"
#include "display.hpp"

Cavebombers::Cavebombers() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "CaveBombers";
		this->version = "0.0002";
}

Cavebombers::~Cavebombers() {
}

bool Cavebombers::init() {
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

bool Cavebombers::mainloop() {
	while (!this->mainloop_done and this->works) {
		get_events();
		this->display->refresh();
	}
	return this->works;
}
