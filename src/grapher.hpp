#ifndef GRAPHER_HPP
	#define GRAPHER_HPP

	#include <SDL.h>
	#include "geom.hpp"
	#include "zbuf.hpp"

	class Grapher {
		public:
			unsigned short width;
			unsigned short height;
			Zbuf *zbuf;
			void draw_pixel(Uint16 x, Uint16 y, unsigned int color);
			void draw_hline(int x1, int x2, int y, unsigned int color);
			//void draw_line(int x1, int y1, int x2, int y2, unsigned char width, unsigned int color, SDL_Surface *sdlsurface);
			void draw_triangle(Triangle2D triangle);
			void draw_triangle(Triangle3D triangle);
			void draw_polygon(Polygon2D *polygon);
			void draw_polygon(Polygon3D *polygon);
			SDL_Surface *sdlsurface;
			bool with_coordinategrid = false;
			Coordinategrid *coordinategrid;
	};

#endif // GRAPHER_HPP
