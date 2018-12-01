#include "timeline.hpp"

Timeline::Timeline() {
}

Timeline::~Timeline() {
}

/*

void Timeline::init() {
	init_timestamp = SDL_GetTicks();
}

void Timeline::sync(unsigned char sync_type) {
	switch (sync_type) {
		case SYNC_CLOCK:
			// Calibrate our starting timestamp to be zero:
			position = SDL_GetTicks() - init_timestamp;
			break;
	}
	// TODO: Handle cumulative actions between our leaps
}

int Timeline::get_position() {
	return position;
}

void Timeline::set_position(int new_position) {
	position = new_position;
}

void Timeline::jumpto(int new_position) {
	position = new_position;
}

void Timeline::set_speed(float new_speed) {
	speed = new_speed;
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
	playing = true;
}

void Timeline::stop() {
	playing = false;
}

int Timeline::time_until_next_action() {
//    current_time =
//    return next_event_time - current_time;
	for (int i=0; i<actions.size(); i++) {
		//if (actions.at(i). )
	}
}

*/
