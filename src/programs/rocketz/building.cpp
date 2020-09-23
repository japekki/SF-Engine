#include "building.hpp"
#include "human.hpp"
#include "item.hpp"

Building::Building(Gameplay* gameplay) : Gameblob(gameplay) {
	stationary = true;
}

void Building::explode() {
	// Burst some items inside to outside to the field, make some bursted items deteriorate, delete some items
	for (uint32_t i = 0; i < items_inside.size(); i++)
		items_inside[i]->explode();

	// Damage (eject?) humans inside:
		//for (uint32_t i = 0; i < humans_inside.size(); i++)
			//humans_inside[i)->damage();
}
