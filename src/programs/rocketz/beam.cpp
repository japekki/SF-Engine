#include "beam.hpp"
#include "gameplay.hpp"

Beam::Beam(Gameplay* gameplay) : Gameblob(gameplay) {
	type = GAMEBLOB_TYPE_BEAM;
}

Beam::~Beam() {
}

void Beam::draw() {
	// TODO: Reflections

	Point point_start;
	point_start.x = location.x;
	point_start.y = location.y;
	point_start = gameplay->display->grid.transform(point_start);

	// Calculate end point:
		Point point_end;
		point_end.x = point_start.x + 10;	// TODO
		point_end.y = point_start.y + 10;	// TODO
		point_end = gameplay->display->grid.transform(point_end);

	// Draw line from vehicle to end point:
		SDL_SetRenderDrawColor(gameplay->display->renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(gameplay->display->renderer, point_start.x, point_start.y, point_end.x, point_end.y);

}
