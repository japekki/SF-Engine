#include "tetrex.hpp"
#include "display.hpp"

bool Piece::rotate_cw() {
	return false;	// TODO: return false if no room in bucket to rotate
}

bool Piece::rotate_ccw() {
	return false;	// TODO: return false if no room in bucket to rotate
}

void create_all_pieces(unsigned char block_count) {
}

void Bucket::generate_shapes() {
	// TODO: no duplicates
}

void Bucket::check_fills() {
	// Check for complete line of blocks
}

Bucket::Bucket() {
	this->generate_shapes();
}

Bucket::~Bucket() {
}

void Bucket::execute() {
	this->check_fills();
}

Gameplay::Gameplay(Display* display, Audio* audio) {
	this->display = display;
	this->audio = audio;
}

Gameplay::~Gameplay() {
}

Tetrex::Tetrex(int argc, char** argv) : Program(argc, argv) {
	// SET PROGRAM ATTRIBUTES:
		name = "Tetrex";
		version = "0.0002";
}

Tetrex::~Tetrex() {
}

bool Tetrex::init() {
	// SET UP DISPLAY DEVICE:
		display->set_width(640);
		display->set_height(480);
		display->set_desiredfps(50);
		//display->resizable_window = false;
		//display->vsync = true;
		//display->mousecursor_visible = false;
		//display->set_fullscreen(true);
	Program::init();
	return this->works;
}

bool Tetrex::init_titlescreen() {
	return true;	// TODO
}

bool Tetrex::deinit_titlescreen() {
	return true;	// TODO
}

bool Tetrex::init_gameplay() {
	gameplay = new Gameplay(display, audio);
	return true;	// TODO
}

bool Tetrex::deinit_gameplay() {
	return true;	// TODO
}

bool Tetrex::mainloop() {
	while (!mainloop_done and this->works) {
		get_events();
		// If space, drop block immediately
		// bucket.check_fills();
		// If down, drop block faster
		// If left, move block left
		// If right, move block right
		// If V, rotate block right
		// If F, rotate block left
		// If Esc, quit/pause

		//gameplay->level->bucket->execute();
		//this->display->clearscreen();
		display->refresh();
	}
	return this->works;
}
