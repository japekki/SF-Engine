/*
	SF-Engine

	This file has routines for 3D graphics.
*/

#include <math.h>
#include <iostream>
#include "display.hpp"
#include "graph3d.hpp"
#include "globals.hpp"

// GLOBALS:
extern Display monitor;

Pixel3d::Pixel3d() {
}

void Pixel3d::setcolor(Uint32 color_) {
  color = color_;
  // TODO: update r, g, b
}

void Pixel3d::setcolor(float r_, float g_, float b_) {
  r = r_;
  g = g_;
  b = b_;
}

Uint32 Pixel3d::getcolor(SDL_Surface *sdlsurface) {
  return SDL_MapRGB(sdlsurface->format, Uint8(255*r), Uint8(255*g), Uint8(255*b));
}

//float[3] Pixel3d::getcolor()
//{
//}

Triangle3d::Triangle3d() {
}

Triangle3d::~Triangle3d() {
#ifdef WITH_DEBUG
  printf("Triangle3d destructor\n");
#endif
}

Vertex3d::Vertex3d() {
}


Uint32 Vertex3d::colorint(SDL_Surface *sdlsurface) {
  Uint32 color = SDL_MapRGB(sdlsurface->format, Uint8(255*r), Uint8(255*g), Uint8(255*b));
  return color;
}



void draw3d_pixel(int x, int y, float z, Uint32 color, SDL_Surface *sdlsurface) {
	// * NOTE: The surface must be locked before calling this!
  int index;

  int clip_x1, clip_x2, clip_y1, clip_y2;
  if (monitor.centered) {
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
		  index = monitor.get_width()*(y+monitor.get_height()/2)+(x+monitor.get_width()/2);
		}
	  else {
		  index = monitor.get_width()*y+x;
		}
	  if (z < monitor.z_buf.z.at(index)) {
		  draw_pixel_clip(x, y, color, sdlsurface);
		  monitor.z_buf.z.at(index) = z;
		}
	}
}


void draw3d_hline(Point a, Point b, Uint32 color, SDL_Surface *sdlsurface) {
  // TODO: Leikkaa koordinaatit näytön reunojen mukaan
  if (a.x > b.x) {
	  Point tmp = a;
	  a = b;
	  b = tmp;
	}
  float z = a.z;
  float k_z = 0;
  if (round(b.x) != round(a.x)) {
	  k_z = (b.z - a.z) / (b.x - a.x);    // Z;n muutos kun X muuttuu yhdella
	}
  int x;
  for (x=round(a.x); x<=round(b.x); x++) {
	  z = z + k_z;
	  draw3d_pixel(x, a.y, z, color, sdlsurface);
	  //draw_pixel_clip(x, a.y, color, sdlsurface);
	}
}

void draw3d_hlinesmooth(Point A, Point B, SDL_Surface *sdlsurface) {
  // TODO: Leikkaa koordinaatit näytön reunojen mukaan
  if (A.x > B.x) {
	  Point Tmp = A;
	  A = B;
	  B = Tmp;
	}
  float z = A.z;
  float k = (B.z - A.z) / (B.x - A.x);    // Z;n muutos kun X muuttuu yhdella
  int x;
  float color;
  //float color_k = (color2 - color1) / (B.x - A.x);
  for (x=A.x; x<=B.x; x++) {

	  z = z + k;
	  //color = color + color_k;
	  draw3d_pixel(x, A.y, z, round(color), sdlsurface);

	}
}

void draw3d_vline(Point A, Point B, Uint32 color, SDL_Surface *sdlsurface) {
}

void draw3d_line(Point A, Point B, Uint32 color, SDL_Surface *sdlsurface) {
}

void draw3d_triangle(SDL_Surface *sdlsurface) {
}


