#include "rain.hpp"

Rain::Rain(Gameplay* gameplay) {
	this->gameplay = gameplay;
}

Rain::~Rain() {
}

void Rain::makerain() {
	// Create new drop(s):
		switch (type) {
			case RAIN_WATER:
				break;
			case RAIN_SNOW:
				break;
			case RAIN_LAND:
				break;
			case RAIN_LAVA:
				break;
			case RAIN_BOMB:
				break;
			case RAIN_ITEM:
				break;
		}
}

void Rain::execute() {
}
