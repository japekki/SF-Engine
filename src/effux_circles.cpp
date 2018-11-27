/*
	SF-Engine
*/

// FIXME:
// - Even and odd circles are different width
// - Twitching motion (probably because of using integers)

#include <math.h>
#include "effux_circles.hpp"
#include "misc.hpp"

EffuxCircles::EffuxCircles(Grapher *grapher) {
	this->width = grapher->width;
	this->height = grapher->height;
	this->pixels = new Uint32[width * height];
	this->grapher = grapher;
	this->sdltexture = SDL_CreateTexture(this->grapher->sdlrenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	circles.resize(width*height*4);
	for (int y=0; y < 2*height; y++) {
		for (int x=0; x < 2*width; x++) {
			this->circles[y*(2*width)+x] =
				(int)sqrt(
					pow(double(y - height) ,2) +
					pow(double(x - width) ,2)
				) % (width/16) > (width/32);
		}
	}
}

EffuxCircles::~EffuxCircles() {
	delete[] this->pixels;
}

void EffuxCircles::execute(Uint32 time, bool both) {
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
			if (this->circles[index_y1 + x+this->grapher->width/2+motion_x1] xor this->circles[index_y2 + x+this->grapher->width/2+motion_x2]) {
			// IF BIT XOR 1
				if (both) {
					// Sierpinski 1:
						//color = SDL_MapRGB(sdlsurface->format, 255-(y and Uint8(x+time/100)), 255-(x xor Uint8(y+time/100)), 255-(Uint8(x-time/100)) xor y);
						//color = (255-(y and Uint8(x+time/100))) << 24 + (255-(x xor Uint8(y+time/100))) << 16 + (255-(Uint8(x-time/100)) xor y) << 8;

					// ?:
						color =
						(Uint8(255-(y xor Uint8(x+time/100))) << 16) +
						(Uint8(255-(x xor Uint8(y+time/100))) << 8) +
						(Uint8(255-(Uint8(x-time/100)) xor y));

					// Rainbow:
						//ColorHSL colorhsl;
						//ColorRGB colorrgb;
						//colorhsl.h = 1.0/sdlsurface->w*x;
						//colorrgb = HSLtoRGB(colorhsl);
						//color = SDL_MapRGB(sdlsurface->format, round(255*colorrgb.r), round(255*colorrgb.g), round(255*colorrgb.b));

						//extern Uint32 hsltable[16][16][16];
						//color = hsltable [(y >> 5) & 15] [3] [7];

					this->pixels[y * this->grapher->width + x] = color;

				}
			}
			else {
			// IF BIT XOR 0

				// Sierpinski 1:
					//color = SDL_MapRGB(sdlsurface->format, y and Uint8(x+time/100), x xor Uint8(y+time/100), Uint8(x-time/100) xor y);
					//color = Uint8(y and Uint8(x+time/100)) << 16 + Uint8(x xor Uint8(y+time/100)) << 8 + Uint8(x-time/100 xor y);
					//color = colorBlack;

				// ?:
					color =
					(Uint8(y xor Uint8(x+time/100)) << 16) +
					(Uint8(x xor Uint8(y+time/100)) << 8) +
					(Uint8(Uint8(x-time/100)) xor y);

				// Rainbow:
					//ColorHSL colorhsl;
					//ColorRGB colorrgb;
					//colorhsl.h = 1.0/sdlsurface->w*x;
					//colorrgb = HSLtoRGB(colorhsl);
					//color = SDL_MapRGB(sdlsurface->format, 255-round(255*colorrgb.r), 255-round(255*colorrgb.g), 255-round(255*colorrgb.b));

					//extern Uint32 hsltable[16][16][16];
					//color = hsltable[(x >> 5) & 15] [7] [11];

				this->pixels[y * this->grapher->width + x] = color;
			}
		}
	}
	SDL_UpdateTexture(this->sdltexture, NULL, this->pixels, this->grapher->width * sizeof(Uint32));
}
