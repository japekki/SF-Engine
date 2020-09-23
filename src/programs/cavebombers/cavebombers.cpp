#include "cavebombers.hpp"
#include "display.hpp"

void Level::generate() {
	//
}

void Gameplay::init() {
	level->width = 100;
	level->height = 100;
}

Cavebombers::Cavebombers(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "Cave Bombers";
		version = "0.0002";
}

Cavebombers::~Cavebombers() {
}

bool Cavebombers::init() {
	// SET UP DISPLAY DEVICE:
		display->set_width(640);
		display->set_height(480);
		display->set_desiredfps(20);
		//display->resizable_window = false;
		//display->vsync = true;
		//display->mousecursor_visible = false;
		//display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool Cavebombers::mainloop() {
	while (!mainloop_done and this->works) {
		get_events();
		display->refresh();
	}
	return this->works;
}
