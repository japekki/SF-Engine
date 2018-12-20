#include "effux_motionblur.hpp"
#include "grapher.hpp"

EffuxMotionblur::EffuxMotionblur(Grapher* grapher) {
	this->grapher = grapher;
	this->lastframe = SDL_CreateTexture(grapher->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, grapher->width, grapher->height);
}

EffuxMotionblur::~EffuxMotionblur() {
	SDL_DestroyTexture(this->lastframe);
}

void EffuxMotionblur::execute(SDL_Texture* sdltexture) {
	// Dimmen previous texture and mix new texture it
	//SDL_SetTextureBlendMode(sdltexture, SDL_BLENDMODE_BLEND);
}
