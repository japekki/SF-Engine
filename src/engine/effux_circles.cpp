#include <math.h>
#include "effux_circles.hpp"
#include "misc.hpp"
#include "grapher.hpp"

EffuxCircles::EffuxCircles() {
	viewport = new SDL_Rect;
}

void EffuxCircles::setup(SDL_Renderer* renderer, uint16_t width, uint16_t height) {
	// TODO: Give same circle thickness in all resolutions
		//this->grapher = grapher;
		//this->renderer = renderer;
	this->width = width;
	this->height = height;
	viewport->x = 0;
	viewport->y = 0;
	viewport->w = width;
	viewport->h = height;
	pixels = new uint32_t[viewport->w * viewport->h];
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	circles.resize(width * height * 4);
	// Generate pixel map
	for (int y=0; y < 2*height; y++) {
		for (int x=0; x < 2*width; x++) {
			circles[y * (2*width) + x] =
				(int)sqrt(
					pow(double(y - height) ,2) +
					pow(double(x - width) ,2)
				) % (width/16) > (width/32);
		}
	}
}

EffuxCircles::~EffuxCircles() {
	delete viewport;
	if (pixels != nullptr) delete pixels;
	if (texture != nullptr) SDL_DestroyTexture(texture);
}

void EffuxCircles::execute_OLD(uint32_t time) {
	uint32_t color = 0;
	int motion_y1 = round(this->height/2 * cos(-time/1000.0));
	int motion_x1 = round(this->width/2 * sin(-time/1200.0));
	int motion_y2 = round(this->height/2 * cos(time/1800.0));
	int motion_x2 = round(this->width/2 * sin(time/1000.0));

	//if (circles[ int((y+res_y/2+motion_y1) *res_x*2 +
	//					x+res_x/2+motion_x1) ]
	//		xor
	//		circles[ int((y+res_y/2+motion_y2) *res_x*2 +
	//					x+res_x/2+motion_x2) ]
	//		)

	for (int y=0; y<this->height; y++) {
		int index_y1 = (y + this->height/2 + motion_y1) * this->width*2;
		int index_y2 = (y + this->height/2 + motion_y2) * this->width*2;

		for (int x=0; x<this->width; x++) {

			switch (style) {
				case 1:
					if (this->circles[index_y1 + x + this->width/2 + motion_x1] xor this->circles[index_y2 + x + this->width/2 + motion_x2])
						color = 0x003050;
					else
						color = 0x005030;
					break;

				case 2:
					if (this->circles[index_y1 + x + this->width/2 + motion_x1] xor this->circles[index_y2 + x + this->width/2 + motion_x2])
						color =
						(uint8_t(255-(y xor uint8_t(x+time/100))) << 16) +
						(uint8_t(255-(x xor uint8_t(y+time/100))) << 8) +
						(uint8_t(255-(uint8_t(x-time/100)) xor y));
					else
						color =
						(uint8_t(y xor uint8_t(x+time/100)) << 16) +
						(uint8_t(x xor uint8_t(y+time/100)) << 8) +
						(uint8_t(uint8_t(x-time/100)) xor y);
					break;
			}
				pixels[y * this->width + x] = color;
				//this->pixels[y * this->width + x] = (0xff << 24) + color;

		}
	}
	//SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);	// Enable alpha
	SDL_UpdateTexture(texture, NULL, pixels, this->width * sizeof(uint32_t));
}

void EffuxCircles::execute(uint32_t time) {
	uint32_t color = 0;
	int motion_y1 = round(this->height/2 * cos(-time/1000.0));
	int motion_x1 = round(this->width/2 * sin(-time/1200.0));
	int motion_y2 = round(this->height/2 * cos(time/1800.0));
	int motion_x2 = round(this->width/2 * sin(time/1000.0));

	//if (circles[ int((y+res_y/2+motion_y1) *res_x*2 +
	//					x+res_x/2+motion_x1) ]
	//		xor
	//		circles[ int((y+res_y/2+motion_y2) *res_x*2 +
	//					x+res_x/2+motion_x2) ]
	//		)

	for (int y=viewport->y; y<viewport->y+viewport->h; y++) {
		int index_y1 = (y + viewport->h/2 + motion_y1) * viewport->w*2;
		int index_y2 = (y + viewport->h/2 + motion_y2) * viewport->w*2;

		for (int x=viewport->x; x<viewport->x+viewport->w; x++) {

			switch (style) {
				case 1:
					if (circles[index_y1 + x + viewport->w/2 + motion_x1] xor circles[index_y2 + x + viewport->w/2 + motion_x2])
						color = 0x003050;
					else
						color = 0x005030;
					break;

				case 2:
					if (circles[index_y1 + x + viewport->w/2 + motion_x1] xor circles[index_y2 + x + viewport->w/2 + motion_x2])
						color =
						(uint8_t(255-(y xor uint8_t(x+time/100))) << 16) +
						(uint8_t(255-(x xor uint8_t(y+time/100))) << 8) +
						(uint8_t(255-(uint8_t(x-time/100)) xor y));
					else
						color =
						(uint8_t(y xor uint8_t(x+time/100)) << 16) +
						(uint8_t(x xor uint8_t(y+time/100)) << 8) +
						(uint8_t(uint8_t(x-time/100)) xor y);
					break;
			}
			pixels[y * this->width + x] = color;

		}
	}
	//SDL_UpdateTexture(texture, NULL, pixels, this->width * sizeof(uint32_t));
	SDL_UpdateTexture(texture, viewport, pixels, viewport->w * sizeof(uint32_t));
}

SDL_Texture* execute_rect(uint32_t time, SDL_Rect area) {
	return nullptr;	// TODO
}