void Triangle3d::draw(SDL_Surface *sdlsurface) {
  if (shadestyle == POLYGON_SHADESTYLE_POINT) {
	  draw_pixel_clip(a.x, a.y, a.getcolor(sdlsurface), sdlsurface);
	  draw_pixel_clip(b.x, b.y, b.getcolor(sdlsurface), sdlsurface);
	  draw_pixel_clip(c.x, c.y, c.getcolor(sdlsurface), sdlsurface);
	}
  else if (shadestyle == POLYGON_SHADESTYLE_WIREFRAME) {
	  draw_line(a.x, a.y, b.x, b.y, 1, a.getcolor(sdlsurface), sdlsurface);
	  draw_line(b.x, b.y, c.x, c.y, 1, b.getcolor(sdlsurface), sdlsurface);
	  draw_line(c.x, c.y, a.x, a.y, 1, c.getcolor(sdlsurface), sdlsurface);
	}
  else if (shadestyle == POLYGON_SHADESTYLE_SINGLE or shadestyle == POLYGON_SHADESTYLE_FLAT or shadestyle == POLYGON_SHADESTYLE_GOURAUD) {
	  // TODO:
	  //Sort a.y < b.y < c.y :
	  Pixel3d tmp;
	  if (c.y < b.y) {
		  tmp = b;
		  b = c;
		  c = tmp;
		}
	  if (c.y < a.y) {
		  tmp = a;
		  a = c;
		  c = tmp;
		}
	  if (b.y < a.y) {
		  tmp = a;
		  a = b;
		  b = tmp;
		}
	  // ??
	  /*
			  if (tr.c.y < tr.b.y){
				  tmp = tr.b;
				  tr.b = tr.c;
				  tr.c = tmp;
			  }
	  */
	  // Kulmakertoimet sivuille:
	  float k_ab, k_ac, k_bc = 0; // Used for calculating scanline's left and right x coordinates
	  float color_k_ab, color_k_ac, color_k_bc;   // For gouraud shading

	  if (b.y != a.y) {
		  k_ab = (b.x-a.x) / (b.y-a.y);
		}
	  if (c.y != a.y) {
		  k_ac = (c.x-a.x) / (c.y-a.y);
		}
	  if (c.y != b.y)
		{
		  k_bc = (b.x-c.x) / (b.y-c.y);
		}
	  if (shadestyle == POLYGON_SHADESTYLE_GOURAUD) {
		  if (b.y != a.y) {
			  color_k_ab = (b.x-a.x) / (b.y-a.y);
			}
		  else {
			  color_k_ab = 0;
			}
		  if (c.y != a.y) {
			  color_k_ac = (c.x-a.x) / (c.y-a.y);
			}
		  else {
			  color_k_ac = 0;
			}
		  if (c.y != b.y) {
			  color_k_bc = (c.x-b.x) / (c.y-b.y);
			}
		  else {
			  color_k_bc = 0;
			}
		}
	  float k_z_ab, k_z_ac, k_z_bc;       // Used for calculating scanline's left and right z coordinates
	  if ((b.z - a.z) != 0) {
		  k_z_ab = (b.z - a.z) / (b.y - a.y);
		}
	  else {
		  k_z_ab = 0;
		}
	  if ((c.z - a.z) != 0) {
		  k_z_ac = (c.z - a.z) / (c.y - a.y);
		}
	  else {
		  k_z_ac = 0;
		}
	  if ((c.z - b.z) != 0) {
		  k_z_bc = (c.z - b.z) / (c.y - b.y);
		}
	  else {
		  k_z_bc = 0;
		}
	  // Piirra ylaosa ABD:
	  float left = a.x;
	  float right = a.x;
	  float left_z = a.z;
	  float right_z = a.z;
	  if (round(a.y) != round(b.y))
		for (int y=round(a.y); y<round(b.y); y++) {
			if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
				Point p1, p2;
				p1.x = left;
				p1.y = y;
				p2.x = right;
				p2.y = y;
				draw3d_hline(p1, p2, color, sdlsurface);
			  }
			else if (shadestyle==POLYGON_SHADESTYLE_FLAT) {
				Point p1, p2;
				p1.x = left;
				p1.y = y;
				p1.z = left_z;
				p2.x = right;
				p2.y = y;
				p2.z = right_z;
				draw3d_hline(p1, p2, color, sdlsurface);
			  }
			else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
				Pixel3d p1, p2;
				p1.x = left;
				p1.y = y;
				p2.x = right;
				p2.y = y;
				//draw3d_hlinesmooth(p1, p2, sdlsurface);
			  }
			left = left + k_ab;
			right = right + k_ac;
			left_z = left_z + k_z_ab;
			right_z = right_z + k_z_ac;
		  }
	  // Piirra alaosa BCD:
	  // TODO: mieti nyt vielä miksi tämä toimii/ei toimi
	  left = b.x;//a.x + (round(b.y) - round(a.y)) * k_ab;
	  right = a.x + (round(b.y) - round(a.y)) * k_ac;
	  left_z = b.z;
	  right_z = a.z + (round(b.y) - round(a.y)) * k_z_ac;
	  for (int y=round(b.y); y<round(c.y); y++) {
		  if (shadestyle==POLYGON_SHADESTYLE_SINGLE) {
			  Point p1, p2;
			  p1.x = left;
			  p1.y = y;
			  p2.x = right;
			  p2.y = y;
			  draw3d_hline(p1, p2, color, sdlsurface);
			}
		  else if (shadestyle==POLYGON_SHADESTYLE_FLAT) {
			  Point p1, p2;
			  p1.x = left;
			  p1.y = y;
			  p2.x = right;
			  p2.y = y;
			  p2.y = y;
			  p2.z = right_z;
			  draw3d_hline(p1, p2, color, sdlsurface);
			}
		  else if (shadestyle==POLYGON_SHADESTYLE_GOURAUD) {
			  Pixel3d p1, p2;
			  p1.x = left;
			  p1.y = y;
			  p2.x = right;
			  p2.y = y;
			  //draw3d_hlinesmooth(p1, p2, sdlsurface);
			}
		  left = left + k_bc;
		  right = right + k_ac;
		  left_z = left_z + k_z_bc;
		  right_z = right_z + k_z_ac;

		  // TODO: smooth/gouraud shading
		}
	}   // SHADESTYLE_SINGLE or SHADESTYLE_FLAT or SHADESTYLE_GOURAUD
}



