#include "options.hpp"
#include "math.hpp"
#include "graph.hpp"
#include "graph3d.hpp"
#include "display.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <math.h>

//#ifdef WITH_OPENGL
//    #include <GL/gl.h>
//#endif

extern Display monitor;

SDL_Surface *load_image(string filename) {
	SDL_Surface *loaded, *result;
	loaded = IMG_Load(filename.c_str());
	if ( loaded == NULL ) {
		fprintf(stderr, "SDL: Couldn't load %s: %s\n", filename.c_str(), SDL_GetError());
		result = NULL;
	}
	else {
		// Convert the loaded image into same bpp than current video mode:
		result = SDL_DisplayFormatAlpha(loaded);
		SDL_FreeSurface(loaded);
	}
	return result;
}

Color::Color() {
}

void Color::Set(ColorHSL colorhsl) {
}

void Color::Set(ColorRGB colorrgb) {
}

ColorHSL Color::Gethsl() {
}

ColorRGB Color::Getrgb() {
}

Uint32 Color::getsdlcolor(SDL_Surface *sdlsurface) {
}


Vertex2d::Vertex2d() {
}

Uint32 Vertex2d::colorint(SDL_Surface *sdlsurface) {
	Uint32 color = SDL_MapRGB(sdlsurface->format, 255*r, 255*g, 255*b);
	return color;
}


