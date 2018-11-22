/*
	SF-Engine

	This file has routines for drawing graphics.
*/

#include "grapher.hpp"

void Grapher::draw_pixel(Uint16 x, Uint16 y, unsigned int color) {
	unsigned char *p = (unsigned char *)this->sdlsurface->pixels
		+ y * this->sdlsurface->pitch
		+ x * this->sdlsurface->format->BytesPerPixel;
	p[0] = color & 0xff;
	p[1] = (color >> 8) & 0xff;
	p[2] = (color >> 16) & 0xff;
}

void Grapher::draw_triangle(Triangle2D triangle) {
	/*
	switch(shadestyle) {
		case POLYGON_SHADESTYLE_POINT:
			draw_pixel(tr.a.x, tr.a.y, tr.a.colorint(sdlsurface), sdlsurface);
			draw_pixel(tr.b.x, tr.b.y, tr.b.colorint(sdlsurface), sdlsurface);
			draw_pixel(tr.c.x, tr.c.y, tr.c.colorint(sdlsurface), sdlsurface);
			break;
		case POLYGON_SHADESTYLE_WIREFRAME:
			draw_line(tr.a.x, tr.a.y, tr.b.x, tr.b.y, 3, tr.a.colorint(sdlsurface), sdlsurface);
			draw_line(tr.b.x, tr.b.y, tr.c.x, tr.c.y, 3, tr.b.colorint(sdlsurface), sdlsurface);
			draw_line(tr.c.x, tr.c.y, tr.a.x, tr.a.y, 3, tr.c.colorint(sdlsurface), sdlsurface);
			break;
		case POLYGON_SHADESTYLE_SINGLE:
			// TODO:
			//Sort a.y > b.y > c.y :
			Vertex2d tmp;
			if (tr.c.y < tr.b.y) {
				tmp = tr.b;
				tr.b = tr.c;
				tr.c = tmp;
			}
			if (tr.b.y < tr.a.y) {
				tmp = tr.a;
				tr.a = tr.b;
				tr.b = tmp;
			}
			// ??

			if (tr.c.y < tr.b.y) {
				tmp = tr.b;
				tr.b = tr.c;
				tr.c = tmp;
			}

			// Slopes for sides:
			float k_ab, k_ac, k_bc;

			if (tr.b.y != tr.a.y) {k_ab = (tr.b.x-tr.a.x) / (tr.b.y-tr.a.y);}
			if (tr.c.y != tr.a.y) {k_ac = (tr.c.x-tr.a.x) / (tr.c.y-tr.a.y);}
			if (tr.c.y != tr.b.y) {k_bc = (tr.c.x-tr.b.x) / (tr.c.y-tr.b.y);}

			float left = tr.a.x;
			float right = tr.a.x;
			// Draw upper part ABD:
			for (int i=round(tr.a.y); i<round(tr.b.y); i++) {
				if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
					draw_hline(left, right, i, tr.a.colorint(sdlsurface), sdlsurface);
					//draw_hline_gouraud(left, right, i, tr.a.colorint(sdlsurface), coordinategrid, sdlsurface);
				}
				else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
				}
				left = left + k_ab;
				right = right + k_ac;
			}
			// Draw lower part BCD:
			for (int i=round(tr.b.y); i<round(tr.c.y); i++) {
				if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
					draw_hline(left, right, i, tr.a.colorint(sdlsurface), sdlsurface);
				}
				else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
				}
				left = left + k_bc;
				right = right + k_ac;
			}
			break;
	}   // switch(shadestyle){
	*/
}

void Grapher::draw_triangle(Triangle3D triangle) {
}

void Grapher::draw_polygon(Polygon2D *polygon) {
}

void Grapher::draw_polygon(Polygon3D *polygon) {
}
