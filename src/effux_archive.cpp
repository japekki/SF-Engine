/*
	SF-Engine

	This file has a collection of miscellaneous routines for demo effects.
*/

#include <math.h>
#include <vector>
//#ifdef WITH_OPENGL
	//#include <GL/gl.h>
//#endif
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "graph.hpp"
#include "entity.hpp"
#include "effux_archive.hpp"
#include "display.hpp"

#include "globals.hpp"
//#include "display.hpp"
//#include "timeline.hpp"
#include "product.hpp"

extern Display monitor;

void effux_rainbow(Uint32 time, SDL_Surface *sdlsurface) {
// Koordinaatisto = false
	extern Uint32 hsltable[16][16][16];
	ColorHSL colorhsl;
		colorhsl.l = 0.5;
		//colorhsl.s = sin(time/1000.0);
		//colorhsl.h = 1.0/res_x*x;
		colorhsl.s = 1.0;
	ColorRGB colorrgb;
	Uint32 color;
	int x, y;
	for (y=0; y<sdlsurface->h; y++) {
		for (x=0; x<sdlsurface->w; x++) {
			color = hsltable [int(16.0/sdlsurface->w*x)] [int(16.0/sdlsurface->h*y)] [time & 15] ;
			draw_pixel_noclip(x, y, color, sdlsurface);
		}
	}
}

	bool image_to_cubearray(SDL_Surface *sdlsurface, float scale, float ratio) {
	// Create an array of 3d cubes colored by the pixels of an image/sdl_surface
	// scale is the length of cubes width, height or depth
	// if ratio is 0, cubes are 0 in size
	// if ratio is 1, no space is left between the cubes
		float r,g,b;
		for (int x=0; x<sdlsurface->w; x++) {
			for (int y=0; y<sdlsurface->h; y++) {
				Uint32 color = get_pixel_clip(x, y, sdlsurface);
				r = 1.0/256*(color >> 16);
				g = 1.0/256*(color >> 8);
				b = 1.0/256*(color >> 0);
				generate_cube(scale*x, scale*y, 0, ratio, r, g, b);
			}
		}
	}

/*
#ifdef WITH_OPENGL
void effux_hattu(Uint32 time)
// Kartio/töttörölakki
{
	//glTranslatef(0.0f,0.0f,-2+sin(kulma/10));
	//float kulma;
	//kulma = kulma + PI/2;
	//glRotatef(kulma, 0.0f, 0.0f, 1.0f);
	glRotatef(1.0f, 1.0f, 1.0f, 1.0f);

	int i;
	Uint8 faces = 8;

	glBegin(GL_TRIANGLES);
	for (i=0; i<faces; i++){
		glColor3f( 1.0f, 0.0f, 0.0f);
		glVertex3f( sin(PI/(faces/2)*i), cos(PI/(faces/2)*i), 0.0f);
		glColor3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( sin((PI/(faces/2)*(i+1))), cos(PI/(faces/2)*(i+1)), 0.0f);
		glColor3f( 0.0f, 0.0f, 0.5+0.5*sin(time/100.0));
		glVertex3f( 0.0f, 0.0f, 0.0);

		glColor3f( 1.0f, 0.0f, 0.0f);
		glVertex3f( sin(PI/(faces/2)*i), cos(PI/(faces/2)*i), 0.0f);
		glColor3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( sin(PI/(faces/2)*(i+1)), cos(PI/(faces/2)*(i+1)), 0.0f);
		glColor3f( 0.0f, 0.0f, 0.5+0.5*sin(time/100.0));
		glVertex3f( 0.0f, 0.0f, -1.0f);
	}
	glEnd();
}
#endif
*/

void effux_blur(SDL_Surface *sdlsurface) {
	for (int x=1; x<sdlsurface->w-1; x++)
	{
		for (int y=1; y<sdlsurface->h-1; y++)
		{
			Uint32 pixels[4];
			Uint16 red[4];
			Uint16 green[4];
			Uint16 blue[4];
			pixels[0] = get_pixel_noclip(x, y, sdlsurface);
			pixels[1] = get_pixel_noclip(x+1, y, sdlsurface);
			pixels[2] = get_pixel_noclip(x-1, y, sdlsurface);
			pixels[3] = get_pixel_noclip(x, y+1, sdlsurface);
			pixels[4] = get_pixel_noclip(x, y-1, sdlsurface);
			for (int i = 0; i <= 4; i++)
			{
				red[i] = pixels[i] >> 16 & 255;
				green[i] = pixels[i] >> 8 & 255;
				blue[i] = pixels[i] & 255;
			}
			Uint16 red_ = ( red[0] + red[1] + red[2] + red[3] + red[4] / 5);
			Uint16 green_ = ( green[0] + green[1] + green[2] + green[3] + green[4] / 5);
			Uint16 blue_ = ( blue[0] + blue[1] + blue[2] + blue[3] + blue[4] ) / 5;
			// Separate RGB from color:
			// Calculate average for r, g and b:
			// Put RGB back to color:
			//color0 = (color + color1 + color2 + color3 + color4) / 5;

			draw_pixel_noclip(x, y, Uint32(red_ << 24 + green_ << 16 + blue_ << 8), sdlsurface);
		}
	}
}

