#include <SDL.h>
#include "timeline.hpp"

Timeline::Timeline() {
}

Timeline::~Timeline() {
}

void Timeline::init() {
	this->init_timestamp = SDL_GetTicks();
}

void Timeline::set_speed(float speed) {
	this->speed = speed;
}

/*
float Timeline::get_speed() {
	return this->speed;
}
*/

int Timeline::get_position() {
	//return position;
	return speed * (SDL_GetTicks() - this->init_timestamp);	// FIXME: jump from current position
}

void Timeline::set_position(int position) {
	this->position = position;
}

/*
void Timeline::sync(unsigned char sync_type) {
	switch (sync_type) {
		case SYNC_CLOCK:
			// Calibrate our starting timestamp to be zero:
			position = SDL_GetTicks() - init_timestamp;
			break;
	}
	// TODO: Handle cumulative actions between our leaps
}

void Timeline::set_position(int new_position) {
	position = new_position;
}

//void Timeline::add_action(Action action) {
//	actions.push_back(action);
//}

//void add_action(int time, void *function) {
//    Action tmpact;
//    tmpact.triggertime = time;
//    tmpact.function = function;
//}

void Timeline::clear() {
	actions.clear();
}

void Timeline::start() {
	running = true;
}

void Timeline::stop() {
	running = false;
}

int Timeline::time_until_next_action() {
//    current_time =
//    return next_event_time - current_time;
	for (int i=0; i<actions.size(); i++) {
		//if (actions.at(i). )
	}
}

*/
