#include "building.hpp"

void Building::explode() {
	// burst some items inside to outside to the field, make some bursted items deteriorate, delete some items
	// Kill humans inside:
		for (int i = 0; i < this->humans_inside.size(); i++)
			this->humans_inside.at(i)->die();
}