void effux1(Uint32 time, SDL_Surface *sdlsurface) {
		Uint32 color;
		int x,y;
		for (y=0; y<sdlsurface->h; y++)
		{
			for (x=0; x<sdlsurface->w; x++)
			{
				color = SDL_MapRGB(sdlsurface->format, x xor y, y - x, time+x);
				draw_pixel_noclip(x, y, color, sdlsurface);

				//draw_vline(res_x/2, 0, res_y, color, screen);

				//color = SDL_MapRGB(sdlsurface->format, y, 255-y-time, 0xff);
				//draw_hline(int(res_x/2-100*sin(time/5.0+y/50.0)), res_x, y, color, false, sdlsurface);
			}
		}
}

EffuxRinkula::EffuxRinkula() {
}

void EffuxRinkula::init(Uint16 width_, Uint16 height_) {
	circles.resize(width_*height_*4);
	for (int y=0; y < 2*height_; y++)
	{
		for (int x=0; x < 2*width_; x++)
		{
			circles[y*(2*width_)+x] =
			(int)sqrt(
			pow(double(y-height_) ,2) +
			pow(double(x-width_) ,2)
			) % (width_/16) > (width_/32);
		}
	}
	width = width_;
	height = height_;
}

void effux2(Uint32 time, SDL_Surface *sdlsurface) {
	// koordinaatisto = false
	float max_distance;
	float distance;
	int liike_x = sdlsurface->w/2 + sdlsurface->w/2*sin(time/1000.0);
	int liike_y = sdlsurface->h/2 + sdlsurface->h/2*cos(time/1000.0);
	Uint32 color;
	int x,y;
	int x_,y_;
	max_distance = sqrt(sdlsurface->w*sdlsurface->w + sdlsurface->h*sdlsurface->h);
	for (y=0; y<sdlsurface->h; y++){
		y_ = y + liike_y;
		for (x=0; x<sdlsurface->w; x++)
			{
				x_ = x - liike_x; // -0.5*max_distance*sin(time);
				distance = sqrt(x_*x_+y_*y_);
				if ((int(distance) < int(max_distance/2*sin(time/1000.0)))){
					//color = SDL_MapRGB(sdlsurface->format, 100, 100, Uint8(128+128.0/res_x*x));
					//color = colorYellow;
				}
				else{
					if (distance != 0){
						color = SDL_MapRGB(sdlsurface->format, Uint8(255/max_distance*distance), Uint8(255-255/max_distance*distance), 0);
						//color = colorGrey;
						draw_pixel_noclip(x, y, color, sdlsurface);
					}
				}
			}
	}
}

