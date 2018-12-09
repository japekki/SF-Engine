#include "gameplay.hpp"

void Gameplay::execute() {
	// MOVE STUFF:
		// Move vehicles:
			//if (this->keyboard->key_UP_down) this->rocket->y -= 1;
			//if (this->keyboard->key_DOWN_down) this->rocket->y += 1;
			//if (this->keyboard->key_LEFT_down) this->rocket->x -= 1;
			//if (this->keyboard->key_RIGHT_down) this->rocket->x += 1;
			//this->rocket->rotate(10);
		// Move bullets:
			// TODO
		// Move rogues:
			// TODO
	// DRAW STUFF:
		// Draw level:
			// Draw parallax background:
				//for (unsigned int layernum = 0; layernum < this->gameplay->level->backgrounds.size(); layernum++) {
					// Calculate offset where to draw texture from
					// draw texture this->gameplay->level->backgrounds[layernum];
				//}
			// Draw player rockets:
				//this->display->draw_polygon(this->rocket);
				//this->display->draw_triangle(this->rocket);

			// Draw bullets:
				//for (unsigned int playernum = 0; playernum < this->gameplay->players.size(); playernum++) {
				//		for (unsigned int bulletnum = 0; bulletnum < this->gameplay->bulletnum.size(); bulletnum++) {
				//			// TODO: Draw player bullet
				//		}
				//}
				//for (unsigned int layernum = 0; layernum < this->gameplay->level->backgrounds.size(); layernum++) {
				//}
			// Draw rogues:
				// TODO
}

void Selfplay::init() {
	// Randomize level
	// Randomize game objective
	// Randomize 1-8 players (1-8 for fool around or rally mode, 2-8 for the rest)
}
