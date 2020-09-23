#include "base.hpp"
#include "gameplay.hpp"
#include "player.hpp"

Base::Base(Gameplay* gameplay) : Building(gameplay) {
	type = GAMEBLOB_TYPE_BASE;
}

Base::Base(Gameplay* gameplay, Team* owner_team) : Building(gameplay) {
	type = GAMEBLOB_TYPE_BASE;
	this->owner_team = owner_team;
}

Base::~Base() {
}

void Base::draw() {
	SDL_Rect rectangle;
	float width = 14;
	float height = 2;
	Point pa(location.x - width/2, location.y - height/2);
	Point pb(location.x + width/2, location.y + height/2);
	gameplay->display->grid_draw_line(pa, Point(pb.x, pa.y), 0x80808080);
	gameplay->display->grid_draw_line(Point(pa.x, pb.y), pb, 0x80808080);
	gameplay->display->grid_draw_line(pa, Point(pa.x, pb.y), 0x80808080);
	gameplay->display->grid_draw_line(Point(pb.x, pa.y), pb, 0x80808080);

	//SDL_SetRenderDrawColor(gameplay->display->renderer, 0x80, 0x80, 0x80, 0xff);
	//SDL_RenderFillRect(gameplay->display->renderer, &rectangle);
}

void Base::get_invaded(Team* new_team) {
    owner_team = new_team;
}
