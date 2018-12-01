#include "program_publiippari.hpp"

void Faucet::drip() {
}

PubLiippari::PubLiippari() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "Pub Liippari Screensaver";
		this->version = "0.0001";
}

PubLiippari::~PubLiippari() {
}

bool PubLiippari::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(50);
		//this->display->vsync = true;
		//this->display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool PubLiippari::mainloop() {
	while (!this->mainloop_done and this->works) {
		handle_events();
		this->display->refresh();
	}
	return this->works;
}
