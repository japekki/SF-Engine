/*
	SF-Engine

	This file has routines for drawing graphics.
*/

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
			SDL_Texture* load_texture(const char* filename);
			//void draw_pixel(Uint16 x, Uint16 y, unsigned int color);
			//void draw_hline(int x1, int x2, int y, unsigned int color);
			void draw_triangle(Triangle2D *triangle);
			void draw_triangle(Triangle3D *triangle);
			void draw_polygon(Polygon2D *polygon);
			void draw_polygon(Polygon3D *polygon);
			SDL_Renderer *sdlrenderer;
			//SDL_Texture *sdltexture;
			bool with_coordinategrid = false;
			Coordinategrid *coordinategrid;
	};

#endif // GRAPHER_HPP