void effux3(Uint32 time, SDL_Surface *sdlsurface) {
// Koordinaatisto = false

		int x,y;
		for (y=0; y<sdlsurface->h; y++)
		{
			int y_= round(y+sdlsurface->h*cos(time/1000.0));
			y_ = y_*y_;
			for (x=0; x<sdlsurface->w; x++)
			{
				int x_=round(x+sdlsurface->w*sin(time/1000.0));

				if (int(sqrt(x_*x_+y_)) % 20 > 15)
				{
					draw_pixel_noclip(x, y, SDL_MapRGB(sdlsurface->format, 0, 100+time/10, 100-time/20), sdlsurface);
				}
			}
		}
}
/*
void effux_rotozoomer(Uint32 time, SDL_Surface *image, SDL_Surface *sdlsurface)
// ROTOZOOMER
// KESKEN
{
	Uint32 color;
	SDL_Surface *rotozoomed;
	extern Point P1, P2, P3, P4;

	int x,y;
	float x_min, y_min, x_max, y_max;
	for (y=0; y<sdlsurface->h; y++)
	{
		float angle = time/2000.0;
		// Laske rotatoidun kuvan uusi koko:
			// Rotatoidaan kulmapisteet (origo keskella kuvaa):
			P1.x = 0-(image->w)/2;
			P1.y = 0-(image->h)/2;
			P2.x = 0-(image->w)/2;
			P2.y = 0-(image->h)/2;
			P3.x = 0-(image->w)/2;
			P3.y = 0-(image->h)/2;
			P4.x = 0-(image->w)/2;
			P4.y = 0-(image->h)/2;
			P1.rotate(0, 0, angle);
			P2.rotate(0, 0, angle);
			P3.rotate(0, 0, angle);
			P4.rotate(0, 0, angle);
			// Etsitaan minimit ja maksimit:
			if (P1.x < x_min) x_min = P1.x;
			else if (P1.x > x_max) x_max = P1.x;
			if (P1.y < y_min) y_min = P1.y;
			else if (P1.y > y_max) y_max = P1.y;
			if (P2.x < x_min) x_min = P2.x;
			else if (P2.x > x_max) x_max = P2.x;
			if (P2.y < x_min) x_min = P2.y;
			else if (P2.y > x_max) x_max = P2.y;
			if (P3.x < x_min) x_min = P3.x;
			else if (P3.x > x_max) x_max = P3.x;
			if (P3.y < y_min) y_min = P3.y;
			else if (P3.y > y_max) y_max = P3.y;
			if (P4.x < x_min) x_min = P4.x;
			else if (P4.x > x_max) x_max = P4.x;
			if (P4.y < x_min) x_min = P4.y;
			else if (P4.y > x_max) x_max = P4.y;
		// Varataan muistia uudelle surfacelle;
		// Lasketaan rotatoidun kuvan joka pisteelle.....

	}
}
*/
/*
void effux_bitmapweaver(Uint32 time, SDL_Surface *bitmap, SDL_Surface *sdlsurface) {
	extern SDL_Rect effux_bitmapweaver_rect;
	effux_bitmapweaver_rect.w = sdlsurface->w;
	effux_bitmapweaver_rect.h = sdlsurface->h;
	effux_bitmapweaver_rect.x = (-sdlsurface->w/2+(sdlsurface->w/2-(bitmap->w)/2)*sin(time/1000.0) + (bitmap->w)/2 );
	effux_bitmapweaver_rect.y = (-sdlsurface->h/2+(sdlsurface->h/2-(bitmap->h)/2)*cos(time/1000.0) + (bitmap->h)/2 );
	SDL_BlitSurface(bitmap, &effux_bitmapweaver_rect, sdlsurface, NULL);
}
*/

void effux_geomelem(Uint32 time, SDL_Surface *sdlsurface) {
	// Koordinaatisto = true
	Linesegment linesegment;
	Point Pyora1center, Pyora2center;
	Point Piste;
	int i;
	Uint32 color = SDL_MapRGB(sdlsurface->format, 255, 0, 255);
	//for (i=0; i<100; i++){
		Piste.x = sdlsurface->w/2*sin(time/1000.0);
		Piste.y = sdlsurface->h/2*cos(time/1000.0);

		//Piste.rotate(0, 0, PI/100.0*((time/1000.0))+i);
		//draw_line(Piste.X, Piste.Y, 0, 0, colorWhite, true, sdlsurface);


		// Juna:
		draw_circle(Piste, 64, 24, 10, colorBlue, sdlsurface);

		linesegment.A.x = 300;
		linesegment.A.y = 300;
		linesegment.B.x = 0;
		linesegment.B.y = 0;
		linesegment.A.rotate(0, 0, time/(1000.0));
		linesegment.B.rotate(0, 0, time/-1000.0);

		draw_line(linesegment.A.x, linesegment.A.y, -linesegment.B.x, -linesegment.B.y, 10, colorYellow, sdlsurface);

	//}
}

void effux_chessplane(Uint32 time, SDL_Surface *sdlsurface) {
	//koordinaatisto = true
	extern Uint32 hsltable[16][16][16];
	int size = 80;    // Chess board's square
	bool colorbool;
	Uint32 color;
	for (int y=1; y<sdlsurface->h/2; y++) {
		for (int x=-sdlsurface->w/2; x<sdlsurface->w/2; x++) {
			int persp_y = 6*y;//abs(y/(x/100.0));
			int persp_x = abs(int(x/(y/100.0)));
			colorbool = false;

			if ( ( (persp_y + time/4) % size ) > size/2 )
			{
				colorbool = !colorbool;
			}
			if ( (persp_x % size) > size/2 )
			{
				colorbool = !colorbool;
			}
			if (colorbool)
			{
				color = hsltable [abs(x/30) & 15] [abs(y/30) & 15] [10] ;
			}
			else
			{
				color = hsltable [abs(y/30) & 15] [abs(x/30) & 15] [5] ;
			}
			draw_pixel_clip(x, y, color, sdlsurface);
		}
	}
}

