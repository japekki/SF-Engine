#include "publiippari.hpp"
#include "display.hpp"
#include "filenames.hpp"

Faucet::Faucet() {
	// load faucet picture file
	//this->texture =
}

Faucet::~Faucet() {
	// free faucet picture
	//SDL_DestroyTexture(this->texture->sdltexture);
}

void Faucet::drip() {
}

void Faucet::plumps() {
}

PubLiippari::PubLiippari() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "Pub Liippari Screensaver";
		this->version = "0.0002";
}

PubLiippari::~PubLiippari() {
}

bool PubLiippari::init() {
	// SET UP DISPLAY DEVICE:
		this->display->set_width(640);
		this->display->set_height(480);
		this->display->set_desiredfps(50);
		this->display->resizable_window = false;
		//this->display->vsync = true;
		//this->display->mousecursor_visible = false;
		//this->display->set_fullscreen(true);
	Program::init();

	// INIT OBJECTS:
		this->logo.sdltexture = this->display->load_texture(FILENAME_TEXTURE_LOGO);
		this->faucet = new Faucet();

	return this->works;
}

bool PubLiippari::mainloop() {
	while (!this->mainloop_done and this->works) {
		this->faucet->drip();
		// check if bucket full
		// draw faucet
		// draw beer
		// move and rotate logo
		// draw logo
		// move and rotate drunken fish
		// draw drunken fish
		get_events();
		this->display->refresh();
	}
	return this->works;
}
