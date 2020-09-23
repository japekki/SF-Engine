#include "publiippari.hpp"
#include "display.hpp"
#include "filenames.hpp"

Faucet::Faucet() {
	// load faucet picture file
	//this->texture =
}

Faucet::~Faucet() {
	// free faucet picture
	//SDL_DestroyTexture(this->texture->texture);
}

void Faucet::drip() {
	// Make dropplet
	// Play drip sound
}

void Faucet::plumps() {
	// Play plumps sound
}

PubLiippari::PubLiippari(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "Pub Liippari Screensaver";
		version = "0.0002";
}

PubLiippari::~PubLiippari() {
}

bool PubLiippari::init() {
	// SET UP DISPLAY DEVICE:
		display->set_width(640);
		display->set_height(480);
		display->set_desiredfps(50);
		display->resizable_window = false;
		//display->vsync = true;
		//display->mousecursor_visible = false;
		//display->set_fullscreen(true);
	Program::init();

	// INIT OBJECTS:
		//logo.texture = this->display->load_texture(FILENAME_TEXTURE_LOGO);

	return this->works;
}

bool PubLiippari::mainloop() {
	while (!mainloop_done and this->works) {
		faucet.drip();
		faucet.plumps();
		// check if bucket full
		// draw faucet
		// draw beer
		// move and rotate logo
		// draw logo
		// move and rotate drunken fish
		// draw drunken fish
		get_events();
		display->refresh();
	}
	return this->works;
}