Zbuf::Zbuf() {
  //z.resize(monitor.get_width()*monitor.get_height());
}

Zbuf::Zbuf(Uint16 size_x, Uint16 size_y) {
  //z.resize(size_x*size_y);
}

void Zbuf::resize(Uint32 newsize) {
  //z.resize(newsize);
}

void Zbuf::reset() {
  Uint32 i;
  for (i=0; i<z.size(); i++) {
	  z.at(i)=1000000.0;
	}
};

//scale = sivun pituus * glVertex3f
void generate_cube(float x, float y, float z, float scale, float r, float g, float b) {
/*
#ifdef WITH_OPENGL
  glBegin(GL_TRIANGLES);
  // Kuution pinnat A-F (12 triangelia; 2 per pinta):
  // A:
  glColor3f( r,g,b);
  glVertex3f (x-scale/2, y-scale/2, z-scale/2);
  //glVertex3f (0.5, 0, 0);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z-scale/2);
  //glVertex3f (0.5, 0.5, 0.2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z-scale/2);
  //glVertex3f (0.8, -1.2, 0.6);

  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z-scale/2);
  // B:
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z+scale/2);

  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z+scale/2);
  // C:
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z+scale/2);

  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z+scale/2);
  // D:
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z+scale/2);

  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z+scale/2);
  // E:
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z+scale/2);

  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y+scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y+scale/2, z-scale/2);
  // F:
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z-scale/2);
  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z+scale/2);

  glColor3f( r,g,b );
  glVertex3f (x-scale/2, y-scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z+scale/2);
  glColor3f( r,g,b );
  glVertex3f (x+scale/2, y-scale/2, z-scale/2);

  glEnd();
#else
#endif
*/
}
