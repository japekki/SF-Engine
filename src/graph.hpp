#ifndef GRAPH_HPP
	#define GRAPH_HPP

	// CONSTANTS:
		#define POLYGON_SHADESTYLE_NODRAW 0
		#define POLYGON_SHADESTYLE_POINT 1
		#define POLYGON_SHADESTYLE_WIREFRAME 2
		#define POLYGON_SHADESTYLE_SINGLE 3
		#define POLYGON_SHADESTYLE_FLAT 4
		#define POLYGON_SHADESTYLE_GOURAUD 5
		#define POLYGON_SHADESTYLE_TEXTURE 6

	//#include "options.hpp"
	#include <SDL/SDL.h>

	#include "math.hpp"
	#include "graph3d.hpp"

	//#ifdef WITH_OPENGL
	//    #include <GL/gl.h>
	//#endif

	#include <iostream>

	// GLOBALS:
		//extern Display Monitor;

	using namespace std;

	class Sprite {
		public:
		Sprite();
		// Opengl:
			//std::vector<char> pixeldata:
			//draw(int x, int y);

			SDL_Surface *sdlsurface;
			Sprite(SDL_Surface *sdlsurface);
			//draw(int x, int y);   // for to global default or something
			void draw(int x, int y, SDL_Surface *sdlsurface_);
			void draw(int x, int y, Sprite another);

		bool collide(Sprite another);
		// TODO:
		//void scale(float factor);
		//void scale(float xfactor, float yfactor);
		// void colornegate();
		// void negate();
		// void set_hue();
		// void set_saturation();
		// void set_lightness();
		// void multiply(Color color);
		// void multiply(ColorHSL colorhsl);
		// void multiply(ColorRGB colorrgb);
	};

	/* Opengl:
		class Vertex2d {
			public:
			GLfloat x,y;
			GLfloat r,g,b;
			Vertex2d();
		};
	*/
		class Vertex2d {
			public:
			float x,y;
			float r,g,b;
			Vertex2d();
			Uint32 colorint(SDL_Surface *sdlsurface);
		};


	struct ColorHSL {
		float h;
		float s;
		float l;
	};

	struct ColorRGB {
		float r;
		float g;
		float b;
	};

	struct pixel2d {
		float x;
		float y;
		float r;
		float g;
		float b;
	};

	struct triangle2d {
		Vertex2d a;
		Vertex2d b;
		Vertex2d c;
	};

	class Triangle2d {
	public:
		Point a, b, c;
		Uint32 color;
		Triangle2d();
		void draw();
	};

	class Color {
		private:
			float r;
			float g;
			float b;
			float h;
			float s;
			float l;
		public:
			Color();
			void Set(ColorHSL colorhsl);
			void Set(ColorRGB colorrgb);
			ColorHSL Gethsl();
			ColorRGB Getrgb();
			Uint32 getsdlcolor(SDL_Surface *sdlsurface);
	};

	// FUNKTIOT:
		SDL_Surface* scale_surface(int new_x, int new_y, SDL_Surface *bitmap);
		SDL_Surface *load_image(string filename);
		ColorRGB HSLtoRGB(float h, float s, float l);
		ColorRGB HSLtoRGB(ColorHSL colorHSL);
		// Pixel drawing:
			Uint32 get_pixel_clip(int x, int y, SDL_Surface *sdlsurface);
			Uint32 get_pixel_noclip(int x, int y, SDL_Surface *sdlsurface);
			void draw_pixel_clip(int x, int y, Uint32 color, SDL_Surface *sdlsurface);
			void draw_pixel_noclip(int x, int y, Uint32 color, SDL_Surface *sdlsurface);
		// Line drawing:
			void draw_hline(int x1, int x2, int y, Uint32 color, SDL_Surface *sdlsurface);
			void draw_hline_gouraud(int x1, int x2, int y, Uint32 color, bool koordinaatisto, SDL_Surface *sdlsurface);
			void draw_vline(int x, int y1, int y2, Uint32 color, SDL_Surface *sdlsurface);
			void draw_line(int x1, int y1, int x2, int y2, Uint8 width, Uint32 color, SDL_Surface *sdlsurface);
		// Triangle drawing:
			void draw2d_triangle(triangle2d tr, Uint8 shadestyle, bool koordinaatisto, SDL_Surface *surface);
			//void draw_triangle(triangle3d tr, Uint8 shadestyle, bool koordinaatisto, SDL_Surface *surface);
		// Geometric:
			void draw_square(float x1, float y1, float x2, float y2, Uint32 color, SDL_Surface *sdlsurface);
			void draw_circle(float x, float y, float r, Uint8 slices, Uint8 width, Uint32 color, SDL_Surface *sdlsurface);
			void draw_circle(point2d c, float r, Uint8 slices, Uint8 width, Uint32 color, SDL_Surface *sdlsurface);
			void draw_circle(Point P, float r, Uint8 slices, Uint8 width, Uint32 color, SDL_Surface *sdlsurface);

	// MUUTTUJAT:
		extern bool gpuvertexbuffer;

	// VAKIOT:
		extern Uint32 colorRed;
		extern Uint32 colorGreen;
		extern Uint32 colorBlue;
		extern Uint32 colorWhite;
		extern Uint32 colorBlack;
		extern Uint32 colorYellow;
		extern Uint32 colorCyan;
		extern Uint32 colorOrange;
		extern Uint32 colorViolet;
		extern Uint32 colorBrown;
		extern Uint32 colorGrey;

#endif // GRAPH_HPP
