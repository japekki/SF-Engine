#include "color.hpp"
#include <math.h>

Color::Color() {
}

ColorRGB Color::hsl_to_rgb() {
	/*
	h = fabs(h-trunc(h));
	s = fabs(s-trunc(s));
	l = fabs(l-trunc(l));

	float r, g, b; //, h, s, l; //this function works with floats between 0 and 1
	float temp1, temp2, tempr, tempg, tempb;
	//h = colorHSL.h / 256.0;
	//s = colorHSL.s / 256.0;
	//l = colorHSL.l / 256.0;

	// If saturation is 0, the color is a shade of gray
	if(s == 0) r = g = b = l;

	 // If saturation > 0, more complex calculations are needed
	else {
		//Set the temporary values
		if(l < 0.5) temp2 = l * (1 + s);
		else temp2 = (l + s) - (l * s);
		temp1 = 2 * l - temp2;
		tempr = h + 1.0 / 3.0;
		if(tempr > 1) tempr--;
		tempg = h;
		tempb = h - 1.0 / 3.0;
		if(tempb < 0) tempb++;

		// Red
		if(tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
		else if(tempr < 0.5) r = temp2;
		else if(tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
		else r = temp1;

		// Green
		if(tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
		else if(tempg < 0.5) g = temp2;
		else if(tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
		else g = temp1;

		// Blue
		if(tempb < 1.0 / 6.0) b = temp1 + (temp2 - temp1) * 6.0 * tempb;
		else if(tempb < 0.5) b = temp2;
		else if(tempb < 2.0 / 3.0) b = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
		else b = temp1;
	}
	*/
	ColorRGB color;
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}

uint32_t Color::hsl_to_int() {
	return 0;	// TODO
}

ColorHSL Color::rgb_to_hsl() {
	ColorHSL color;
	return color;
}

uint32_t Color::rgb_to_int() {
	//uint8_t r = 255*this->r;
	//uint8_t g = 255*this->g;
	//uint8_t b = 255*this->b;
	//this->rgbint = (r << 16) + (g << 8) + b;
	return 0;	// TODO
}

/*
ColorRGB Color::int_to_rgb() {
}

ColorHSL Color::int_to_hsl() {
}
*/

/*
Color::HSLtoRGB(ColorHSL colorHSL) {
	float r, g, b, h, s, l; //this function works with floats between 0 and 1
	float temp1, temp2, tempr, tempg, tempb;
	h = colorHSL.h;
	s = colorHSL.s;
	l = colorHSL.l;

	//h = abs(round(h) - h);
	//s = abs(round(s) - s);
	//l = abs(round(l) - l);

	// If saturation is 0, the color is a shade of gray
	if(s == 0)
		r = g = b = l;

	// If saturation > 0, more complex calculations are needed
	else {
		//Set the temporary values
		if(l < 0.5) temp2 = l * (1 + s);
		else temp2 = (l + s) - (l * s);
		temp1 = 2 * l - temp2;
		tempr = h + 1.0 / 3.0;
		if(tempr > 1) tempr--;
		tempg = h;
		tempb = h - 1.0 / 3.0;
		if(tempb < 0) tempb++;

		// Red
		if(tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
		else if(tempr < 0.5) r = temp2;
		else if(tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
		else r = temp1;

		// Green
		if(tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
		else if(tempg < 0.5) g = temp2;
		else if(tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
		else g = temp1;

		// Blue
		if(tempb < 1.0 / 6.0) b = temp1 + (temp2 - temp1) * 6.0 * tempb;
		else if(tempb < 0.5) b = temp2;
		else if(tempb < 2.0 / 3.0) b = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
		else b = temp1;
	}

	ColorRGB colorRGB;
	colorRGB.r = r;
	colorRGB.g = g;
	colorRGB.b = b;
	return colorRGB;
}

void generate_hsl_table() {
	//generate_hsl_table(SDL_Surface *sdlsurface);
}

// Index: 6 bit for hue, 1 bit for saturation, 1 bit for lightness
	uint32_t hsltable[16][16][16]; // 16*16*16 for hsl

void generate_hsl_table(SDL_Surface *sdlsurface) {
	ColorHSL tmp_hsl;
	ColorRGB tmp_rgb;
	for (int l = 0; l<16; l++) {
		for (int s = 0; s<16; s++) {
			for (int h=0; h<16; h++) {
				tmp_hsl.h = 1.0/16*h;
				tmp_hsl.s = 1.0/16*s;
				tmp_hsl.l = 1.0/16*l;
				tmp_rgb = HSLtoRGB(tmp_hsl);
				hsltable[h][s][l] = SDL_MapRGB(sdlsurface->format, 255*tmp_rgb.r, 255*tmp_rgb.g, 255*tmp_rgb.b);
			}
		}
	}
}
*/

SDL_Color color::UintToSDLColor(uint32_t color) {
	SDL_Color sdlcolor;
	sdlcolor.a = 255;
	sdlcolor.r = (color >> 16) & 0xFF;
	sdlcolor.g = (color >> 8) & 0xFF;
	sdlcolor.b = color & 0xFF;
	return sdlcolor;
}
