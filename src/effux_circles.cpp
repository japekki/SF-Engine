#include <math.h>
#include "effux_circles.hpp"
#include "misc.hpp"

EffuxCircles::EffuxCircles(Grapher *grapher) {
	// TODO: Give same circle thickness in all resolutions
	this->width = grapher->width;
	this->height = grapher->height;
	this->pixels = new Uint32[width * height];
	this->grapher = grapher;
	this->sdltexture = SDL_CreateTexture(this->grapher->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	circles.resize(width * height * 4);
	for (int y=0; y < 2*height; y++) {
		for (int x=0; x < 2*width; x++) {
			this->circles[y * (2*width) + x] =
				(int)sqrt(
					pow(double(y - height) ,2) +
					pow(double(x - width) ,2)
				) % (width/16) > (width/32);
		}
	}
}

EffuxCircles::~EffuxCircles() {
	if (this->pixels != nullptr) delete[] this->pixels;
}

void EffuxCircles::draw(Uint32 time, Uint8 style) {
	Uint32 color;
	int x, y;

	int motion_y1 = round(this->height/2*cos(-time/1000.0));
	int motion_x1 = round(this->width/2*sin(-time/1200.0));
	int motion_y2 = round(this->height/2*cos(time/1800.0));
	int motion_x2 = round(this->width/2*sin(time/1000.0));
	//int index_x1;
	int index_y1;
	//int index_x2;
	int index_y2;

	//if (circles[ int((y+res_y/2+motion_y1) *res_x*2 +
	//					  x+res_x/2+motion_x1) ]
	//		xor
	//		circles[ int((y+res_y/2+motion_y2) *res_x*2 +
	//					  x+res_x/2+motion_x2) ]
	//		)

	for (y=0; y<this->grapher->height; y++) {
		index_y1 = (y+this->height/2+motion_y1)*this->width*2;
		index_y2 = (y+this->height/2+motion_y2)*this->width*2;

		for (x=0; x<this->grapher->width; x++) {
			switch (style) {
				case 1:
					if (this->circles[index_y1 + x+this->grapher->width/2+motion_x1] xor this->circles[index_y2 + x+this->grapher->width/2+motion_x2])
						color = 0x003050;
					else
						color = 0x005030;
					break;
				case 2:
					if (this->circles[index_y1 + x+this->grapher->width/2+motion_x1] xor this->circles[index_y2 + x+this->grapher->width/2+motion_x2])
						color =
						(Uint8(255-(y xor Uint8(x+time/100))) << 16) +
						(Uint8(255-(x xor Uint8(y+time/100))) << 8) +
						(Uint8(255-(Uint8(x-time/100)) xor y));
					else
						color =
						(Uint8(y xor Uint8(x+time/100)) << 16) +
						(Uint8(x xor Uint8(y+time/100)) << 8) +
						(Uint8(Uint8(x-time/100)) xor y);
					break;
			}
			this->pixels[y * this->grapher->width + x] = color;
		}
	}
	SDL_UpdateTexture(this->sdltexture, NULL, this->pixels, this->grapher->width * sizeof(Uint32));
}