ColorRGB HSLtoRGB(float h, float s, float l) {
	h = fabs(h-trunc(h));
	s = fabs(s-trunc(s));
	l = fabs(l-trunc(l));

	float r, g, b; //, h, s, l; //this function works with floats between 0 and 1
	float temp1, temp2, tempr, tempg, tempb;
	//h = colorHSL.h / 256.0;
	//s = colorHSL.s / 256.0;
	//l = colorHSL.l / 256.0;

	//If saturation is 0, the color is a shade of gray
	if(s == 0) r = g = b = l;

	 //If saturation > 0, more complex calculations are needed
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

		//Red
		if(tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
		else if(tempr < 0.5) r = temp2;
		else if(tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
		else r = temp1;

		//Green
		if(tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
		else if(tempg < 0.5) g = temp2;
		else if(tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
		else g = temp1;

		//Blue
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

ColorRGB HSLtoRGB(ColorHSL colorHSL) {
	float r, g, b, h, s, l; //this function works with floats between 0 and 1
	float temp1, temp2, tempr, tempg, tempb;
	h = colorHSL.h;
	s = colorHSL.s;
	l = colorHSL.l;

	//h = abs(round(h) - h);
	//s = abs(round(s) - s);
	//l = abs(round(l) - l);

	//If saturation is 0, the color is a shade of gray
	if(s == 0) r = g = b = l;

	 //If saturation > 0, more complex calculations are needed
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

		//Red
		if(tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
		else if(tempr < 0.5) r = temp2;
		else if(tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
		else r = temp1;

		//Green
		if(tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
		else if(tempg < 0.5) g = temp2;
		else if(tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
		else g = temp1;

		//Blue
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

	// TODO: draw_pixel yms. opengl:llä

void draw_pixel_clip(int x, int y, Uint32 color, SDL_Surface *sdlsurface) {
	// NOTE: The surface must be locked before calling this!
	int clip_x1, clip_x2, clip_y1, clip_y2;
	if (monitor.centered){
		clip_x1 = - sdlsurface->w /2;
		clip_x2 = sdlsurface->w /2 -1;
		clip_y1 = - sdlsurface->h /2;
		clip_y2 = sdlsurface->h /2 -1;
	}
	else {
		clip_x1 = 0;
		clip_x2 = sdlsurface->w-1;
		clip_y1 = 0;
		clip_y2 = sdlsurface->h-1;
	}

	if (x>=clip_x1 and x<=clip_x2 and y>=clip_y1 and y<=clip_y2) {
		if (monitor.centered) {
			x += sdlsurface->w/2;
			y += sdlsurface->h/2;
		}
		int bpp = sdlsurface->format->BytesPerPixel;

		Uint8 *p = (Uint8 *)sdlsurface->pixels + y * sdlsurface->pitch + x * bpp;

		switch(bpp) {
		case 1:
			*p = color;
			break;

		case 2:
			*(Uint16 *)p = color;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (color >> 16) & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = color & 0xff;
			} else {
				p[0] = color & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = (color >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = color;
			break;
		}
	}   // if (clip...)
}

void draw_pixel_noclip(int x, int y, Uint32 color, SDL_Surface *sdlsurface) {
	// * NOTE: The surface must be locked before calling this!
		int bpp = sdlsurface->format->BytesPerPixel;

		Uint8 *p = (Uint8 *)sdlsurface->pixels + y * sdlsurface->pitch + x * bpp;

		switch(bpp) {
		case 1:
			*p = color;
			break;

		case 2:
			*(Uint16 *)p = color;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (color >> 16) & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = color & 0xff;
			} else {
				p[0] = color & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = (color >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = color;
			break;
		}
}

Uint32 get_pixel_clip(int x, int y, SDL_Surface *sdlsurface) {
	// NOTE: The surface must be locked before calling this!
	Uint32 color;
	int clip_x1, clip_x2, clip_y1, clip_y2;
	if (monitor.centered){
		clip_x1 = - sdlsurface->w /2;
		clip_x2 = sdlsurface->w /2;
		clip_y1 = - sdlsurface->h /2;
		clip_y2 = sdlsurface->h /2;
	}
	else {
		clip_x1 = 0;
		clip_x2 = sdlsurface->w-1;
		clip_y1 = 0;
		clip_y2 = sdlsurface->h-1;
	}

	if (x>=clip_x1 and x<=clip_x2 and y>=clip_y1 and y<=clip_y2) {

		if (monitor.centered) {
			x += sdlsurface->w/2;
			y += sdlsurface->h/2;
		}

		int bpp = sdlsurface->format->BytesPerPixel;

		Uint8 *p = (Uint8 *)sdlsurface->pixels + y * sdlsurface->pitch + x * bpp;

		switch(bpp) {
		case 1:
			color = *p;
			break;

		case 2:
			color = *(Uint16 *)p;
			break;

		case 3:
			// TODO: ei toimi
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				color = p[0] << 16;
				color += p[1] << 8;
				color += p[2];
			} else {
				color = p[0];
				color += p[1] << 8;
				color += p[2] << 16;
			}
			break;

		case 4:
			color = *(Uint32 *)p;
			break;
		}
	}
	return color;
}

Uint32 get_pixel_noclip(int x, int y, SDL_Surface *sdlsurface) {
	// * NOTE: The surface must be locked before calling this!
	Uint32 color;
	int bpp = sdlsurface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)sdlsurface->pixels + y * sdlsurface->pitch + x * bpp;

	switch(bpp) {
	case 1:
		color = *p;
		break;

	case 2:
		color = *(Uint16 *)p;
		break;

	case 3:
		// TODO: ei toimi
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			color = p[0] << 16;
			color += p[1] << 8;
			color += p[2];
		} else {
			color = p[0];
			color += p[1] << 8;
			color += p[2] << 16;
		}
		break;

	case 4:
		color = *(Uint32 *)p;
		break;
	}
	return color;
}


void draw_hline(int x1, int x2, int y, Uint32 color, SDL_Surface *sdlsurface) {
// Draw a horizontal line
	if (x1 > x2)
	{
		int temp = x2;
		x2 = x1;
		x1 = temp;
	}
	// TODO: Parempi clippaus
	//    if (x1 > Monitor.koordinaatisto.get_x_min() and x1 < Monitor.koordinaatisto.get_x_max()
	//    and x2 > Monitor.koordinaatisto.get_x_min() and x2 < Monitor.koordinaatisto.get_x_max()
	//    and y > Monitor.koordinaatisto.get_y_min() and y < Monitor.koordinaatisto.get_y_max())
	//    {
		int i;
		for (i=x1; i<=x2; i++)
		{
			draw_pixel_clip(i, y, color, sdlsurface);
		}
	//    }
}



void draw_vline(int x, int y1, int y2, Uint32 color, SDL_Surface *sdlsurface) {
// Draw a vertical line
// TODO: Leikkaa koordinaatit näytön reunojen mukaan

	if (y1 > y2)
	{
		int temp = y2;
		y2 = y1;
		y1 = temp;
	}
	int i;
	for (i=y1; i<=y2; i++)
	{
		draw_pixel_clip(x, i, color, sdlsurface);
	}
}


void draw_line(int x1, int y1, int x2, int y2, Uint8 width, Uint32 color, SDL_Surface *sdlsurface) {
	int clip_xmin, clip_xmax, clip_ymin, clip_ymax;
	if (monitor.centered){
		clip_xmin = -monitor.get_width()/2;
		clip_xmax = monitor.get_width()/2;
		clip_ymin = -monitor.get_height()/2;
		clip_ymax = monitor.get_height()/2;
	}
	else {
		clip_xmin = 0;
		clip_xmax = monitor.get_width()-1;
		clip_ymin = 0;
		clip_ymax = monitor.get_height()-1;
	}
	if ((x1>=clip_xmin and x1<=clip_xmax and y1>=clip_ymin and y1<=clip_ymax) and
	   (x2>=clip_xmin and x2<=clip_xmax and y2>=clip_ymin and y2<=clip_ymax)) {
//            if (koordinaatisto) {
//                x1 += res_x/2;
//                x2 += res_x/2;
//                y1 += res_y/2;
//                y2 += res_y/2;
//            }
		}
	int tmpx, tmpy;

	// Sorttaa y2 > y1 :
	if (y1 > y2){
		tmpx = x1;
		tmpy = y1;
		x1 = x2;
		y1 = y2;
		x2 = tmpx;
		y2 = tmpy;
	}

	float x = x1;
	int y;
	if ((y2-y1) != 0) {
		float k = float(x2-x1) / (y2-y1);
		for (y=int(y1); y<int(y2); y++) {
			draw_hline(x-width, x+k+width, y, color, sdlsurface);
			x = x + k;
		}
	}
	else {
		draw_hline(x1-width, x2+width, y1, color, sdlsurface);
	}
}

//void draw_triangle2d(triangle3d tr, Uint8 shadestyle, bool koordinaatisto, SDL_Surface *sdlsurface)
void draw2d_triangle(triangle2d tr, Uint8 shadestyle, bool koordinaatisto, SDL_Surface *sdlsurface) {
	// Koordinaatisto = true
	// KESKEN
	switch(shadestyle){
		case POLYGON_SHADESTYLE_POINT: {
			draw_pixel_clip(tr.a.x, tr.a.y, tr.a.colorint(sdlsurface), sdlsurface);
			draw_pixel_clip(tr.b.x, tr.b.y, tr.b.colorint(sdlsurface), sdlsurface);
			draw_pixel_clip(tr.c.x, tr.c.y, tr.c.colorint(sdlsurface), sdlsurface);
			break;
		}
		case POLYGON_SHADESTYLE_WIREFRAME: {
			draw_line(tr.a.x, tr.a.y, tr.b.x, tr.b.y, 3, tr.a.colorint(sdlsurface), sdlsurface);
			draw_line(tr.b.x, tr.b.y, tr.c.x, tr.c.y, 3, tr.b.colorint(sdlsurface), sdlsurface);
			draw_line(tr.c.x, tr.c.y, tr.a.x, tr.a.y, 3, tr.c.colorint(sdlsurface), sdlsurface);
			break;
		}
		case POLYGON_SHADESTYLE_SINGLE: {
			// TODO:
			//Sort a.y > b.y > c.y :
			Vertex2d tmp;
			if (tr.c.y < tr.b.y){
				tmp = tr.b;
				tr.b = tr.c;
				tr.c = tmp;
			}
			if (tr.b.y < tr.a.y){
				tmp = tr.a;
				tr.a = tr.b;
				tr.b = tmp;
			}
			// ??

			if (tr.c.y < tr.b.y){
				tmp = tr.b;
				tr.b = tr.c;
				tr.c = tmp;
			}

			// Kulmakertoimet sivuille:
			float k_ab, k_ac, k_bc;

			if (tr.b.y != tr.a.y) {k_ab = (tr.b.x-tr.a.x) / (tr.b.y-tr.a.y);}
			if (tr.c.y != tr.a.y) {k_ac = (tr.c.x-tr.a.x) / (tr.c.y-tr.a.y);}
			if (tr.c.y != tr.b.y) {k_bc = (tr.c.x-tr.b.x) / (tr.c.y-tr.b.y);}

			float left = tr.a.x;
			float right = tr.a.x;
			// Piirra ylaosa ABD:
			for (int i=round(tr.a.y); i<round(tr.b.y); i++) {
				if (shadestyle==POLYGON_SHADESTYLE_SINGLE){
					draw_hline(left, right, i, tr.a.colorint(sdlsurface), sdlsurface);
					//draw_hline_gouraud(left, right, i, tr.a.colorint(sdlsurface), koordinaatisto, sdlsurface);
				}
				else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
				}
					left = left + k_ab;
					right = right + k_ac;
			}
			// Piirra alaosa BCD:
			for (int i=round(tr.b.y); i<round(tr.c.y); i++) {
				if (shadestyle==POLYGON_SHADESTYLE_SINGLE){
					draw_hline(left, right, i, tr.a.colorint(sdlsurface), sdlsurface);
				}
				else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
				}
				left = left + k_bc;
				right = right + k_ac;
			}
			break;
		}   // case SHADESTYLE_SOLID:
	}   // switch(shadestyle){
}

/*
fade_alpha(Uint8 alpha, SDL_Surface *sdlsurface) {
}
TEST:
	//Monitor.clearcolor = colorBlue;
	//clearscreen();
	//SDL_BlitSurface(pic_logo, NULL, Monitor.sdlsurface, NULL);
	//SDL_SetAlpha(pic_huvimaja, SDL_SRCALPHA, 128); //4*(63-FMUSIC_GetRow(musa)));
	//SDL_BlitSurface(pic_huvimaja, NULL, Monitor.sdlsurface, NULL);
		SDL_Surface *screen_copy = SDL_CreateRGBSurface (Monitor.sdlsurface->flags|SDL_SRCALPHA,
		Monitor.sdlsurface->w,
		Monitor.sdlsurface->h,
		Monitor.sdlsurface->format->BitsPerPixel,
		Monitor.sdlsurface->format->Rmask,
		Monitor.sdlsurface->format->Gmask,
		Monitor.sdlsurface->format->Bmask,
		Monitor.sdlsurface->format->Amask);
		SDL_BlitSurface(Monitor.sdlsurface, NULL, screen_copy, NULL) ;

		SDL_Surface *black_surface = SDL_CreateRGBSurface (Monitor.sdlsurface->flags|SDL_SRCALPHA,
		Monitor.sdlsurface->w,
		Monitor.sdlsurface->h,
		Monitor.sdlsurface->format->BitsPerPixel,
		Monitor.sdlsurface->format->Rmask,
		Monitor.sdlsurface->format->Gmask,
		Monitor.sdlsurface->format->Bmask,
		Monitor.sdlsurface->format->Amask);

		SDL_FillRect(black_surface, NULL, 0);

		SDL_SetAlpha(black_surface, SDL_SRCALPHA, (Uint8)(200));
		//SDL_BlitSurface(screen_copy, NULL, Monitor.sdlsurface, NULL);
		SDL_BlitSurface(black_surface, NULL, Monitor.sdlsurface, NULL);
		SDL_FreeSurface(black_surface);
		SDL_FreeSurface(screen_copy);
*/


void draw_square(float x1, float y1, float x2, float y2, Uint32 color, SDL_Surface *sdlsurface)
{
	float x1_ = round(x1);
	float y1_ = round(y1);
	float x2_ = round(x2);
	float y2_ = round(y2);

	// Sort:
	if (x1_ > x2_) {
		float tmp = x2_;
		x2_ = x1_;
		x1_ = tmp;
	}
	if (y1_ > y2_) {
		float tmp = y2_;
		y2_ = y1_;
		y1_ = tmp;
	}

	for (int y=round(y1_); y<round(y2_); y++) {
		draw_hline(x1, x2, y, color, sdlsurface);
	}
}


void draw_circle(float x, float y, float r, Uint8 width, Uint8 slices, Uint32 color, SDL_Surface *sdlsurface) {
	for (int i=0; i<slices; i++) {
		draw_line(x+r*sin(2*PI/slices*i), y+r*cos(2*PI/slices*i), x+r*sin(2*PI/slices*(i+1)), y+r*cos(2*PI/slices*(i+1)), width, color, sdlsurface);
	}
}


void draw_circle(point2d c, float r, Uint8 slices, Uint8 width, Uint32 color, SDL_Surface *sdlsurface) {
	for (int i=0; i<slices; i++) {
		draw_line(c.x+r*sin(2*PI/slices*i), c.y+r*cos(2*PI/slices*i), c.x+r*sin(2*PI/slices*(i+1)), c.y+r*cos(2*PI/slices*(i+1)), width, color, sdlsurface);
	}
}


void draw_circle(Point P, float r, Uint8 slices, Uint8 width, Uint32 color, SDL_Surface *sdlsurface) {
	for (int i=0; i<slices; i++) {
		draw_line(P.x+r*sin(2*PI/slices*i), P.y+r*cos(2*PI/slices*i), P.x+r*sin(2*PI/slices*(i+1)), P.y+r*cos(2*PI/slices*(i+1)), width, color, sdlsurface);
	}
}


void Sprite::draw(int x, int y, SDL_Surface *sdlsurface_) {
	SDL_Rect offset; //Give the offsets to the rectangle\
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface( sdlsurface, NULL, sdlsurface_, &offset );
}

void Sprite::draw(int x, int y, Sprite another) {
}


SDL_Surface* scale_surface(int new_x, int new_y, SDL_Surface *sdlsurface) {
	// Koordinaatisto = false ?
	// TODO: testaa 8, 16, 24 ja 32 bpp
	SDL_Surface *result;
	int bpp = sdlsurface->format->BitsPerPixel;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 rmask = 0xff000000;
		Uint32 gmask = 0x00ff0000;
		Uint32 bmask = 0x0000ff00;
		Uint32 amask = 0x000000ff;
	#else
		Uint32 rmask = 0x000000ff;
		Uint32 gmask = 0x0000ff00;
		Uint32 bmask = 0x00ff0000;
		Uint32 amask = 0xff000000;
	#endif
	//scaled = SDL_CreateRGBSurface(SDL_SWSURFACE, new_x, new_y, sdlsurface->format->BitsPerPixel, rmask, gmask, bmask, amask);
	result = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, new_x, new_y, bpp, 0, 0, 0, 0);
	if(result == NULL) {
		fprintf(stderr, "SDL: CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Scale original surface into this one:
	float k_x = float(sdlsurface->w)/new_x;
	float k_y = float(sdlsurface->h)/new_y;
	for (int y=0; y<new_y; y++) {
		for (int x=0; x<new_x; x++) {
			Uint32 color = get_pixel_noclip(round(k_x*x), round(k_y*y), sdlsurface);
			draw_pixel_noclip(x, y, color, result);
		}
	}
	result = SDL_DisplayFormatAlpha(sdlsurface);
	return result;
}


void Triangle2d::draw() {
}


/*

Class Polygon
void translate(x, y, z)
void scale(float factor_x, float factor_y, float factor_z)
void rotate(float angle_x, float angle_y, float angle_z) {
}

Class Circle
void draw (float x, float y, float r, Uint32 color) {
}


Class Square
void draw () {
}

Class Line
void draw (float x1, float y1, float z1, float x2, float y2, float z2, Uint32 color) {
}


*/

bool Sprite::collide(Sprite another) {
	return false;
}
