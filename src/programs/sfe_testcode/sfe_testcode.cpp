#include "sfe_testcode.hpp"
#include <SDL.h>
#include "display.hpp"

SFE_Testcode::SFE_Testcode(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "SFE Testcode";
		version = "0.0001";
}

SFE_Testcode::~SFE_Testcode() {
}

bool SFE_Testcode::init() {
	// SET UP DISPLAY DEVICE:
		display->set_width(640);
		display->set_height(480);
		display->set_desiredfps(0);	// Don't limit FPS
		display->resizable_window = false;
		//display->vsync = true;		// False by default, keep it false
		//display->mousecursor_visible = false;
		//display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool SFE_Testcode::mainloop() {
	while (!mainloop_done and this->works) {
		get_events();
		display->refresh();
	}
	return this->works;
}
