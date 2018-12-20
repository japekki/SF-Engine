#include "building.hpp"
#include "human.hpp"
#include "item.hpp"

void Building::explode() {
	// burst some items inside to outside to the field, make some bursted items deteriorate, delete some items
	for (unsigned int i = 0; i < this->items_inside.size(); i++)
		this->items_inside.at(i)->explode();

	// Kill humans inside:
		for (unsigned int i = 0; i < this->humans_inside.size(); i++)
			this->humans_inside.at(i)->die();
}
