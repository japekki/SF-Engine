#include "explosion.hpp"
#include "gameplay.hpp"
#include "gamespace.hpp"
#include "weapon.hpp"

Explosion::Explosion(Gameplay* gameplay) {
	this->gameplay = gameplay;
}

void Explosion::create_sparks(Point location, Vector heading, uint16_t bullet_amount, float total_mass) {
	for (int i=0; i<bullet_amount; i++) {
		Bullet* spark = new Bullet(gameplay);
		spark->mass = total_mass / bullet_amount;
		spark->location = location;
		Point direction(0, rand() % 100 * 0.03 + 0.5);
		direction.rotate(PIX2/bullet_amount*i);
		spark->heading.i = direction.x + heading.i;
		spark->heading.j = direction.y + heading.j;
		switch (rand() % 4) {
			case 0:
				spark->color = SDLCOLOR_ORANGE;
				break;
			case 1:
				spark->color = SDLCOLOR_YELLOW;
				break;
			case 2:
				spark->color = SDLCOLOR_WHITE;
				break;
			case 3:
				spark->color = SDLCOLOR_RED;
				break;
		}
		gameplay->gamespace->add_blob(spark);
	}
}

/*
void Explosion::execute() {
	for (uint32_t i = 0; i < sparks.size(); i++) {
		if (sparks[i)->timeleft <= 0) {
			// Delete expired spark:
			delete sparks[i);
			sparks.erase(sparks.begin() + i);
		} else {
			sparks[i)->age();
			SDL_SetRenderDrawColor(display->renderer, 0xff, rand(), 0, 0xff);
			Point point;
			point.x = sparks[i)->location.x;
			point.y = sparks[i)->location.y;
			sparks[i)->heading.j += 0.01;
			point = display->grid.transform(point);
			SDL_RenderDrawPoint(display->renderer, point.x-1, point.y);
			SDL_RenderDrawPoint(display->renderer, point.x+1, point.y);
			SDL_RenderDrawPoint(display->renderer, point.x, point.y-1);
			SDL_RenderDrawPoint(display->renderer, point.x, point.y+1);
			SDL_RenderDrawPoint(display->renderer, point.x, point.y);
			//SDL_SetRenderDrawColor(display->renderer, 0x00, 0x00, 0x00, 0x00);
			sparks[i)->move();
		}
	}
	if (rand() % 20 == 0) this->create_sparks();
}
*/

