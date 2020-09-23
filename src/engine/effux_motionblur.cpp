#include "effux_motionblur.hpp"
#include "grapher.hpp"

EffuxMotionblur::EffuxMotionblur(Grapher* grapher) {
	this->grapher = grapher;
	//blend previous frame over current frame
	previous_frame = SDL_CreateTexture(grapher->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, grapher->width, grapher->height);
}

EffuxMotionblur::~EffuxMotionblur() {
	SDL_DestroyTexture(previous_frame);
}

void EffuxMotionblur::execute(SDL_Texture* texture) {
	//blend previous frame over current frame
	//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	//previous_frame = SDL_CreateTexture(grapher->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, grapher->width, grapher->height);
}