void EffuxRinkula::draw(Uint32 time, bool both, SDL_Surface *sdlsurface) {
	// Koordinaatisto= false
	//float distance1, distance2;
	//int pos_x, pos_y;
	Uint32 color;
	int x,y;
	//int x_,y_;
	int liike_y1 = round(height/2*cos(-time/1000.0));
	int liike_x1 = round(width/2*sin(-time/1200.0));
	int liike_y2 = round(height/2*cos(time/1800.0));
	int liike_x2 = round(width/2*sin(time/1000.0));
	//int index_x1;
	int index_y1;
	//int index_x2;
	int index_y2;

/*
		if (circles[ int((y+res_y/2+liike_y1) *res_x*2 +
							  x+res_x/2+liike_x1) ]
				xor
				circles[ int((y+res_y/2+liike_y2) *res_x*2 +
							  x+res_x/2+liike_x2) ]
				)

*/

	for (y=0; y<sdlsurface->h; y++) {
		index_y1 = (y+height/2+liike_y1)*width*2;
		index_y2 = (y+height/2+liike_y2)*width*2;

		for (x=0; x<sdlsurface->w; x++) {
			if (circles[index_y1 + x+sdlsurface->w/2+liike_x1] xor circles[index_y2 + x+sdlsurface->w/2+liike_x2]) {
			// JOS BIT XOR 1
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
							/*
							ColorHSL colorhsl;
							ColorRGB colorrgb;
							colorhsl.h = 1.0/sdlsurface->w*x;
							colorrgb = HSLtoRGB(colorhsl);
							color = SDL_MapRGB(sdlsurface->format, round(255*colorrgb.r), round(255*colorrgb.g), round(255*colorrgb.b));
							*/
							//extern Uint32 hsltable[16][16][16];
							//color = hsltable [(y >> 5) & 15] [3] [7];

						draw_pixel_noclip(x, y, color, sdlsurface);
				}
			}
			else {
			// JOS BIT XOR 0
						// Sierpinski 1:
							color = SDL_MapRGB(sdlsurface->format, y and Uint8(x+time/100), x xor Uint8(y+time/100), Uint8(x-time/100) xor y);
							//color = Uint8(y and Uint8(x+time/100)) << 16 + Uint8(x xor Uint8(y+time/100)) << 8 + Uint8(x-time/100 xor y);
							//color = colorBlack;
						// ?:
							color =
							(Uint8(y xor Uint8(x+time/100)) << 16) +
							(Uint8(x xor Uint8(y+time/100)) << 8) +
							(Uint8(Uint8(x-time/100)) xor y);
						// Rainbow:
							/*
							ColorHSL colorhsl;
							ColorRGB colorrgb;
							colorhsl.h = 1.0/sdlsurface->w*x;
							colorrgb = HSLtoRGB(colorhsl);
							color = SDL_MapRGB(sdlsurface->format, 255-round(255*colorrgb.r), 255-round(255*colorrgb.g), 255-round(255*colorrgb.b));
							*/
							//extern Uint32 hsltable[16][16][16];
							//color = hsltable[(x >> 5) & 15] [7] [11];

						draw_pixel_noclip(x, y, color, sdlsurface);
			}
		}
	}
}

void effux_viivat(Uint8 index, SDL_Surface *sdlsurface) {
	/*
	std::vector<Vertex3d> temp = Entiteetti.vertex3darray;
	#ifndef WITH_OPENGL
		Entiteetti.color = colorYellow;
	#endif
	Entiteetti.polygonshadestyle = POLYGON_SHADESTYLE_WIREFRAME;
	//std::vector<Vertex3d> temp = Entiteetti.vertex3darray;
	Entiteetti.pushgeom();
	Entiteetti.rotatevertexarray();
	Entiteetti.rotation.x = time/1548.0;
	Entiteetti.rotation.y = time/1023.5;
	Entiteetti.rotation.z = time/660.0;
		Entiteetti.draw3d_polygon();
		//Entiteetti.draw_wireframe(true, screen);
		//Entiteetti.vertex3darray = temp;
	Entiteetti.popgeom();
*/


Point a, b;
a.x = 300;
a.y = 300;
b.x = 0;
b.y = 0;
a.rotate(0, 0, index/100.0f);
a.rotate(0, 0, index/100.0f);
draw_line(a.x, a.y, b.x, b.y, 1, colorBlue, sdlsurface);

}


//#ifdef WITH_OPENGL
//void effux_entity(Uint32 time, Entity Entiteetti)
//#else
void effux_entity(Uint32 time, Entity Entiteetti, SDL_Surface *sdlsurface)
//#endif
{
	//effux_chessplane(time, screen);
	//#ifndef WITH_OPENGL
		Entiteetti.color = colorYellow;
	//#endif
//    Entiteetti.polygonshadestyle = POLYGON_SHADESTYLE_WIREFRAME;
	//std::vector<Vertex3d> temp = Entiteetti.vertex3darray;
	Entiteetti.pushgeom();
	Entiteetti.rotation.x = time/1500.0;
	Entiteetti.rotation.y = time/1500.0;
	Entiteetti.rotation.z = time/1500.0;
	Entiteetti.rotatevertexarray();
		Entiteetti.draw3d_polygon();
		//Entiteetti.draw_wireframe(true, screen);
		//Entiteetti.vertex3darray = temp;
	Entiteetti.popgeom();
}





