#include "grapher.hpp"
#include "item.hpp"
#include "human.hpp"
#include "gameplay.hpp"

Item::Item(Gameplay* gameplay) : Gameblob(gameplay) {
	type = GAMEBLOB_TYPE_ITEM;
	can_expire = true;
	expirecounter = 2000;
	collision_radius = 1;
}

//void Item::explode() {
//}

Item::~Item() {
}

void Item::draw() {
}

ItemText::ItemText(Gameplay* gameplay) : Item(gameplay) {
}

Item_extralife::Item_extralife(Gameplay* gameplay) : ItemText(gameplay) {
	//expirecounter = 2000;
	texture = grapher::create_textline_texture(gameplay->display->renderer, "1UP", gameplay->font_glasstty_tiny, SDLCOLOR_GREEN);
}

Item_extralife::~Item_extralife() {
}

//void Item_extralife::execute(Gameblob* collector) {
//}

Item_medkit::Item_medkit(Gameplay* gameplay) : ItemText(gameplay) {
		texture = grapher::create_textline_texture(gameplay->display->renderer, "+", gameplay->font_glasstty_small, SDLCOLOR_RED);
		// TODO: white background box
}

//void Item_medkit::execute(Gameblob* collector) {
	//human->heal(this->health);
	// TODO: leave healing points to medkit if all is not used, else the medkit vanishes
//}

Item_medkit::~Item_medkit() {
}

Item_money::Item_money(Gameplay* gameplay) : ItemText(gameplay) {
	texture = grapher::create_textline_texture(gameplay->display->renderer, "$", gameplay->font_glasstty_small, SDLCOLOR_GOLD);
}

//void Item_money::execute(Gameblob* collector) {
//}

Item_fuel::Item_fuel(Gameplay* gameplay) : ItemText(gameplay) {
	texture = grapher::create_textline_texture(gameplay->display->renderer, "F", gameplay->font_glasstty_tiny, SDLCOLOR_BROWN);
}

Item_fuel::~Item_fuel() {
}

//void Item_fuel::execute(Gameblob* collector) {
//}

void ItemText::draw() {
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);	// TODO: Optimize
	Point location = gameplay->display->grid.transform(this->location);
	location.x -= width/2;
	location.y -= height/2;
	grapher::draw_texture(gameplay->display->renderer, texture, location);
}

Item_money::~Item_money() {
}
