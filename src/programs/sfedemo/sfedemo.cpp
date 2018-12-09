#include "sfedemo.hpp"

SFEdemo::SFEdemo() {
	// SET PROGRAM ATTRIBUTES:
		this->name = "SFE demo";
		this->version = "0.0001";
}

SFEdemo::~SFEdemo() {
}

bool SFEdemo::init() {
	// INITIALIZE TIMELINE:
		this->timeline = new Timeline();
		this->timeline->init();
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

bool SFEdemo::world_room_init() {
	Polygon3D polygon_chair;
	Polygon3D polygon_table;
	world_room.add_polygon3d(polygon_chair);
	world_room.add_polygon3d(polygon_table);
	return true;	// TODO
}

bool SFEdemo::mainloop() {
	while (!this->mainloop_done and this->works) {
		unsigned int time_elapsed = this->timeline->get_position();
		//world_room.camera.rotate(timeline.get_position(), 0, 0);
		get_events();
		if (this->keyboard->key_PLUS_down) {
			this->timeline->set_position(this->timeline->position + 1000);
			this->keyboard->key_PLUS_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_MINUS_down) {
			this->timeline->set_position(this->timeline->position - 1000);
			this->keyboard->key_MINUS_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_PAGEUP_down) {
			this->timeline->set_position(this->timeline->position + 10000);
			this->keyboard->key_PAGEUP_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_PAGEDOWN_down) {
			this->timeline->set_position(this->timeline->position - 10000);
			this->keyboard->key_PAGEDOWN_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_ASTERISK_down) {
			this->timeline->set_speed(this->timeline->speed * 1.1);
			this->keyboard->key_ASTERISK_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_SLASH_down) {
			this->timeline->set_speed(this->timeline->speed * 0.9);
			this->keyboard->key_SLASH_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_HOME_down) {
			this->keyboard->key_HOME_down = false;	// FIXME: keydown event keeps looping
		}
		if (this->keyboard->key_END_down) {
			this->keyboard->key_END_down = false;	// FIXME: keydown event keeps looping
		}
		this->display->refresh();
	}
	return this->works;
}
